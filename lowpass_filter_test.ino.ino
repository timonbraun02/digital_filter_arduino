#include "filter_lib.h"

// filter instances
rc_filter rc_sim(1000, 4.7e-6);
lowpass_filter filter1(12);

void setup() {
  Serial.begin(115200);
}

void loop() {

  float t = millis() / 1e3;

  // test signal
  float y = sin(2 * PI * t * 10) + 0.2 * sin(2 * PI * t * 35) + 0.2 * sin(2 * PI * t * 450);

  float val1 = filter1.filter(y);
  float rc = rc_sim.filter(y);

  Serial.print(y);
  Serial.print(" ,");
  Serial.print(val1);
  Serial.print(" ,");
  Serial.print(rc);
  Serial.println(" ");
}