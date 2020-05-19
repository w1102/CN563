#include <relays.h>
#include <Arduino.h>

boolean relayState[4] = {1,1,1,1};
int relayPin[4] = {2,3,4,5};


void pinDeclare()
{
    for (int i = 0;i < sizeof(relayPin) / sizeof(int); i++)
    {
        pinMode(relayPin[i], OUTPUT);
        digitalWrite(relayPin[i], relayState[i]);
    }
}

void checkState(float *t0, float *t1, float *t2, float *t3)
{
    if (*t0 >= 35.00)   {relayState[0] = 1;} else {relayState[0] = 0;}
    if (*t1 >= 35.00)   {relayState[1] = 1;} else {relayState[1] = 0;}
    if (*t2 >= 40.00)   {relayState[2] = 1;} else {relayState[2] = 0;}
    if (*t3 >= 40.00)   {relayState[3] = 1;} else {relayState[3] = 0;}
    

    
}

void sendState(boolean *st0, boolean *st1, boolean *st2, boolean *st3)
{
    if (relayState[0] == 0) {*st0 = 1;} else {*st0 = 0;}
    if (relayState[1] == 0) {*st1 = 1;} else {*st1 = 0;}
    if (relayState[2] == 0) {*st2 = 1;} else {*st2 = 0;}
    if (relayState[3] == 0) {*st3 = 1;} else {*st3 = 0;}

    for (int i = 0;i < sizeof(relayPin) / sizeof(int); i++) {
        digitalWrite(relayPin[i],relayState[i]);
    }



}

void remoState()
{
    for (int i = 0;i < sizeof(relayPin) / sizeof(int); i++) {
        digitalWrite(relayPin[i], HIGH);
    }
}















