/*--------------------------------------------------------------------------------------

 dmd_test.cpp 
   Demo and example project for the Freetronics DMD, a 512 LED matrix display
   panel arranged in a 32 x 16 layout.

 Copyright (C) 2011 Marc Alexander (info <at> freetronics <dot> com)

 See http://www.freetronics.com/dmd for resources and a getting started guide.

 Note that the DMD library uses the SPI port for the fastest, low overhead writing to the
 display. Keep an eye on conflicts if there are any other devices running from the same
 SPI port, and that the chip select on those devices is correctly set to be inactive
 when the DMD is being written to.

 USAGE NOTES
 -----------

 - Place the DMD library folder into the "arduino/libraries/" folder of your Arduino installation.
 - Get the TimerOne library from here: http://code.google.com/p/arduino-timerone/downloads/list
   or download the local copy from the DMD library page (which may be older but was used for this creation)
   and place the TimerOne library folder into the "arduino/libraries/" folder of your Arduino installation.
 - Restart the IDE.
 - In the Arduino IDE, you can open File > Examples > DMD > dmd_demo, or dmd_clock_readout, and get it
   running straight away!

 * The DMD comes with a pre-made data cable and DMDCON connector board so you can plug-and-play straight
   into any regular size Arduino Board (Uno, Freetronics Eleven, EtherTen, USBDroid, etc)
  
 * Please note that the Mega boards have SPI on different pins, so this library does not currently support
   the DMDCON connector board for direct connection to Mega's, please jumper the DMDCON pins to the
   matching SPI pins on the other header on the Mega boards.

 This example code is in the public domain.
 The DMD library is open source (GPL), for more see DMD.cpp and DMD.h

--------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------
  Includes
--------------------------------------------------------------------------------------*/
#include <SPI.h>        //SPI.h must be included as DMD is written by SPI (the IDE complains otherwise)
#include <DMD.h>        //
#include <TimerOne.h>   //
#include "SystemFont5x7.h"
#include "Arial_black_16.h"

//Fire up the DMD library as dmd
#define DISPLAYS_ACROSS 1
#define DISPLAYS_DOWN 1
DMD dmd(DISPLAYS_ACROSS, DISPLAYS_DOWN);

void drawDigit(int digit, int x, int y);

/*--------------------------------------------------------------------------------------
  Interrupt handler for Timer1 (TimerOne) driven DMD refresh scanning, this gets
  called at the period set in Timer1.initialize();
--------------------------------------------------------------------------------------*/
void ScanDMD()
{ 
  dmd.scanDisplayBySPI();
}

/*--------------------------------------------------------------------------------------
  setup
  Called by the Arduino architecture before the main loop begins
--------------------------------------------------------------------------------------*/
void setup(void)
{

   //initialize TimerOne's interrupt/CPU usage used to scan and refresh the display
   Timer1.initialize( 5000 );           //period in microseconds to call ScanDMD. Anything longer than 5000 (5ms) and you can see flicker.
   Timer1.attachInterrupt( ScanDMD );   //attach the Timer1 interrupt to ScanDMD which goes to dmd.scanDisplayBySPI()

   //clear/init the DMD pixels held in RAM
   dmd.clearScreen( true );   //true is normal (all pixels off), false is negative (all pixels on)

}

/*--------------------------------------------------------------------------------------
  loop
  Arduino architecture main loop
--------------------------------------------------------------------------------------*/
void loop(void)
{
   
  //dmd.selectFont(Arial_Black_16);
  //dmd.selectFont(SystemFont5x7);
  
  //32x16 pixels

  dmd.clearScreen( true );
  drawDigit(0,0,0);
  drawDigit(1,5,0);
  drawDigit(2,10,0);
  drawDigit(3,15,0);
  drawDigit(4,20,0);
    
  delay(5000);
  
  dmd.clearScreen( true );
  drawDigit(5,0,8);
  drawDigit(6,5,8);
  drawDigit(7,10,8);
  drawDigit(8,15,8);
  drawDigit(9,20,8);
  
  delay(5000);
    

  // for(int i =0; i<512; i++)
  // {
  //   dmd.writePixel( i%32, i/32, GRAPHICS_NORMAL, 1 );
  //   delay(50);
  // }

   


   
}

