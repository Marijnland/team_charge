
#include "LedDefines.h"
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "LedControl.h"

const char* ssid = "";
const char* password = "";
const char* mqtt_server = "broker.mqttdashboard.com";

WiFiClient espClient;
PubSubClient client(espClient);
int car1phase, car2phase, car3phase, car4phase = 0;
int co2saved, pvpower, gridpower, gridphases = 0;

// Connect the dot matrices as follows: pin 2 from the feather on Din on the matrix, pin 4 to clk, pin 5 to cs
// 13 displays chained
LedControl lc=LedControl(2,4,5,13);

unsigned long lastupdate = 0;
unsigned long matrixupdate = 0;

int pv_increment = 0;

int dataPin = 0;
int latchPin = 15;
int clockPin = 13;



void set_led_matrices(void);
void drawDigit(int digit, int x, int y, int display);
void update_leds();


void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  char inmessage[10] = {0};
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) 
  {
    inmessage[i] = (char)payload[i];
  }

  if(!strcmp(topic, "HANinfoboard/Car1phase"))
  {
    car1phase = atoi(inmessage);
    Serial.print("Car1 phase = ");
    Serial.println(car1phase);
  }  
  else if(!strcmp(topic, "HANinfoboard/Car2phase"))
  {
    car2phase = atoi(inmessage);
    Serial.print("Car2 phase = ");
    Serial.println(car2phase);
  }
  else if(!strcmp(topic, "HANinfoboard/Car3phase"))
  {
    car3phase = atoi(inmessage);
    Serial.print("Car3 phase = ");
    Serial.println(car3phase);  
  }
  else if(!strcmp(topic, "HANinfoboard/Car4phase"))
  {
    car4phase = atoi(inmessage);
    Serial.print("Car4 phase = ");
    Serial.println(car4phase);
  }
  else if(!strcmp(topic, "HANinfoboard/CO2saved"))
  {
    co2saved = atoi(inmessage);
    Serial.print("co2 saved = ");
    Serial.println(co2saved);
  }
  else if(!strcmp(topic, "HANinfoboard/Gridphases"))
  {
    gridphases = atoi(inmessage);
    Serial.print("grid phases = ");
    Serial.println(gridphases);
  }  
  else if(!strcmp(topic, "HANinfoboard/Gridpower"))
  {
    gridpower = atoi(inmessage);
    Serial.print("grid power = ");
    Serial.println(gridpower);
  }  
  else if(!strcmp(topic, "HANinfoboard/PVpower"))
  {
    pvpower = atoi(inmessage);
    Serial.print("pv power = ");
    Serial.println(pvpower);
  }
  else
  {
    Serial.println("UNKNOWM message topic");
  }


}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-Marijn";
    //clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      //client.publish("HANinfoboard/testje", "hello world");
      client.subscribe("HANinfoboard/CO2saved");
      client.subscribe("HANinfoboard/Car1phase");
      client.subscribe("HANinfoboard/Car2phase");
      client.subscribe("HANinfoboard/Car3phase");
      client.subscribe("HANinfoboard/Car4phase");
      client.subscribe("HANinfoboard/Gridphases");
      client.subscribe("HANinfoboard/Gridpower");
      client.subscribe("HANinfoboard/PVpower");

    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);

  //Set display brightness, 13 pieces
  for(int i=0;i<13;i++)
  {
      lc.shutdown(i,false);
      lc.setIntensity(i,8);
      lc.clearDisplay(i);
  }
  //Test to show digits on displays
  for(int i=0; i<8; i++)
    drawDigit(i+1, 2, -1, i);
  for(int i=0; i<5; i++)
    drawDigit(i+9, 2, -1, i);

  


  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) 
  {
    reconnect();
  }
  client.loop();

  unsigned long now = millis();
  if(now - lastupdate > 500)
  {
    lastupdate = now;
    update_leds();
  }
  if(now - matrixupdate > 15000)
  {
    set_led_matrices();
    matrixupdate = now;
  }

}

void update_leds()
{
	// to write a one to shift registers, 
	// latchpin low
	// datapin high (or low to write zero)
	// clockpin high and then low
	// latchpin high to enable output
  digitalWrite(latchPin, LOW);
  digitalWrite(dataPin, HIGH);
  digitalWrite(clockPin, HIGH);
  digitalWrite(clockPin, LOW);
  digitalWrite(latchPin, HIGH);
}


