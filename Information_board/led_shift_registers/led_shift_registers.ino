int dataPin = 0;
int latchPin = 15;
int clockPin = 13;
byte leds= 0;

void setup() 
{
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
}

void loop() 
{

// while(1)
// {
//   leds = 0b11111111;
//   updateShiftRegisterR();
//   delay(1000);
//   leds = 0b00000000;
//   updateShiftRegisterR();
//   delay(1000);

// }
  for (int i = 0; i<3; i++)
  {
    digitalWrite(latchPin, LOW);
    digitalWrite(dataPin, 1);
    digitalWrite(clockPin, HIGH);
    digitalWrite(clockPin, LOW);
    digitalWrite(latchPin, HIGH);
    delay(150);
  }

  for (int i = 0; i<30; i++)
  {
    digitalWrite(latchPin, LOW);
    digitalWrite(dataPin, 0);
    digitalWrite(clockPin, HIGH);
    digitalWrite(clockPin, LOW);
    digitalWrite(latchPin, HIGH);
    delay(150);
  }

  //delay(1000000);

}

void updateShiftRegisterL()
{
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, leds);
  digitalWrite(latchPin, HIGH);
}

void updateShiftRegisterR()
{
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, leds);
  digitalWrite(latchPin, HIGH);
}