# digital_filter_arduino

A library for creating digital lowpass filter.

![alt text](https://github.com/timonbraun02/digital_filter_arduino/blob/main/noisefilter.png)
- The image shows a 0.1 Hz sine wave signal with an added 50 Hz and 150 Hz sine wave to simulate noise.
- The raw signal is shown in blue and the filtered signal is shown in red

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

![alt text](https://github.com/timonbraun02/digital_filter_arduino/blob/main/1Hz.png)
- The image shows the raw 1 Hz sine wave (blue) and the filtered result (red)
- As you can see, the magnitude of the input has been decreased, as should be expected when the input signals frequency matches the cutoff frequency of the filter 
- The phase shift of 45° can also be seen in the image

## Results
- The filter was tested for 0.1 Hz, 1 Hz, 10 Hz and 100 Hz
- The expected gain of the output signal is -3 dB, since the input signals frequency is set to match the filters cutoff frequency
  - 0.1 Hz -> Gain = -3.12 dB
  - 1 Hz -> Gain = -3.13 dB
  - 10 Hz -> Gain = -3.12 dB
  - 100 Hz -> Gain = -3.13 dB
- The limiting factor for input signals is your sampling rate

# Conclusion:
  - The filter works great for smoothing out a sensor reading or filter high frequency noise
  - The filter is limited by your sampling rate
  - I did not include the test for the 1000 Hz frequency, since I was limited by my sampling rate
  - Recommended applications: noise filter for analog sensors, and other low frequency signals
