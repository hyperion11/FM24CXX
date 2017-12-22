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

if (fram.write(600,in)==11)
Serial.println("overflow" );

Serial.println(in,6);
fram.read(600,out);
Serial.println(out,6);

  



}

void loop() {
  // nothing to do
}
