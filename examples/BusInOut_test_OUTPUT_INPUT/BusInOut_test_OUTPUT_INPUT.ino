/** BusInOut OUTPUT-INPUT example
 *
 *  To test this sample, connect pins as follows
 *    D2 - D10, 
 *    D3 - D11, 
 *    D4 - D12, 
 *    D5 - D13, 
 *    D6 - D14(A4), 
 *    D7 - D15(A5)
 *  You will see count-up values on terminal console
 *
 *  @author  Tedd OKANO
 *
 *  Released under the MIT license License
 */

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
