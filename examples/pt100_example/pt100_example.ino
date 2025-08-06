#include <patchugino_pt100.h>

/**
  This example shows how to use the library for the Patchugino PT100 shield board.

  The wiring of the board that was used for this example is as follows:

  3.3V Power source:  
    - Jumper between H14 and H15
    - Jumper between H17 and H22 pin 2

  Connected 2Wire PT100 as PT100_N_0:
    - Jumper on H2 to PGND
    - Jumper on H18 and H19
    - PT100 Wires to RTDIN0+ and RTDIN0-

  Connected 3Wire PT100 as PT100_N_1:
    - Jumper on H1 to FORCE1+
    - Jumper to H20 and H21
    - PT100 Wires to FORCE1+ RTDIN1+ and RTDIN1-
*/

Patchugino_PT100 patchuginoPt100;

void setup() {
  /*
    IMPORTANT!!! Patchugino PT100 library needs
    Serial instance to be initialized before calling any function!
  */
  Serial.begin(115200);
  
  //Initialize the PT100 shield board and specify which CS it's using(CS0 in this case)
  patchuginoPt100.Init(PT100_CS_0);

  //Configure library to use PT100_N_0 as 2WIRE
  patchuginoPt100.Configure(PT100_N_0, PT100_2WIRE);

  //Configure library to use PT100_N_1 as 3WIRE
  patchuginoPt100.Configure(PT100_N_1, PT100_3WIRE);

}

void loop() {
  
  //Read temperature from PT100_N_0
  float temp = patchuginoPt100.Read(PT100_N_0);
  Serial.print("SENSOR 1: ");
  Serial.println(temp);
  delay(500);

  //Read temperature from PT100_N_1
  float temp2 = patchuginoPt100.Read(PT100_N_1);
  Serial.print("SENSOR 2: ");
  Serial.println(temp2);
  delay(2000);

}
