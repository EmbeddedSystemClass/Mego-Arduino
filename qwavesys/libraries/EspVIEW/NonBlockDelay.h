
#ifndef NONBLOCKDELAY_H
#define NONBLOCKDELAY_H

class NonBlockDelay {
    unsigned long iTimeout=0;
public:
    bool Timeout (unsigned long);
    unsigned long Time(void);
};


#endif