void drawDigit(int digit, int x, int y)
{
  switch (digit)
  {
    case 0:
      dmd.writePixel( 1+x, 0+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 2+x, 0+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 0+x, 1+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 3+x, 1+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 0+x, 2+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 3+x, 2+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 0+x, 3+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 3+x, 3+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 0+x, 4+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 3+x, 4+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 0+x, 5+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 3+x, 5+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 1+x, 6+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 2+x, 6+y, GRAPHICS_NORMAL, 1 );
      break;

    case 1:
      dmd.writePixel( 2+x, 0+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 1+x, 1+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 2+x, 1+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 2+x, 2+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 2+x, 3+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 2+x, 4+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 2+x, 5+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 1+x, 6+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 2+x, 6+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 3+x, 6+y, GRAPHICS_NORMAL, 1 );
      break;

    case 2:
      dmd.writePixel( 1+x, 0+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 2+x, 0+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 0+x, 1+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 3+x, 1+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 3+x, 2+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 2+x, 3+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 1+x, 4+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 0+x, 5+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 0+x, 6+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 1+x, 6+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 2+x, 6+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 3+x, 6+y, GRAPHICS_NORMAL, 1 );
      break;

    case 3:
      dmd.writePixel( 1+x, 0+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 2+x, 0+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 0+x, 1+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 3+x, 1+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 3+x, 2+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 2+x, 3+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 1+x, 3+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 3+x, 4+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 0+x, 5+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 3+x, 5+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 1+x, 6+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 2+x, 6+y, GRAPHICS_NORMAL, 1 );
      break;

    case 4:
      dmd.writePixel( 0+x, 0+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 3+x, 0+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 0+x, 1+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 3+x, 1+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 0+x, 2+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 3+x, 2+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 0+x, 3+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 1+x, 3+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 2+x, 3+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 3+x, 3+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 3+x, 4+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 3+x, 5+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 3+x, 6+y, GRAPHICS_NORMAL, 1 );
      break;

    case 5:
      dmd.writePixel( 0+x, 0+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 1+x, 0+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 2+x, 0+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 3+x, 0+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 0+x, 1+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 0+x, 2+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 0+x, 3+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 1+x, 3+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 2+x, 3+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 3+x, 4+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 3+x, 5+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 0+x, 6+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 1+x, 6+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 2+x, 6+y, GRAPHICS_NORMAL, 1 );
      break;

    case 6:
      dmd.writePixel( 1+x, 0+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 2+x, 0+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 0+x, 1+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 0+x, 2+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 0+x, 3+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 1+x, 3+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 2+x, 3+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 0+x, 4+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 3+x, 4+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 0+x, 5+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 3+x, 5+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 1+x, 6+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 2+x, 6+y, GRAPHICS_NORMAL, 1 );
      break;

    case 7:
      dmd.writePixel( 0+x, 0+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 1+x, 0+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 2+x, 0+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 3+x, 0+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 3+x, 1+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 3+x, 2+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 2+x, 3+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 1+x, 4+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 1+x, 5+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 1+x, 6+y, GRAPHICS_NORMAL, 1 );
      break;

    case 8:
      dmd.writePixel( 1+x, 0+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 2+x, 0+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 0+x, 1+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 3+x, 1+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 0+x, 2+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 3+x, 2+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 1+x, 3+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 2+x, 3+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 0+x, 4+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 3+x, 4+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 0+x, 5+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 3+x, 5+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 1+x, 6+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 2+x, 6+y, GRAPHICS_NORMAL, 1 );
      break;

    case 9:
      dmd.writePixel( 1+x, 0+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 2+x, 0+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 0+x, 1+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 3+x, 1+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 0+x, 2+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 3+x, 2+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 1+x, 3+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 2+x, 3+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 3+x, 3+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 3+x, 4+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 2+x, 5+y, GRAPHICS_NORMAL, 1 );
      dmd.writePixel( 1+x, 6+y, GRAPHICS_NORMAL, 1 );
      break;

    default:
      break;
  }

}

