/*
 * ADCblock.hpp
 *
 *  Created on: Apr 10, 2015
 *      Author: constantin
 */
#include "MAPhelper.hpp"
#include "ADC.hpp"

// External declaration for class instance global storage
extern MAP map;

static void createADC(void** work)
{
    // do the initialization twice due to strange behavior of the adc
    map.openMap();
    ADC* adc1 = new ADC(map);
	delete adc1;
    usleep(1);
    ADC* adc = new ADC(map);
    usleep(1);
    *work = (void*) adc1;
}

static void deleteADC(void** work)
{
    ADC* adc = (ADC*) (*work);
	delete adc;
    map.closeMap();
}

static void outputADC(void** work, double adcOut[7])
{
    ADC* adc = (ADC*) (*work);
    adc->getAllNumericValues(adcOut);
}