void set_led_matrices()
{
  for(int i=0; i<13; i++)
    lc.clearDisplay(i);

  int carpower = pvpower - gridpower;
  if (carpower < 0)
    carpower = 0;

  if(pvpower < 10)
  {
    drawDigit(0,2,-1,pv_power_matrix0);
    drawDigit(0,2,-1,pv_power_matrix1);
    drawDigit(pvpower,2,-1,pv_power_matrix2);
  }
  else if(pvpower < 100)
  {
    drawDigit(0,2,-1,pv_power_matrix0);
    drawDigit((int)(pvpower/10),2,-1,pv_power_matrix1);
    drawDigit((pvpower%10),2,-1,pv_power_matrix2);

  }
  else
  {
    drawDigit((int)(pvpower/100),2,-1,pv_power_matrix0);
    drawDigit((int)(pvpower/10),2,-1,pv_power_matrix1);
    drawDigit((pvpower%10),2,-1,pv_power_matrix2);
  }

  if(gridpower < 0)
  {
    gridpower *= -1;
    drawDigit(10,0,0,grid_power_matrix0);
    //Write +- signs in grid_power_matrix0
  }
  else
    drawDigit(11,0,0,grid_power_matrix0);

  if(gridpower < 10)
  {
    drawDigit(0,2,-1,grid_power_matrix1);
    drawDigit(0,2,-1,grid_power_matrix2);
    drawDigit(gridpower,2,-1,grid_power_matrix3);
  }
  else if(gridpower < 100)
  {
    drawDigit(0,2,-1,grid_power_matrix1);
    drawDigit((int)(gridpower/10),2,-1,grid_power_matrix2);
    drawDigit((gridpower%10),2,-1,grid_power_matrix3);

  }
  else
  {
    drawDigit((int)(gridpower/100),2,-1,grid_power_matrix1);
    drawDigit((int)(gridpower/10),2,-1,grid_power_matrix2);
    drawDigit((gridpower%10),2,-1,grid_power_matrix3);
  }

  if(carpower < 10)
  {
    drawDigit(0,2,-1,car_power_matrix0);
    drawDigit(0,2,-1,car_power_matrix1);
    drawDigit(carpower,2,-1,car_power_matrix2);
  }
  else if(carpower < 100)
  {
    drawDigit(0,2,-1,car_power_matrix0);
    drawDigit((int)(carpower/10),2,-1,car_power_matrix1);
    drawDigit((carpower%10),2,-1,car_power_matrix2);

  }
  else
  {
    drawDigit((int)(carpower/100),2,-1,car_power_matrix0);
    drawDigit((int)(carpower/10),2,-1,car_power_matrix1);
    drawDigit((carpower%10),2,-1,car_power_matrix2);
  }
  
  if(co2saved < 10)
  {
    drawDigit(0,2,-1,co2_saved_matrix0);
    drawDigit(0,2,-1,co2_saved_matrix1);
    drawDigit(co2saved,2,-1,co2_saved_matrix2);
  }
  else if(co2saved < 100)
  {
    drawDigit(0,2,-1,co2_saved_matrix0);
    drawDigit((int)(co2saved/10),2,-1,co2_saved_matrix1);
    drawDigit((co2saved%10),2,-1,co2_saved_matrix2);

  }
  else
  {
    drawDigit((int)(co2saved/100),2,-1,co2_saved_matrix0);
    drawDigit((int)(co2saved/10),2,-1,co2_saved_matrix1);
    drawDigit((co2saved%10),2,-1,co2_saved_matrix2);
  }


}

