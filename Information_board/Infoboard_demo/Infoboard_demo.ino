
#include "LedDefines.h"
#include "LedControl.h"


int car1phase, car2phase, car3phase, car4phase = 0;
int co2saved, pvpower, gridpower, gridphases = 0;

LedControl lc=LedControl(2,4,5,13);

unsigned long lastupdate = 0;
unsigned long matrixupdate = 0;

int pv_increment = 0;

int dataPin = 11;
int latchPin = 12;
int clockPin = 13;

bool pv[33];


void set_led_matrices(void);
void drawDigit(int digit, int x, int y, int display);
void update_leds();



void setup() {
  Serial.begin(115200);

  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(3, OUTPUT);

  //Set display brightness, 13 pieces
  for(int i=0;i<13;i++)
  {
      lc.shutdown(i,false);
      lc.setIntensity(i,8);
      lc.clearDisplay(i);
  }
  for(int i=0; i<8; i++)
    drawDigit(i+1, 2, -1, i);
  for(int i=0; i<5; i++)
    drawDigit(i+9, 2, -1, i);

  
  for(int i=0;i<33;i++)
    pv[i] = false;

  pvpower = 63;
  gridpower = 32;
  co2saved = 40;

  digitalWrite(1, HIGH);
  digitalWrite(3, HIGH);
  
}

