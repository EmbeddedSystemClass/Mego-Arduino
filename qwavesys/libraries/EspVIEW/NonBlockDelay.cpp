#include "Arduino.h"
#include "NonBlockDelay.h"

bool NonBlockDelay::Timeout (unsigned long t)
{
	if(iTimeout == 0) {
		iTimeout = millis();
		return 0;
	}
	
    bool t_status = (millis() - iTimeout) > t;
    if(t_status) {
        iTimeout = millis();
    }
	
    return t_status;
}

unsigned long NonBlockDelay::Time(void)
{
    return (millis() - iTimeout);
}