#ifndef __COLOR_H__
#define __COLOR_H__

#include "types.hpp"
#include "converter.hpp"

inline void HsvToRgb(
                    const uint8_t &src_h,
                    const uint8_t &src_s,
                    const uint8_t &src_v,

                    uint8_t &dst_r,
                    uint8_t &dst_g,
                    uint8_t &dst_b) {
    float h = tofloat(src_h) * 2.0F;   // 0-360
    float s = tofloat(src_s) / 255.0F; // 0.0-1.0
    float v = tofloat(src_v) / 255.0F; // 0.0-1.0

    float r, g, b; // 0.0-1.0

    int hi = (int)(h / 60.0F) % 6;
    float f = (h / 60.0F) - hi;
    float p = v * (1.0F - s);
    float q = v * (1.0F - s * f);
    float t = v * (1.0F - s * (1.0F - f));

    switch (hi)
    {
    case 0:
        r = v, g = t, b = p;
        break;
    case 1:
        r = q, g = v, b = p;
        break;
    case 2:
        r = p, g = v, b = t;
        break;
    case 3:
        r = p, g = q, b = v;
        break;
    case 4:
        r = t, g = p, b = v;
        break;
    case 5:
        r = v, g = p, b = q;
        break;
    }

    dst_r = (uint8_t)(r * 255); // dst_r : 0-255
    dst_g = (uint8_t)(g * 255); // dst_r : 0-255
    dst_b = (uint8_t)(b * 255); // dst_r : 0-255
}

inline void HsvToRgb(
                    const uint8_t &src_h,
                    const uint8_t &src_s,
                    const uint8_t &src_v,

                    uint32_t &dst_rgb
                    ) {

    float h = tofloat(src_h) * 2.0F;   // 0-360
    float s = tofloat(src_s) / 255.0F; // 0.0-1.0
    float v = tofloat(src_v) / 255.0F; // 0.0-1.0

    float r, g, b; // 0.0-1.0

    int hi = (int)(h / 60.0F) % 6;
    float f = (h / 60.0F) - hi;
    float p = v * (1.0F - s);
    float q = v * (1.0F - s * f);
    float t = v * (1.0F - s * (1.0F - f));

    switch (hi)
    {
    case 0:
        r = v, g = t, b = p;
        break;
    case 1:
        r = q, g = v, b = p;
        break;
    case 2:
        r = p, g = v, b = t;
        break;
    case 3:
        r = p, g = q, b = v;
        break;
    case 4:
        r = t, g = p, b = v;
        break;
    case 5:
        r = v, g = p, b = q;
        break;
    }

    dst_rgb = ((uint8_t)(r * 255) << 16) + ((uint8_t)(g * 255) << 8) + ((uint8_t)(b * 255)) ;
    
}

#endif