void loop() {

  unsigned long now = millis();
  if(now - lastupdate > 200)
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

   digitalWrite(latchPin, LOW);
 delay(1);
  digitalWrite(dataPin, 1);
  delay(1);
  digitalWrite(clockPin, HIGH);
  delay(1);
  digitalWrite(clockPin, LOW);
  delay(1);
    digitalWrite(latchPin, HIGH);
    delay(200);
     digitalWrite(latchPin, LOW);
 delay(1);
  digitalWrite(dataPin, 1);
  delay(1);
  digitalWrite(clockPin, HIGH);
  delay(1);
  digitalWrite(clockPin, LOW);
  delay(1);
    digitalWrite(latchPin, HIGH);
    delay(200);
     digitalWrite(latchPin, LOW);
 delay(1);
  digitalWrite(dataPin, 1);
  delay(1);
  digitalWrite(clockPin, HIGH);
  delay(1);
  digitalWrite(clockPin, LOW);
  delay(1);
    digitalWrite(latchPin, HIGH);
    
delay(200);
    for(int i = 0; i<8; i++)
{
 digitalWrite(latchPin, LOW);
 delay(1);
  digitalWrite(dataPin, 0);
  delay(1);
  digitalWrite(clockPin, HIGH);
  delay(1);
  digitalWrite(clockPin, LOW);
  delay(1);
    digitalWrite(latchPin, HIGH);
    
delay(200);
}
  
  //digitalWrite(latchPin, LOW);

// for (int i=0; i<34; i++)
//   pv[i] = false;
// pv[25] = true; pv[24] = true; pv[26] = true; 
// pv[14] = true; pv[13] = true; pv[12] = true; 
// pv[2] = true; pv[1] = true; pv[0] = true;
  
  
  
//   for(int i =0; i<34; i++)
//   {
//     digitalWrite(latchPin, LOW);

//       digitalWrite(dataPin, pv[i]);
      
//       digitalWrite(clockPin, HIGH);

//       digitalWrite(clockPin, LOW);

//   digitalWrite(latchPin, HIGH);
//   }
// delay(500);

// for (int i=0; i<34; i++)
//   pv[i] = false;
//   pv[25] = true; pv[27] = true; pv[26] = true; 
// pv[14] = true; pv[13] = true; pv[15] = true; 
// pv[2] = true; pv[1] = true; pv[3] = true;
  
  
  
//   for(int i =0; i<34; i++)
//   {
//     digitalWrite(latchPin, LOW);

//       digitalWrite(dataPin, pv[i]);
      
//       digitalWrite(clockPin, HIGH);
      
//       digitalWrite(clockPin, LOW);

//   digitalWrite(latchPin, HIGH);
  
//   }
//     delay(500);

  // for(int i = 0; i<11; i++)
  // {
  //   if ((i%11 == 0) || (i%11 == 1) || (i%2 == 1))
  //     pv[i] = true;
  //   else
  //     pv[i] = false;
  //       digitalWrite(latchPin, LOW);

  //     digitalWrite(dataPin, pv[i]);
  //     delay(1);
  //     digitalWrite(clockPin, HIGH);
  //     delay(1);
  //     digitalWrite(clockPin, LOW);

  // digitalWrite(latchPin, HIGH);
  // delay(200);


  // }
  // for(int i = 0; i<33; i++)
  // Serial.print(pv[i]);
  // Serial.println();

  // pv[3] = true;

  //  for(int i=0; i<33;i++)
  //   {
  //     if(pv[i])
  //       digitalWrite(dataPin, HIGH);
  //     else
  //       digitalWrite(dataPin, LOW);
  //     delay(1);
  //     digitalWrite(clockPin, HIGH);
  //     delay(1);
  //     digitalWrite(clockPin, LOW);
  //     delay(1);
  //   }

  //     digitalWrite(latchPin, HIGH);

  // for(int i = 0; i<11; i++)
  // {
  //   if(i%11 == 0 || i%11 == 1 || i%2 == 1)
  //     pv[i] = true;
  //   else
  //     pv[i] = false;
  // }
  // for(int i = 0; i<11; i++)
  // {
  //   if(i%11 == 0 || i%11 == 1 || i%2 == 1)
  //     pv[i] = true;
  //   else
  //     pv[i] = false;
  // }
  
  // for(int i=0; i<11; i++)
  // {
  //   pv[10-i] = pv[9-1];
  //   pv[21-i] = pv[20-i];
  //   pv[32-i] = pv[31-i];
  // }

  // if(pv_increment == 0)
  // {
  //   pv[0] = true;
  // }
  // else if(pv_increment == 1)
  // {
  //   pv[0] = true;
  //   pv[11] = true;
  // }
  // else if(pv_increment == 2)
  // {
  //   pv[0] = true;
  //   pv[11] = true;
  //   pv[22] = true;
  // }
  // else if(pv_increment == 3)
  // {
  //   pv[0] = false;
  //   pv[11] = true;
  //   pv[22] = true;
  // }
  // else if(pv_increment == 4)
  // {
  //   pv[0] = false;
  //   pv[11] = false;
  //   pv[22] = true;
  // }
  // else
  // {
  //   pv[0] = false;
  //   pv[11] = false;
  //   pv[22] = false;
  // }





    // for(int i=0; i<33;i++)
    // {
    //   pv[32-i] = pv[31-i];
    // }    
    // if( ((pv_increment)%11 == 0))
    //   pv[0] = true;
    // else
    //   pv[0] = false;

    // for(int i=0; i<33;i++)
    // {
    //   digitalWrite(dataPin, pv[i]);
    //   delay(1);
    //   digitalWrite(clockPin, HIGH);
    //   delay(1);
    //   digitalWrite(clockPin, LOW);
    //   delay(1);
    // }
    // for(int j=0; j<33; j++)
    // {
    //   if( ((j+pv_increment)%10 == 1) || ((j+pv_increment)%10 == 2) || ((j+pv_increment)%10 == 3) )
    //   pv[j] = true;
    //   else
    //   pv[j] = false;
    //   digitalWrite(dataPin, pv[j]);
    //   digitalWrite(clockPin, HIGH);
    //   digitalWrite(clockPin, LOW);

    // digitalWrite(latchPin, HIGH);

    // }
  //     if(pv_increment == 1)
  //     digitalWrite(dataPin, HIGH);
  //     else
  //     digitalWrite(dataPin, LOW);
  //     delay(1);
  //     digitalWrite(clockPin, HIGH);
  //     delay(1);
  //     digitalWrite(clockPin, LOW);
  //     delay(1);
  // digitalWrite(latchPin, HIGH);
  pv_increment++;
  if (pv_increment == 11)
    pv_increment = 0;

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

