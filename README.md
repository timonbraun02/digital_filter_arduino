# digital_filter_arduino

A library for creating digital lowpass filter.

# Quick start guide

- Include the lib
```cpp
#include "filter_lib.h"
```

- Create and name a filter object. Define the cutoff frequency.
```cpp
lowpass_filter my_filter_1(cutoff frequency); // cutoff frequency in Hz
lowpass_filter my_filter_2; // default 1 Hz is used as cutoff frequency
```

- In your loop, pass an incoming signal (sensor reading) to the filter function of the filter object
```cpp
filtered_signal = my_filter_1.filter(raw_signal); // returns the filtered signal
```
- Done

# Frequency response and filters of higher order

- The transfer function of the filter was plotted in MatLab
- The frequncy response for the lowpass filter with a cutoff frequency of 10 Hz shows a magnitude of -3dB at 10 Hz
- The created filter object serves as a first order lowpass filter
  
![alt text](https://github.com/timonbraun02/digital_filter_arduino/blob/main/first_order.png)

- By stacking multiple filter objects, you can create a second(third, fourth, ...) order lowpass filter
- Before stacking filter, be aware of the increasing phase shift of your filters frequency response
- The image shows, how you could create a second order filter
- The frequency response shows a magnitude of -6dB at 10 Hz, but also a phase shift of -90°
 
![alt text](https://github.com/timonbraun02/digital_filter_arduino/blob/main/second_order.png)

- The code for a second order lowpass filter would look like this:
```cpp
lowpass_filter my_filter_1(10);
lowpass_filter my_filter_2(10);

void setup(){
  // init sensors
}

void loop(){
  raw_signal = analogRead(sensor);
  filtered_signal = my_filter_1.filter( my_filter_2.filter( raw_signal ) );
}
```
