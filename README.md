# Patchugino_PT100
Arduino library for the Patchugino_PT100 shield board

## Getting Started
This library allows to control the Patchugino_PT100 shield board which can be mounted on top of a PatchugoLite board. It is therefore necessary to have
the Patchugo Boards package installed from [Arduino Boards Manager](https://docs.arduino.cc/learn/starting-guide/cores/). 

If you have not done that already, add this link in the "_Additional Boards Managers URLs_" in Arduino preferences:

https://github.com/Innuvatech/BoardManagerFiles/raw/main/package_innuvatech_index.json

## Board Description
The Patchugino_PT100 board is a shield board that can be plugged on top of a PatchugoLite board. It allows to control up to 2 PT100 sensors of any type with SPI by configuring the board
correctly with jumpers. Up to 2 PT100 boards can be used together by controlling the CS used with a jumper on H9

### Power Supply
The board can be powered either from 3.3V or from 24V.

The 3.3V configuration is the following:
  - Jumper between H14 and H15
  - Jumper between H17 and H22(pin 2)

 The 24V configuration is the following:
   - Jumper on H22 pins

An image of the pin headers for power source is shown below:

![Power source image](https://github.com/Innuvatech/Patchugino_PT100/blob/rev_0/assets/PT100_PWR_SRC.png)

### Sensor connections
The board has 2 connectors(CN1 and CN3) to which any type of PT100 sensor can be plugged. Depending on the type of the type of the sensor
some jumpers need to be applied or not in order for the board to work correctly. Below the full list of possible configurations is provided

### 2Wire Connected to CN1
  - Jumper on H20 and H21
  - Jumper on H1 to PGND
  - PT100 Wires to RTDIN1+ and RTDIN1-

### 2Wire Connected to CN3
  - Jumper on H18 and H19
  - Jumper on H2 to PGND
  - PT100 Wires to RTDIN0+ and RTDIN0-

### 3Wire Connected to CN1
  - Jumper on H21
  - Jumper on  H1 to FORCE1+
  - PT100 Wires to FORCE1+ RTDIN1+ and RTDIN1-

### 3Wire Connected to CN3
  - Jumper on H19
  - Jumper on H2 to FORCE0+
  - PT100 Wires to FORCE0+ RTDIN0+ and RTDIN0-

### 4Wire Connected to CN1
  - No jumpers on H20 and H21
  - Jumper on H1 to PGND
  - PT100 Wires to CN1

### 4Wire Connected to CN3
  - No jumpers on H18 and H18
  - Jumper on H2 to PGND
  - PT100Wires to CN3

## Library Usage
The arduino library allows to control the board in a really simple and intuitive way with just a few lines of code. It allows to initialize the board by specifying which CS is being used from H9.
It allows to configure which PT100 type is being used on CN1 and CN3 connectors and it allows to read any type of PT100.

### Initialization
The library provides and Initialization function called **Init** that allows to initialize everything that the board needs in order to work. The function takes the following parameters as input:
  -  **cs**: The CS that is selected on H9 connector(CS0 or CS1). There are 2 defines for values assignable to this parameter:
      -  **PT100_CS_0** Specifies that CS0 is being used as SPI CS
      -  **PT100_CS_1** Specifies that CS1 is being used as SPI CS
  -   **serial(optional)**: This is an optional parameter. It specifies the Serial instance used by the internal logs of the library. If not provided this parameter defaults to the default Serial instance of the                   PatchugoLite board
  -   **logLevel(optional)**: This specifies the logging level of the library. Setting a higher logging level means more logs from the library will be shown. Logs from the library can be disabled by setting this to                   **LOG_LEVEL_NONE**. For more information about logging please consult the [Patchugo_Core](https://github.com/Innuvatech/Patchugo_Core) repository

Examples of initialization are provided below:

#### Minimal initialization

```
  /*
    IMPORTANT!!! Patchugino PT100 library needs
    Serial instance to be initialized before calling any function!
  */
  Serial.begin(115200);

  //Initialize the PT100 shield board and specify which CS it's using(CS0 in this case)
  //Since serial and logLevel are not specified this will default to using Serial with LOG_LEVEL_VERBOSE
  patchuginoPt100.Init(PT100_CS_0);
```

#### Custom logging initialization
```
  /*
    IMPORTANT!!! Patchugino PT100 library needs
    Serial instance to be initialized before calling any function!
  */
  HardwareSerial mySerial(PA10, PA11);
  
  //Initialize the PT100 shield board and specify which CS it's using(CS0 in this case)
  //This will use mySerial as logs output channel and will only show DEBUG level logs or lower
  patchuginoPt100.Init(PT100_CS_0, mySerial, LOG_LEVEL_DEBUG);
```
#### No logging initialization
```
void setup() {
  /*
    IMPORTANT!!! Patchugino PT100 library needs
    Serial instance to be initialized before calling any function!
  */
  Serial.begin(115200);
  
  //Initialize the PT100 shield board and specify which CS it's using(CS0 in this case)
  //This will disable logs of the library. A valid Serial instance still needs to be provided
  patchuginoPt100.Init(PT100_CS_0, Serial, LOG_LEVEL_NONE);
```

### Configuration
  The library offers a confgiguration function called **Configure** that can be called after Initialization to specify the type of PT100 that is wired to the CN3 and CN1 connectors. This function allows
  to configure the board to work with 2 different types of PT100 sensors wired to the connectors. 
  The Configure function takes the following parameters:
  - pt100N: Which PT100 is being configured. There are 2 defines assignable to this parameter:
    - **PT100_N_0**: This refers to a PT100 wired to the CN3 connector
    - **PT100_N_1**: This refers to a PT100 wired to the CN1 connector
  - pt100Type: The type of PT100 that's been wired. There are 3 defines assignable to this parameter:
    - **PT100_2WIRE**: 2 Wire PT100
    - **PT100_3WIRE**: 3 Wire PT100
    - **PT100_4WIRE**: 4 Wire PT100
  
  An example is provided below:
  ```
    //Configure library to use PT100_N_0(CN3) as 2WIRE
    patchuginoPt100.Configure(PT100_N_0, PT100_2WIRE);
  
    //Configure library to use PT100_N_1(CN0) as 3WIRE
    patchuginoPt100.Configure(PT100_N_1, PT100_3WIRE);
  ```

### Reading
  This library offers a simple reading function to read the temperature from any type of PT100. The reading function is called **Read** and it returns a floating point value representing the temperature in °C.
  The read function takes the following parameters:
    - pt100N: Which PT100 is being read. This is the same as the Configure function.

  An example is provided below:
   ```
  //Read temperature from PT100_N_0 and prints it
  float temp = patchuginoPt100.Read(PT100_N_0);
  Serial.print("SENSOR 1: ");
  Serial.println(temp);
  delay(500);

  //Read temperature from PT100_N_1 and prints it
  float temp2 = patchuginoPt100.Read(PT100_N_1);
  Serial.print("SENSOR 2: ");
  Serial.println(temp2);
  ```

## Full library example
```
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
  //This will disable logs of the library. A valid Serial instance still needs to be provided
  patchuginoPt100.Init(PT100_CS_0, Serial, LOG_LEVEL_NONE);

  //Configure library to use PT100_N_0(CN3) as 2WIRE
  patchuginoPt100.Configure(PT100_N_0, PT100_2WIRE);

  //Configure library to use PT100_N_1(CN0) as 3WIRE
  patchuginoPt100.Configure(PT100_N_1, PT100_3WIRE);

}

void loop() {
  
  //Read temperature from PT100_N_0 and prints it
  float temp = patchuginoPt100.Read(PT100_N_0);
  Serial.print("SENSOR 1: ");
  Serial.println(temp);
  delay(500);

  //Read temperature from PT100_N_1 and prints it
  float temp2 = patchuginoPt100.Read(PT100_N_1);
  Serial.print("SENSOR 2: ");
  Serial.println(temp2);
  delay(2000);

}
```
