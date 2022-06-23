int dataPin = 11; //0
int latchPin = 12; //15
int clockPin = 13; //13

byte leds = 0;
bool pv[33];

void setup() 
{
  Serial.begin(115200);
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);

  for(int i=0;i<33; i++)
  pv[i] = false;


}

void loop() 
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

// while(1)
// {
//   leds = 0b11111111;
//   updateShiftRegisterR();
//   delay(1000);
//   leds = 0b00000000;
//   updateShiftRegisterR();
//   delay(1000);

// }
  // for (int i = 0; i<3; i++)
  // {
  //   digitalWrite(latchPin, LOW);
  //   digitalWrite(dataPin, 1);
  //   digitalWrite(clockPin, HIGH);
  //   digitalWrite(clockPin, LOW);
  //   digitalWrite(latchPin, HIGH);
  //   delay(150);
  // }

  // for (int i = 0; i<10; i++)
  // {
  //   digitalWrite(latchPin, LOW);
  //   digitalWrite(dataPin, 0);
  //   digitalWrite(clockPin, HIGH);
  //   digitalWrite(clockPin, LOW);
  //   digitalWrite(latchPin, HIGH);
  //   delay(150);
  // }
  // for(int i=0; i<11; i++)
  // {
  // pv[0] = 0b11100000;
  // pv[1] = 0b00011000;
  // pv[2] = 0b00000010;
  // pv[3] = 0b00000000;
  // pv[4] = 0b00000000;
  
  // pv[4] = pv[3] << 7 | pv[4] >> 1;
  // pv[3] = pv[2] << 7 | pv[3] >> 1;
  // pv[2] = pv[1] << 7 | pv[2] >> 1;
  // pv[1] = pv[0] << 7 | pv[1] >> 1;
  // pv[0] = pv[0] >> 1;

  // digitalWrite(latchPin, LOW);
  // shiftOut(dataPin, clockPin, LSBFIRST, pv[4]);
  // shiftOut(dataPin, clockPin, LSBFIRST, pv[3]);
  // shiftOut(dataPin, clockPin, LSBFIRST, pv[2]);
  // shiftOut(dataPin, clockPin, LSBFIRST, pv[1]);
  // shiftOut(dataPin, clockPin, LSBFIRST, pv[0]);
  // digitalWrite(latchPin, HIGH);
  // delay(500);
  // }

  
  

// for(int i=0; i<11; i++)
//   {
//     for(int j=0; j<33; j++)
//     {
//       if( ((j+i)%10 == 1) || ((j+i)%10 == 2) || ((j+i)%10 == 3) )
//       pv[j] = true;
//       else
//       pv[j] = false;
//     }
//     for(int k = 0; k<33; k++)
//     {
//       if(k%11 == 0)
//       {
//         Serial.println();
        
//       }
//             Serial.print(pv[k]);

//     }
  
//   Serial.println();
//   Serial.println();
//     delay(1000);
//   }

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