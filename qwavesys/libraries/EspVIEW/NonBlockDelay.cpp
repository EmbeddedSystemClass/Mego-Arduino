#include "Arduino.h"
#include "NonBlockDelay.h"

bool NonBlockDelay::Timeout (unsigned long t)
{
    bool t_status = iTimeout < millis();
	if(t_status) {
        iTimeout = millis() + t;
    }
    return t_status;
}

unsigned long NonBlockDelay::Time(void)
{
    return iTimeout;
}