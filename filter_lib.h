/*
  filter_lib.h - Library for creating digital filter.
  Created by Timon Braun, March 26, 2023.
  Released into the public domain.
*/

#ifndef filter_lib_h

#define filter_lib_h


// Lowpass filter class;
// default constructor -> f_cutoff = 1Hz;
// custom constructor -> lowpass_filter [filter_name] (f_cutoff);
class lowpass_filter {

  public:
    float f_cutoff, fs;
    // default constructor
    lowpass_filter(): f_cutoff(1) {}

    // custom constructor
    lowpass_filter(float f_c): f_cutoff(f_c) {}

    float old_raw; // old raw val
    float old_filtered; // old filtered val
    float ts = 0; // sampling time 1/sampling frequency
    

    // filter function
    // raw signal as input
    float filter(float raw) {
      ts = (micros() - ts) * 1e-6;
      // coefficients a and b from bilinear transform of transfer function
      // of first order lowpass filter
      float a_0 = -(((ts / 2) * 2 * PI * f_cutoff - 1) / ((ts / 2) * 2 * PI * f_cutoff + 1));
      float b_0 = ((ts / 2) * 2 * PI * f_cutoff) / (1 + (ts / 2) * 2 * PI * f_cutoff);

      float filtered = a_0 * old_filtered + b_0 * raw + b_0 * old_raw;
      old_raw = raw; // save current raw for next calc
      old_filtered = filtered; // save current filtered for next calc
      ts = micros();
      return filtered; // return the filtered val
    }
};

// Simulates behavior of a RC-lowpass filter;
// default constructor -> R = 1000, C = 1.59e-4 => f_cutoff = 1Hz;
// custom constructor -> rc_filter [filter_name] (r, c);
class rc_filter {

  public:
    float r, c, fs; // resistor val, cap. val, sampling frequency
    // default constructor
    rc_filter(): r(1000), c(1.59e-4) {}

    // custom constructor
    rc_filter(float r_val, float c_val): r(r_val), c(c_val) {}
    float f_cutoff = 1 / (2 * PI * r * c); // calc cutoff frequency
    float old_raw; // old raw val
    float old_filtered; // old filtered val
    float ts = 0; // sampling time 1/sampling frequency
    float t_s = 0;

    // filter function
    // raw signal as input
    float filter(float raw) {
      t_s = micros() - t_s;
      ts = t_s / 1e6;

      // coefficients a and b from bilinear transform of transfer function
      // of first order lowpass filter
      float a_0 = -((ts / 2) * 2 * PI * f_cutoff - 1) / ((ts / 2) * 2 * PI * f_cutoff + 1);
      float b_0 = ((ts / 2) * 2 * PI * f_cutoff) / (1 + (ts / 2) * 2 * PI * f_cutoff);
      float filtered = a_0 * old_filtered + b_0 * raw + b_0 * old_raw;
      old_raw = raw; // save current raw for next calc
      old_filtered = filtered; // save current filtered for next calc
      t_s = micros();
      return filtered; // return the filtered val
    }

    float phase_shift(float f) {
      return -atan(2 * PI * f * r * c) * 180 / PI;
    }
};



#endif
