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

# Testing

- This digital filter should only be use for low frequency applications as the following tests will show
- In the following tests, I set the cutoff frequency of my filter to the same frequency of a sine wave signal
- The filter was tested for 0.1 Hz, 1 Hz, 2 Hz, 5 Hz and 10 Hz
  - 0.1 Hz -> Gain = -3.01 dB
  - 1 Hz -> Gain = -3.02 dB
  - 2 Hz -> Gain = -3.09 dB
  - 5 Hz -> Gain = -3.50 dB
  - 10 Hz -> Gain = -6.36 dB
- From the tests you can see that your input signal should not exceed 5 Hz
- Conclusion:
  - The filter works great for input signals below 5 Hz, which should not be an issue if your application is to smooth out a sensor reading or filter high frequency noise
  - The filter should not be used for signals above 5 Hz since the results can be in accurate
  - I did not include the test for the 100 Hz frequency, since the result was very inconsistent and even showed a positive gain at the cutoff frequency
  - Recommended applications: noise filter for analog sensors, and other low frequency signals
