#include "MAPhelper.hpp"
#include "DAC.hpp"
#include <stdint.h>
#include <string>

#include <iostream>

// External declaration for class instance global storage
extern MAP map;

static void createAOUT(void** work)
{
#ifdef WITH_HW
    map.openMap();
    DAC* dac = new DAC(map);
    *work = (void *) dac;
#endif
}


static void deleteAOUT(void** work)
{
#ifdef WITH_HW
    DAC* dac = (DAC*) (*work);
    if (dac != 0){
        delete dac;
    }
    map.closeMap();
#endif
}

static void outputAOUT(void** work, double u1[2])
{
#ifdef WITH_HW
    DAC* dac = (DAC*) (*work);
    if (dac != 0){
        dac->setVoltage(u1[0], AOUT1);
        dac->setVoltage(u1[1], AOUT2);
    }
#endif
}
