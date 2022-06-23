//We always have to include the library
#include "LedControl.h"

/*
 Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
 pin 2 is connected to the DataIn 
 pin 4 is connected to the CLK 
 pin 5 is connected to LOAD/CS 
 ***** Please set the number of devices you have *****
 But the maximum default of 8 MAX72XX wil also work.
 */
 void drawDigit(int digit, int x, int y, int display);
 //void drawDigit2(int digit, int x, int y, int display);

LedControl lc=LedControl(2,4,5,13);
//LedControl lc2=LedControl(2,4,5,5);

/* we always wait a bit between updates of the display */
unsigned long delaytime=500;

/* 
 This time we have more than one device. 
 But all of them have to be initialized 
 individually.
 */
void setup() {
  //we have already set the number of devices when we created the LedControl
  //int devices=lc.getDeviceCount();
  //we have to init all devices in a loop
  for(int address=0;address<13;address++) {
    /*The MAX72XX is in power-saving mode on startup*/
    lc.shutdown(address,false);
    /* Set the brightness to a medium values */
    lc.setIntensity(address,8);
    /* and clear the display */
    lc.clearDisplay(address);
  }
  //     for(int address=0;address<5;address++) {
  //   /*The MAX72XX is in power-saving mode on startup*/
  //   lc2.shutdown(address,false);
  //   /* Set the brightness to a medium values */
  //   lc2.setIntensity(address,8);
  //   /* and clear the display */
  //   lc2.clearDisplay(address);
  // }
}

