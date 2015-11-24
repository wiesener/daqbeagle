#include "MAPhelper.hpp"
#include "EHRPWM2.hpp"
#include <stdint.h>
#include <string>

#include <iostream>

// External declaration for class instance global storage
extern MAP map;

static void createPWM(void** work, double frequency)
{
#ifdef WITH_HW
    map.openMap();
    EHRPWM2* pwm = new EHRPWM2(map, frequency);
    *work = (void *) pwm;
#endif
}


static void deletePWM(void** work)
{
#ifdef WITH_HW
    EHRPWM2* pwm = (EHRPWM2*) (*work);
    if (pwm != 0){
        delete pwm;
    }
    map.closeMap();
#endif
}

static void outputPWM(void** work, double u1[2])
{
#ifdef WITH_HW
    EHRPWM2* pwm = (EHRPWM2*) (*work);
    if (pwm != 0){
        pwm->setDuty(u1[0], PWM1);
        pwm->setDuty(u1[1], PWM2);
    }
#endif
}