void drawDigit(int digit, int x, int y, int display)
{
  switch (digit)
  {
    case 0:
      lc.setLed( display, 1+x, 7+y,  1 );
      lc.setLed( display, 2+x, 7+y,  1 );
      lc.setLed( display, 0+x, 6+y,  1 );
      lc.setLed( display, 3+x, 6+y,  1 );
      lc.setLed( display, 0+x, 5+y,  1 );
      lc.setLed( display, 3+x, 5+y,  1 );
      lc.setLed( display, 0+x, 4+y,  1 );
      lc.setLed( display, 3+x, 4+y,  1 );
      lc.setLed( display, 0+x, 3+y,  1 );
      lc.setLed( display, 3+x, 3+y,  1 );
      lc.setLed( display, 0+x, 2+y,  1 );
      lc.setLed( display, 3+x, 2+y,  1 );
      lc.setLed( display, 1+x, 1+y,  1 );
      lc.setLed( display, 2+x, 1+y,  1 );
      break;

    case 1:
      lc.setLed( display, 2+x, 7+y,  1 );
      lc.setLed( display, 1+x, 6+y,  1 );
      lc.setLed( display, 2+x, 6+y,  1 );
      lc.setLed( display, 2+x, 5+y,  1 );
      lc.setLed( display, 2+x, 4+y,  1 );
      lc.setLed( display, 2+x, 3+y,  1 );
      lc.setLed( display, 2+x, 2+y,  1 );
      lc.setLed( display, 1+x, 1+y,  1 );
      lc.setLed( display, 2+x, 1+y,  1 );
      lc.setLed( display, 3+x, 1+y,  1 );
      break;

    case 2:
      lc.setLed( display, 1+x, 7+y,  1 );
      lc.setLed( display, 2+x, 7+y,  1 );
      lc.setLed( display, 0+x, 6+y,  1 );
      lc.setLed( display, 3+x, 6+y,  1 );
      lc.setLed( display, 3+x, 5+y,  1 );
      lc.setLed( display, 2+x, 4+y,  1 );
      lc.setLed( display, 1+x, 3+y,  1 );
      lc.setLed( display, 0+x, 2+y,  1 );
      lc.setLed( display, 0+x, 1+y,  1 );
      lc.setLed( display, 1+x, 1+y,  1 );
      lc.setLed( display, 2+x, 1+y,  1 );
      lc.setLed( display, 3+x, 1+y,  1 );
      break;

    case 3:
      lc.setLed( display, 1+x, 7+y,  1 );
      lc.setLed( display, 2+x, 7+y,  1 );
      lc.setLed( display, 0+x, 6+y,  1 );
      lc.setLed( display, 3+x, 6+y,  1 );
      lc.setLed( display, 3+x, 5+y,  1 );
      lc.setLed( display, 2+x, 4+y,  1 );
      lc.setLed( display, 1+x, 4+y,  1 );
      lc.setLed( display, 3+x, 3+y,  1 );
      lc.setLed( display, 0+x, 2+y,  1 );
      lc.setLed( display, 3+x, 2+y,  1 );
      lc.setLed( display, 1+x, 1+y,  1 );
      lc.setLed( display, 2+x, 1+y,  1 );
      break;

    case 4:
      lc.setLed( display, 0+x, 7+y,  1 );
      lc.setLed( display, 3+x, 7+y,  1 );
      lc.setLed( display, 0+x, 6+y,  1 );
      lc.setLed( display, 3+x, 6+y,  1 );
      lc.setLed( display, 0+x, 5+y,  1 );
      lc.setLed( display, 3+x, 5+y,  1 );
      lc.setLed( display, 0+x, 4+y,  1 );
      lc.setLed( display, 1+x, 4+y,  1 );
      lc.setLed( display, 2+x, 4+y,  1 );
      lc.setLed( display, 3+x, 4+y,  1 );
      lc.setLed( display, 3+x, 3+y,  1 );
      lc.setLed( display, 3+x, 2+y,  1 );
      lc.setLed( display, 3+x, 1+y,  1 );
      break;

    case 5:
      lc.setLed( display, 0+x, 7+y,  1 );
      lc.setLed( display, 1+x, 7+y,  1 );
      lc.setLed( display, 2+x, 7+y,  1 );
      lc.setLed( display, 3+x, 7+y,  1 );
      lc.setLed( display, 0+x, 6+y,  1 );
      lc.setLed( display, 0+x, 5+y,  1 );
      lc.setLed( display, 0+x, 4+y,  1 );
      lc.setLed( display, 1+x, 4+y,  1 );
      lc.setLed( display, 2+x, 4+y,  1 );
      lc.setLed( display, 3+x, 3+y,  1 );
      lc.setLed( display, 3+x, 2+y,  1 );
      lc.setLed( display, 0+x, 1+y,  1 );
      lc.setLed( display, 1+x, 1+y,  1 );
      lc.setLed( display, 2+x, 1+y,  1 );
      break;

    case 6:
      lc.setLed( display, 1+x, 7+y,  1 );
      lc.setLed( display, 2+x, 7+y,  1 );
      lc.setLed( display, 0+x, 6+y,  1 );
      lc.setLed( display, 0+x, 5+y,  1 );
      lc.setLed( display, 0+x, 4+y,  1 );
      lc.setLed( display, 1+x, 4+y,  1 );
      lc.setLed( display, 2+x, 4+y,  1 );
      lc.setLed( display, 0+x, 3+y,  1 );
      lc.setLed( display, 3+x, 3+y,  1 );
      lc.setLed( display, 0+x, 2+y,  1 );
      lc.setLed( display, 3+x, 2+y,  1 );
      lc.setLed( display, 1+x, 1+y,  1 );
      lc.setLed( display, 2+x, 1+y,  1 );
      break;

    case 7:
      lc.setLed( display, 0+x, 7+y,  1 );
      lc.setLed( display, 1+x, 7+y,  1 );
      lc.setLed( display, 2+x, 7+y,  1 );
      lc.setLed( display, 3+x, 7+y,  1 );
      lc.setLed( display, 3+x, 6+y,  1 );
      lc.setLed( display, 3+x, 5+y,  1 );
      lc.setLed( display, 2+x, 4+y,  1 );
      lc.setLed( display, 1+x, 3+y,  1 );
      lc.setLed( display, 1+x, 2+y,  1 );
      lc.setLed( display, 1+x, 1+y,  1 );
      break;

    case 8:
      lc.setLed( display, 1+x, 7+y,  1 );
      lc.setLed( display, 2+x, 7+y,  1 );
      lc.setLed( display, 0+x, 6+y,  1 );
      lc.setLed( display, 3+x, 6+y,  1 );
      lc.setLed( display, 0+x, 5+y,  1 );
      lc.setLed( display, 3+x, 5+y,  1 );
      lc.setLed( display, 1+x, 4+y,  1 );
      lc.setLed( display, 2+x, 4+y,  1 );
      lc.setLed( display, 0+x, 3+y,  1 );
      lc.setLed( display, 3+x, 3+y,  1 );
      lc.setLed( display, 0+x, 2+y,  1 );
      lc.setLed( display, 3+x, 2+y,  1 );
      lc.setLed( display, 1+x, 1+y,  1 );
      lc.setLed( display, 2+x, 1+y,  1 );
      break;

    case 9:
      lc.setLed( display, 1+x, 7+y,  1 );
      lc.setLed( display, 2+x, 7+y,  1 );
      lc.setLed( display, 0+x, 6+y,  1 );
      lc.setLed( display, 3+x, 6+y,  1 );
      lc.setLed( display, 0+x, 5+y,  1 );
      lc.setLed( display, 3+x, 5+y,  1 );
      lc.setLed( display, 1+x, 4+y,  1 );
      lc.setLed( display, 2+x, 4+y,  1 );
      lc.setLed( display, 3+x, 4+y,  1 );
      lc.setLed( display, 3+x, 3+y,  1 );
      lc.setLed( display, 2+x, 2+y,  1 );
      lc.setLed( display, 1+x, 1+y,  1 );
      break;
        // minus sign (-)
    case 10:
      lc.setLed( display, 1+x, 3+y, 1);
      lc.setLed( display, 2+x, 3+y, 1);
      lc.setLed( display, 3+x, 3+y, 1);
      lc.setLed( display, 4+x, 3+y, 1);
      lc.setLed( display, 5+x, 3+y, 1);  
      lc.setLed( display, 6+x, 3+y, 1);
    
      lc.setLed( display, 1+x, 4+y, 1);
      lc.setLed( display, 2+x, 4+y, 1);
      lc.setLed( display, 3+x, 4+y, 1);
      lc.setLed( display, 4+x, 4+y, 1);
      lc.setLed( display, 5+x, 4+y, 1);
      lc.setLed( display, 6+x, 4+y, 1);
      break;
    // plus sign (+)
    case 11:
      lc.setLed( display, 1+x, 3+y, 1);
      lc.setLed( display, 2+x, 3+y, 1);
      lc.setLed( display, 3+x, 3+y, 1);
      lc.setLed( display, 4+x, 3+y, 1);
      lc.setLed( display, 5+x, 3+y, 1);  
      lc.setLed( display, 6+x, 3+y, 1);
    
      lc.setLed( display, 1+x, 4+y, 1);
      lc.setLed( display, 2+x, 4+y, 1);
      lc.setLed( display, 3+x, 4+y, 1);
      lc.setLed( display, 4+x, 4+y, 1);
      lc.setLed( display, 5+x, 4+y, 1);
      lc.setLed( display, 6+x, 4+y, 1);

      lc.setLed( display, 3+x, 6+y, 1);
      lc.setLed( display, 3+x, 5+y, 1);
      lc.setLed( display, 3+x, 2+y, 1);
      lc.setLed( display, 3+x, 1+y, 1);
      lc.setLed( display, 4+x, 6+y, 1);
      lc.setLed( display, 4+x, 5+y, 1);
      lc.setLed( display, 4+x, 2+y, 1);
      lc.setLed( display, 4+x, 1+y, 1);

      break;
    default:
      break;
  }
}