void loop() { 
  //read the number cascaded devices
  //int devices=lc.getDeviceCount();

  for(int i = 0; i< 9; i++)
  {
    drawDigit(i+1, 2, -1, i);
  } 
        
  drawDigit(10, 0,0,9);
  drawDigit(11,0,0,10); 
  drawDigit(1, 2,-1,11);
  drawDigit(2,2,-1,12); 
  // for(int i = 0; i< 5; i++)
  // {
  //   drawDigit2(i+9, 2, -1, i+8);
  // }
  

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

// void drawDigit2(int digit, int x, int y, int display)
// {
//   switch (digit)
//   {
//     case 0:
//       lc2.setLed( display, 1+x, 7+y,  1 );
//       lc2.setLed( display, 2+x, 7+y,  1 );
//       lc2.setLed( display, 0+x, 6+y,  1 );
//       lc2.setLed( display, 3+x, 6+y,  1 );
//       lc2.setLed( display, 0+x, 5+y,  1 );
//       lc2.setLed( display, 3+x, 5+y,  1 );
//       lc2.setLed( display, 0+x, 4+y,  1 );
//       lc2.setLed( display, 3+x, 4+y,  1 );
//       lc2.setLed( display, 0+x, 3+y,  1 );
//       lc2.setLed( display, 3+x, 3+y,  1 );
//       lc2.setLed( display, 0+x, 2+y,  1 );
//       lc2.setLed( display, 3+x, 2+y,  1 );
//       lc2.setLed( display, 1+x, 1+y,  1 );
//       lc2.setLed( display, 2+x, 1+y,  1 );
//       break;

//     case 1:
//       lc2.setLed( display, 2+x, 7+y,  1 );
//       lc2.setLed( display, 1+x, 6+y,  1 );
//       lc2.setLed( display, 2+x, 6+y,  1 );
//       lc2.setLed( display, 2+x, 5+y,  1 );
//       lc2.setLed( display, 2+x, 4+y,  1 );
//       lc2.setLed( display, 2+x, 3+y,  1 );
//       lc2.setLed( display, 2+x, 2+y,  1 );
//       lc2.setLed( display, 1+x, 1+y,  1 );
//       lc2.setLed( display, 2+x, 1+y,  1 );
//       lc2.setLed( display, 3+x, 1+y,  1 );
//       break;

//     case 2:
//       lc2.setLed( display, 1+x, 7+y,  1 );
//       lc2.setLed( display, 2+x, 7+y,  1 );
//       lc2.setLed( display, 0+x, 6+y,  1 );
//       lc2.setLed( display, 3+x, 6+y,  1 );
//       lc2.setLed( display, 3+x, 5+y,  1 );
//       lc2.setLed( display, 2+x, 4+y,  1 );
//       lc2.setLed( display, 1+x, 3+y,  1 );
//       lc2.setLed( display, 0+x, 2+y,  1 );
//       lc2.setLed( display, 0+x, 1+y,  1 );
//       lc2.setLed( display, 1+x, 1+y,  1 );
//       lc2.setLed( display, 2+x, 1+y,  1 );
//       lc2.setLed( display, 3+x, 1+y,  1 );
//       break;

//     case 3:
//       lc2.setLed( display, 1+x, 7+y,  1 );
//       lc2.setLed( display, 2+x, 7+y,  1 );
//       lc2.setLed( display, 0+x, 6+y,  1 );
//       lc2.setLed( display, 3+x, 6+y,  1 );
//       lc2.setLed( display, 3+x, 5+y,  1 );
//       lc2.setLed( display, 2+x, 4+y,  1 );
//       lc2.setLed( display, 1+x, 4+y,  1 );
//       lc2.setLed( display, 3+x, 3+y,  1 );
//       lc2.setLed( display, 0+x, 2+y,  1 );
//       lc2.setLed( display, 3+x, 2+y,  1 );
//       lc2.setLed( display, 1+x, 1+y,  1 );
//       lc2.setLed( display, 2+x, 1+y,  1 );
//       break;

//     case 4:
//       lc2.setLed( display, 0+x, 7+y,  1 );
//       lc2.setLed( display, 3+x, 7+y,  1 );
//       lc2.setLed( display, 0+x, 6+y,  1 );
//       lc2.setLed( display, 3+x, 6+y,  1 );
//       lc2.setLed( display, 0+x, 5+y,  1 );
//       lc2.setLed( display, 3+x, 5+y,  1 );
//       lc2.setLed( display, 0+x, 4+y,  1 );
//       lc2.setLed( display, 1+x, 4+y,  1 );
//       lc2.setLed( display, 2+x, 4+y,  1 );
//       lc2.setLed( display, 3+x, 4+y,  1 );
//       lc2.setLed( display, 3+x, 3+y,  1 );
//       lc2.setLed( display, 3+x, 2+y,  1 );
//       lc2.setLed( display, 3+x, 1+y,  1 );
//       break;

//     case 5:
//       lc2.setLed( display, 0+x, 7+y,  1 );
//       lc2.setLed( display, 1+x, 7+y,  1 );
//       lc2.setLed( display, 2+x, 7+y,  1 );
//       lc2.setLed( display, 3+x, 7+y,  1 );
//       lc2.setLed( display, 0+x, 6+y,  1 );
//       lc2.setLed( display, 0+x, 5+y,  1 );
//       lc2.setLed( display, 0+x, 4+y,  1 );
//       lc2.setLed( display, 1+x, 4+y,  1 );
//       lc2.setLed( display, 2+x, 4+y,  1 );
//       lc2.setLed( display, 3+x, 3+y,  1 );
//       lc2.setLed( display, 3+x, 2+y,  1 );
//       lc2.setLed( display, 0+x, 1+y,  1 );
//       lc2.setLed( display, 1+x, 1+y,  1 );
//       lc2.setLed( display, 2+x, 1+y,  1 );
//       break;

//     case 6:
//       lc2.setLed( display, 1+x, 7+y,  1 );
//       lc2.setLed( display, 2+x, 7+y,  1 );
//       lc2.setLed( display, 0+x, 6+y,  1 );
//       lc2.setLed( display, 0+x, 5+y,  1 );
//       lc2.setLed( display, 0+x, 4+y,  1 );
//       lc2.setLed( display, 1+x, 4+y,  1 );
//       lc2.setLed( display, 2+x, 4+y,  1 );
//       lc2.setLed( display, 0+x, 3+y,  1 );
//       lc2.setLed( display, 3+x, 3+y,  1 );
//       lc2.setLed( display, 0+x, 2+y,  1 );
//       lc2.setLed( display, 3+x, 2+y,  1 );
//       lc2.setLed( display, 1+x, 1+y,  1 );
//       lc2.setLed( display, 2+x, 1+y,  1 );
//       break;

//     case 7:
//       lc2.setLed( display, 0+x, 7+y,  1 );
//       lc2.setLed( display, 1+x, 7+y,  1 );
//       lc2.setLed( display, 2+x, 7+y,  1 );
//       lc2.setLed( display, 3+x, 7+y,  1 );
//       lc2.setLed( display, 3+x, 6+y,  1 );
//       lc2.setLed( display, 3+x, 5+y,  1 );
//       lc2.setLed( display, 2+x, 4+y,  1 );
//       lc2.setLed( display, 1+x, 3+y,  1 );
//       lc2.setLed( display, 1+x, 2+y,  1 );
//       lc2.setLed( display, 1+x, 1+y,  1 );
//       break;

//     case 8:
//       lc2.setLed( display, 1+x, 7+y,  1 );
//       lc2.setLed( display, 2+x, 7+y,  1 );
//       lc2.setLed( display, 0+x, 6+y,  1 );
//       lc2.setLed( display, 3+x, 6+y,  1 );
//       lc2.setLed( display, 0+x, 5+y,  1 );
//       lc2.setLed( display, 3+x, 5+y,  1 );
//       lc2.setLed( display, 1+x, 4+y,  1 );
//       lc2.setLed( display, 2+x, 4+y,  1 );
//       lc2.setLed( display, 0+x, 3+y,  1 );
//       lc2.setLed( display, 3+x, 3+y,  1 );
//       lc2.setLed( display, 0+x, 2+y,  1 );
//       lc2.setLed( display, 3+x, 2+y,  1 );
//       lc2.setLed( display, 1+x, 1+y,  1 );
//       lc2.setLed( display, 2+x, 1+y,  1 );
//       break;

//     case 9:
//       lc2.setLed( display, 1+x, 7+y,  1 );
//       lc2.setLed( display, 2+x, 7+y,  1 );
//       lc2.setLed( display, 0+x, 6+y,  1 );
//       lc2.setLed( display, 3+x, 6+y,  1 );
//       lc2.setLed( display, 0+x, 5+y,  1 );
//       lc2.setLed( display, 3+x, 5+y,  1 );
//       lc2.setLed( display, 1+x, 4+y,  1 );
//       lc2.setLed( display, 2+x, 4+y,  1 );
//       lc2.setLed( display, 3+x, 4+y,  1 );
//       lc2.setLed( display, 3+x, 3+y,  1 );
//       lc2.setLed( display, 2+x, 2+y,  1 );
//       lc2.setLed( display, 1+x, 1+y,  1 );
//       break;

//     // minus sign (-)
//     case 10:
//       lc2.setLed( display, 1+x, 3+y, 1);
//       lc2.setLed( display, 2+x, 3+y, 1);
//       lc2.setLed( display, 3+x, 3+y, 1);
//       lc2.setLed( display, 4+x, 3+y, 1);
//       lc2.setLed( display, 5+x, 3+y, 1);  
//       lc2.setLed( display, 6+x, 3+y, 1);
    
//       lc2.setLed( display, 1+x, 3+y, 1);
//       lc2.setLed( display, 2+x, 4+y, 1);
//       lc2.setLed( display, 3+x, 4+y, 1);
//       lc2.setLed( display, 4+x, 4+y, 1);
//       lc2.setLed( display, 5+x, 4+y, 1);
//       lc2.setLed( display, 6+x, 3+y, 1);
//       break;
//     // plus sign (+)
//     case 11:
//       lc2.setLed( display, 1+x, 3+y, 1);
//       lc2.setLed( display, 2+x, 3+y, 1);
//       lc2.setLed( display, 3+x, 3+y, 1);
//       lc2.setLed( display, 4+x, 3+y, 1);
//       lc2.setLed( display, 5+x, 3+y, 1);  
//       lc2.setLed( display, 6+x, 3+y, 1);
    
//       lc2.setLed( display, 1+x, 3+y, 1);
//       lc2.setLed( display, 2+x, 4+y, 1);
//       lc2.setLed( display, 3+x, 4+y, 1);
//       lc2.setLed( display, 4+x, 4+y, 1);
//       lc2.setLed( display, 5+x, 4+y, 1);
//       lc2.setLed( display, 6+x, 3+y, 1);

//       lc2.setLed( display, 3+x, 6+y, 1);
//       lc2.setLed( display, 3+x, 5+y, 1);
//       lc2.setLed( display, 3+x, 2+y, 1);
//       lc2.setLed( display, 3+x, 1+y, 1);
//       lc2.setLed( display, 4+x, 6+y, 1);
//       lc2.setLed( display, 4+x, 5+y, 1);
//       lc2.setLed( display, 4+x, 2+y, 1);
//       lc2.setLed( display, 4+x, 1+y, 1);

//       break;

//     default:
//       break;
//   }
// }