# BusInOut_Arduino
`BusInOut` for controlling multiple Digital I/O (GPIO) pins on [Arduino](https://www.arduino.cc) boards. 

# What is this?
`BusInOut` is a class to **interface multiple pins** by simple software interface.  

For instance, **if you want to set HIGH/LOW on some pins**, you need to call `pinMode()` and `digitalWrite()` for each pin. 
The code will be looked like following. This is a sample to make binary output of the counter.  
In this sample, a LSB bit is on pin0 (D0) pin and MSB is on pin7 (D7).  

```cpp
// Example: multiple pins output control if 'BusInOut' is not used

void setup() {
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
}

int count	= 0;

void loop() {
  digitalWrite(0, (count >> 0) & 0x01);
  digitalWrite(1, (count >> 1) & 0x01);
  digitalWrite(2, (count >> 2) & 0x01);
  digitalWrite(3, (count >> 3) & 0x01);
  digitalWrite(4, (count >> 4) & 0x01);
  digitalWrite(5, (count >> 5) & 0x01);
  digitalWrite(6, (count >> 6) & 0x01);
  digitalWrite(7, (count >> 7) & 0x01);
  count++;
}
```
This is quite straightforward approach and simple enough but troublesome to write those many lines and keep the correct pin numbers for all bits.  
Also, if you become to need changing the pins, it may take time to changing pin numbers on each lines and check.  

This `BusInOut` solves this problem. This idea is imported from [mbed](https://os.mbed.com/handbook/BusInOut).  
The pins can be decleared as an instance, is can be managed easily.  

As it called: "BusInOut", it can do the **input** also.  

The `BusInOut` is a casual implementation to control the pins.  
It may not fast enough for applications which needs speed, because this class library calls `pinMode()` and `digitalWrite()` inside . 
In that case, try direct port access in low level control.   
However, the `BusInOut` is calling hardware abstracted API, it can run on any Arduino SDKs. It can be ported any platform without modification.  
From viewpoint of speed, the `BusInOut` is good for slow (10kHz or lower on UNO R3) pin control purpose. 

# How to use?

## Basic usage
Following is a sample of its usage.  
In this code, the `bin_out` is a instance of BusInOut. The constructor taked maximum 8 argments to specify the pins. 
Pin order is LSB to MSB. 

Just after the instance is made, the direction is configured as `INPUT`. All those pins becomes high-impedance state.  
To configure it as `OUTPUT`, call `config(OUTPUT)`. Now the pins are ready to output HIGH or LOW.  
The `INPUT` and `OUTPUT` are defined in `Arduino.h`. Same value for `pinMode()` function are used.  

In the loop, the `count` value is assigned to `bin_out`. The output can be done in this simple way.  
```cpp
#include "BusInOut.h"

BusInOut bin_out(0, 1, 2, 3, 4, 5, 6, 7);
int count = 0;

void setup() {
  bin_out.config(OUTPUT);
}

void loop() {
  bin_out = count++;
}
```

## Defining pins
If the argument for the constructor is shorter than 8, the number of bit will become narrower.  
If you want to use just 2 or 4 bits, the code will be like following sample. In any case, the left most pin will become LSB.  

Anfd if you want to skip some bits in the `BusInOut`, the unused bit can be defined by `BusInOut::nc` (nc = no connect).  
In this case, the nc bit is just skipped/ingored for output/input.  
Pin number order is not required to be in sequence, The pins can be assigned arbitraly.  

```cpp
BusInOut two_pins(2, 3);                    // for 2 pins
BusInOut four_pins(7, 5, 4, 6);             // for 4 pins, arbitraly order
BusInOut four_pins(8, 9, BusInOut::nc, 10); // for 3 pins, 3rd bit is skipped
```

## Input and output
After the instance made, it is in mode of `INPUT`. 
This is to make sure the pins does not disturb any externally connected devices by unexpected output state. 
This iswhy the `config(OUTPUT)` is required for **output**. 
Following is a sample to read multiple pins from pin2-pin9. The call of `config(INPUT)` is not necessary.  
The reading can be done by assignment from the instance to variable.  

```cpp
#include "BusInOut.h"

BusInOut bin_in(2, 3, 4, 5, 6, 7, 8, 9); // not using D0 and D1 (0 and 1) pins

void setup() {
  Serial.begin(9600);
  while (!Serial)
    ;

  bin_in.config(INPUT);  // This is not necessary
}

void loop() {
  int value;
  value = bin_in;

  Serial.println(value);
}

```

# Operation samples
## Output
Followings are code and its waveform which was captured by logic-analyzer.  
`BusInOut_test_OUTPUT.ino` is a schetch for testing output features. The code and results are shown below.  

NOTE: **Arduino UNO R3 was used** for this measurement.   

```cpp
#include "BusInOut.h"

constexpr uint8_t NC  = BusInOut::nc;

BusInOut bio0(0, 1, 2, 3, 4, 5, 6, 7);         // counter0-7
//BusInOut bio0(7, 6, 5, 4, 3, 2, 1, 0);       // counter7-0
//BusInOut bio0(7, 6, 5, NC, 3, 2, 1, 0);      // counter7-0_bit4_disabled
//BusInOut bio0(6, 5, 4);                      // counter6-4
//BusInOut bio0(8, 9, 10, 11, 12, 13, A4, A5); // counter using different pins

#define SERIAL_OUT_DISABLE

void setup() {
#ifndef SERIAL_OUT_DISABLE
  Serial.begin(9600);
  while (!Serial)
    ;

  Serial.println("Hello, BusInOUt");
  Serial.println( "\"D0\" and \"D1\" pins are disabled with \"Serial\" feature because those pins are shared");
#endif

  bio0.config(OUTPUT);
}

void loop() {
  for (int i = 0; i < 256; i++) {
    bio0 = i;
  }
}

```

In this code, several `BusInOut bio0(...)` are there but just one of them is enabled by un-comment its line.  
Next pictures show result of one of them is enabled.  

When the `BusInOut bio0(0, 1, 2, 3, 4, 5, 6, 7); // counter0-7` is enabled:  
Bit 0~7 are used to output `count` value. Bit 0 is LSB.  
Analyzer's ch0 is on D0 pin and ch7 is on D7.  
Since the bit0 is LSB, it has highest frequency (\~10kHz).  
![counter0-7.png](https://github.com/teddokano/additional_files/blob/main/BusInOut_Arduino/counter0-7.png)  

Next picture shows when `BusInOut bio0(7, 6, 5, NC, 3, 2, 1, 0); // counter7-0_bit4_disabled` is used:  
Bit 0~7 are for output `count` value. Bit 7 is LSB.  
The signals come in reversed order.  Since the 4th bit is defined as NC (BusInOut::nc), signal on this bit does not appear.  
![counter7-0_bit4_disabled.png](https://github.com/teddokano/additional_files/blob/main/BusInOut_Arduino/counter7-0_bit4_disabled.png)   

The `BusInOut bio0(6, 5, 4); // counter6-4` is enabled.  
The pins 6-4 are used for 3 bit output. Higher bit does not appear.  
![counter6-4.png](https://github.com/teddokano/additional_files/blob/main/BusInOut_Arduino/counter6-4.png)  

On **Arduino UNO R3**, the pins 0 and 1 are taken if `Serial` feature is used. Those pins cannot be used for `BusInOut` while UART or terminal screen IO is used.  
The analyzer picture below was taken with comment-out the line of `#define SERIAL_OUT_DISABLE`.  
![counter0-7_serial_enabled.png](https://github.com/teddokano/additional_files/blob/main/BusInOut_Arduino/counter0-7_serial_enabled.png)  

## Output + Input
A test code of `BusInOut_test_OUTPUT_INPUT.ino` can try both input and output features. 

```cpp
#include "BusInOut.h"

BusInOut bio0(2, 3, 4, 5, 6, 7);
BusInOut bio1(10, 11, 12, 13, A4, A5);

//#define SERIAL_OUT_DISABLE

void setup() {
#ifndef SERIAL_OUT_DISABLE
  Serial.begin(9600);
  while (!Serial)
    ;

  Serial.println("Hello, BusInOUt");
  Serial.println("\"D0\" and \"D1\" pins are disabled with \"Serial\" feature because those pins are shared");
#endif

  bio0.config(OUTPUT);
  bio1.config(INPUT);
}

void loop() {
  uint8_t read_value;
  for (int i = 0; i < 256; i++) {
    bio0 = i;
    read_value  = bio1;
    Serial.println(read_value);
    delay( 100 );
  }
}
```

This code performs output and input together. Pins 2-7 works for **6 bit output**, pins 10-13, A4, A5 for **6 bit input**.  
Connenct those each input and output pins (short with jumper wires) and run the code. It will show the read value on the terminal screen. 

