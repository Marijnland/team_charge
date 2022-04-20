int clockPin = 12;
int latchPin = 8;
int dataPin = 11;
byte leds= 0;

void setup() 
{
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
}

void loop() 
{



  for (int i = 0; i<3; i++)
  {
    digitalWrite(latchPin, LOW);
    digitalWrite(dataPin, 1);
    digitalWrite(clockPin, HIGH);
    digitalWrite(clockPin, LOW);
    digitalWrite(latchPin, HIGH);
    delay(40);
  }

  for (int i = 0; i<13; i++)
  {
    digitalWrite(latchPin, LOW);
    digitalWrite(dataPin, 0);
    digitalWrite(clockPin, HIGH);
    digitalWrite(clockPin, LOW);
    digitalWrite(latchPin, HIGH);
    delay(40);
  }

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