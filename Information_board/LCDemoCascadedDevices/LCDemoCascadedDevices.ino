//We always have to include the library
#include "LedControl.h"

/*
 Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
 pin 12 is connected to the DataIn 
 pin 11 is connected to the CLK 
 pin 10 is connected to LOAD 
 ***** Please set the number of devices you have *****
 But the maximum default of 8 MAX72XX wil also work.
 */
 void drawDigit(int digit, int x, int y, int display);

LedControl lc=LedControl(2,4,5,3);

/* we always wait a bit between updates of the display */
unsigned long delaytime=500;

/* 
 This time we have more than one device. 
 But all of them have to be initialized 
 individually.
 */
void setup() {
  //we have already set the number of devices when we created the LedControl
  int devices=lc.getDeviceCount();
  //we have to init all devices in a loop
  for(int address=0;address<devices;address++) {
    /*The MAX72XX is in power-saving mode on startup*/
    lc.shutdown(address,false);
    /* Set the brightness to a medium values */
    lc.setIntensity(0,2);
    lc.setIntensity(1,8);
    lc.setIntensity(2,15);
    /* and clear the display */
    lc.clearDisplay(address);
  }
}

void loop() { 
  //read the number cascaded devices
  int devices=lc.getDeviceCount();


  drawDigit(1,2,-1,0);
  drawDigit(2,2,-1,1);
  drawDigit(3,2,-1,2);
  while(1);
  


  //we have to init all devices in a loop
  // for(int row=0;row<8;row++) {
  //   for(int col=0;col<8;col++) {
  //     for(int address=0;address<devices;address++) {
  //       delay(delaytime);
  //       lc.setLed(address,row,col,true);
  //       delay(delaytime);
  //       lc.setLed(address,row,col,false);
  //     }
  //   }
  // }
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

    default:
      break;
  }
}