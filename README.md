# digital_filter_arduino

A library for creating digital lowpass filter.

# Quick start guide
- Create and name a filter object. Define the cutoff frequency.
```
lowpass_filter my_filter_1(cutoff frequency); // cutoff frequency in Hz

lowpass_filter my_filter_2; // default 1 Hz is used as cutoff frequency
```
- In your loop, pass an incoming signal (sensor reading) to the filter function of the filter object
```
filtered_signal = my_filter_1.filter(raw_signal); // returns the filtered signal
```
- Done

# Frequency response

