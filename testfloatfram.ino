/**************************************************************************/
/*!
    @file     FRAM_I2C_manual_mode.ino
    @author   SOSAndroid (E. Ha.)
    @license  BSD (see license.txt)

    Sketch to write & read in memory using "manual setting". This will try to write at the beginning of the memory map (1 byte) and at the end of the memory map (2 bytes).

    @section  HISTORY

    v1.0.0 - First release
  V1.1.0 - Reworked code to test wider range of the memory
  v1.1.1 - More detailed feedback to Serial + adaptation to any density + Explanation of what is going on for 16K chip.
  v1.1.2 - Compilation error fix


  A bit of mathematics,

  Example of the 16K chip : chip address translation to match the datasheet.
  write address 0x25 =>  0b 000 00100101
  write address 0x750 => 0b 111 01010000

  According to 16K device's datasheet, the I2C protocol is used the following way :
  7 bits device address + R/W bit. Device address is 1010xxx where xxx are the 3 MSB of the memory slot (out of 11 bits)
  After that device address, the 8 LSB of the memory slot are send to the bus.

  To read or write at 0x025 memory slot, the IC2 device address is 0b 1010 000 x. Which means 0x050
  To read or write at 0x750 memory slot, the IC2 device address is 0b 1010 111 x. Which means 0x057

  The second byte sent is
    To read or write at 0x025 memory slot, (0b 000 00100101 & 0x000 11111111) => 0b 000 00100101 => 0x025
    To read or write at 0x750 memory slot, (0b 111 01010000 & 0x000 11111111) => 0b 000 01010000 => 0x010

  The process (0x025 memory slot)
    wire.beginTranmission(0x50);
    Wire.write(0x25);
    ...

  The process (0x750 memory slot)
    wire.beginTranmission(0x57);
    Wire.write(0x10);
    ...

*/
/**************************************************************************/

#include <Wire.h>
#include "FRAM24CXX.h"

//Example for mamual mode

boolean wp = false; //Allows memory write
int pin = 13;


//random addresses to write from




//--------------------------- Object creation ---------------------------------------

//Creating object for FRAM chip
FRAM24CXX fram(0x50, 4);


//--------------------------- Using Setup() to run the test --------------------------

void setup() {
  float in = 11111.0101;
  float out = 0;
  uint32_t y = 12345678954;
  uint32_t yy = 0;
  Serial.begin(115200);
  while (!Serial) ; //wait until Serial ready
  Wire.begin();

  Serial.println("Starting...");
  fram.begin();
for (int i=0; i<256; i=i+4){
fram.write(i,in);
Serial.println(in,6);
fram.read(i,out);
Serial.println(out,6);
}
for (int i=256; i<512; i=i+4){
fram.write(i,y);
Serial.println(y,6);
fram.read(i,yy);
Serial.println(yy,6);
}



}

void loop() {
  // nothing to do
}
