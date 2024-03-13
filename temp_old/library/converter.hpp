#ifndef __CONVERTER_H__
#define __CONVERTER_H__

inline double todouble(int i) {
    volatile union {
        struct {
            int high;
            int low;
        } i32;
        float f32;
        double f64;
    } conv;
    conv.i32.high = 0x43300000;
    conv.i32.low = i ^ 0x80000000;
    double d = conv.f64;
    conv.i32.high = 0x59800004;
    float f = conv.f32;
    return d - f; 
}

inline float tofloat(int i) {
    return (float)todouble(i);
}

#endif