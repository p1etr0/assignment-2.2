#ifndef __TYPES__
#define __TYPES__

enum RadarState {
    IDLE,
    WORKING,
    PRE_ALARM,
    ALARM
};

extern RadarState radarState;

#endif
