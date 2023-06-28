#include "filter_lib.h"

// create filter with 2 Hz cut-off frequency
lowpass_filter lowpassFilter(2); 

float raw_signal;
float filtered_signal;

void setup() {
  Serial.begin(9600);
}

void loop() {
  // time variable
  float t = micros() / 1e6;
  
  // 0.2 Hz Sine wave
  raw_signal = 10 + 10*(sin(2 * PI * t * 0.2));
  
  // add some noise   
  raw_signal += 2*(sin(2 * PI * t * 50)) + 1*(sin(2 * PI * t * 1500));
  
  // filter raw signal
  filtered_signal = lowpassFilter.filter(raw_signal);

  // print raw and filtered signal to serial monitor
  Serial.print("Raw:");
  Serial.print(raw_signal);
  Serial.print(",");
  Serial.print("Filtered:");
  Serial.println(filtered_signal);
  delay(10);
}
