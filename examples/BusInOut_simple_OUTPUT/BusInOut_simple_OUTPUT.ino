/** BusInOut OUTPUT example
 *  See pins are toggling with each frequencies
 *
 *  @author  Tedd OKANO
 *
 *  Released under the MIT license License
 */
#include "BusInOut.h"

BusInOut bio0(0, 1, 2, 3, 4, 5, 6, 7);

void setup() {
  bio0.config(OUTPUT);
}

void loop() {
  for (int i = 0; i < 256; i++) {
    bio0 = i;
  }
}
