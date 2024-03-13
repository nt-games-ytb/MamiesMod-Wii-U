#ifndef __RANDOM_H__
#define __RANDOM_H__

class Random {
private:

static inline Random *Ctor(Random* ptr) {
    return ((Random*(*)(Random*))0x027DCA84)
    (ptr);
}

public:

inline Random() {
    Random::Ctor(this);
}

int nextInt(int min, int max) {
    return ((int(*)(Random*, int, int))0x027E08E0)
    (this, min, max);
}

float nextFloat(float min, int max) {
    return ((float(*)(Random*, float, float))0x027E0978)
    (this, min, max);
}

};

#endif