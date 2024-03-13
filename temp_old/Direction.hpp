#ifndef __DIRECTION_H__
#define __DIRECTION_H__

class Direction {
public:

    static Direction *getDown() {
        return *(Direction**)0x109C46A0;
    }

    static Direction *getUp() {
        return *(Direction**)0x109C46A4;
    }

    static Direction *getNorth() {
        return *(Direction**)0x109C46A8;
    }

    static Direction *getSouth() {
        return *(Direction**)0x109C46AC;
    }

    static Direction *getWest() {
        return *(Direction**)0x109C46B0;
    }

    static Direction *getEast() {
        return *(Direction**)0x109C46B4;
    }

};

#endif