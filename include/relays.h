#ifndef relays_H
#define relays_H
#include <Arduino.h>




void pinDeclare();
void checkState(float *t0, float *t1, float *t2, float *t3);
void sendState(boolean *st0, boolean *st1, boolean *st2, boolean *st3);
void remoState();

#endif