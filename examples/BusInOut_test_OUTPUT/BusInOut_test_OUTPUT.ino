/** BusInOut OUTPUT example
 *  To test this sample, connect pins to a logic analyzer
 *
 *  @author  Tedd OKANO
 *
 *  Released under the MIT license License
 */
#include "BusInOut.h"

constexpr uint8_t NC  = BusInOut::nc;

BusInOut bio0(0, 1, 2, 3, 4, 5, 6, 7);
//BusInOut bio0(7, 6, 5, 4, 3, 2, 1, 0);
//BusInOut bio0(7, 6, 5, NC, 3, 2, 1, 0);
//BusInOut bio0(6, 5, 4);
//BusInOut bio0(8, 9, 10, 11, 12, 13, A4, A5);

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
