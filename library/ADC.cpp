//!
//! @file: ADC.hpp
//!
//! @author: constantin
//!
//! @date: 08-Apr-2015 4:19:47 PM
//!
//! @ingroup: retrainer/ADC
//!
//! @brief Implementation of the element collection ADC
//!

//
// Copyright (c) TU Berlin
//
#include "ADC.hpp"
#include <time.h>

//! @name ADC
//! 
//! @brief
//! 
ADC::ADC(MAP& map)
	: map(map), adc_clock_initialized(false)
{
#ifdef WITH_HW
	uint32_t* adc_map = map.getMap();

	if (adc_map != 0){
		// enable the CM_WKUP_ADC_TSC_CLKCTRL with CM_WKUP_MODUELEMODE_ENABLE
		adc_map[(CM_WKUP_ADC_TSC_CLKCTRL-MMAP_OFFSET)/4] |= CM_WKUP_MODULEMODE_ENABLE;

		// wait for the enable to complete
		while(!(adc_map[(CM_WKUP_ADC_TSC_CLKCTRL-MMAP_OFFSET)/4] & CM_WKUP_MODULEMODE_ENABLE)) {
			// waiting for adc clock module to initialize
			//printf("Waiting for CM_WKUP_ADC_TSC_CLKCTRL to enable with MODULEMODE_ENABLE\n");
		}
		adc_clock_initialized = true;
		// software reset, set bit 1 of sysconfig high?
		// make sure STEPCONFIG write protect is off
		adc_map[(ADC_CTRL-MMAP_OFFSET)/4] |= ADC_STEPCONFIG_WRITE_PROTECT_OFF;

		// set up each ADCSTEPCONFIG for each ain pin
		adc_map[(ADCSTEPCONFIG1-MMAP_OFFSET)/4] = 0x00<<19 | ADC_AVG16;
		adc_map[(ADCSTEPDELAY1-MMAP_OFFSET)/4]  = (0x0F)<<24;
		adc_map[(ADCSTEPCONFIG2-MMAP_OFFSET)/4] = 0x01<<19 | ADC_AVG16;
		adc_map[(ADCSTEPDELAY2-MMAP_OFFSET)/4]  = (0x0F)<<24;
		adc_map[(ADCSTEPCONFIG3-MMAP_OFFSET)/4] = 0x02<<19 | ADC_AVG16;
		adc_map[(ADCSTEPDELAY3-MMAP_OFFSET)/4]  = (0x0F)<<24;
		adc_map[(ADCSTEPCONFIG4-MMAP_OFFSET)/4] = 0x03<<19 | ADC_AVG16;
		adc_map[(ADCSTEPDELAY4-MMAP_OFFSET)/4]  = (0x0F)<<24;
		adc_map[(ADCSTEPCONFIG5-MMAP_OFFSET)/4] = 0x04<<19 | ADC_AVG16;
		adc_map[(ADCSTEPDELAY5-MMAP_OFFSET)/4]  = (0x0F)<<24;
		adc_map[(ADCSTEPCONFIG6-MMAP_OFFSET)/4] = 0x05<<19 | ADC_AVG16;
		adc_map[(ADCSTEPDELAY6-MMAP_OFFSET)/4]  = (0x0F)<<24;
		adc_map[(ADCSTEPCONFIG7-MMAP_OFFSET)/4] = 0x06<<19 | ADC_AVG16;
		adc_map[(ADCSTEPDELAY7-MMAP_OFFSET)/4]  = (0x0F)<<24;
		adc_map[(ADCSTEPCONFIG8-MMAP_OFFSET)/4] = 0x07<<19 | ADC_AVG16;
		adc_map[(ADCSTEPDELAY8-MMAP_OFFSET)/4]  = (0x0F)<<24;

		// enable the ADC
		adc_map[(ADC_CTRL-MMAP_OFFSET)/4] |= 0x03;
	} else {
        printf("Error!\n");
		exit(EXIT_FAILURE);
	}
#endif
}

//! @name ~ADC
//! 
//! @brief
//! 
//! 
//! @retval
ADC::~ADC(){
}

//! @name getNumericValue
//! 
//! @brief
//! 
//! 
//! @retval int
int ADC::getNumericValue(adcName pin){
#ifdef WITH_HW
	uint32_t* adc_map = map.getMap();
	if (adc_map != 0){
		if (!adc_clock_initialized){
			exit(EXIT_FAILURE);
		} else {
			// enable the step sequencer for this pin
			adc_map[(ADC_STEPENABLE-MMAP_OFFSET)/4] |= (0x01<<(((uint8_t) pin) + 1));

			// return the the FIFO0 data register
			return adc_map[(ADC_FIFO0DATA-MMAP_OFFSET)/4] & ADC_FIFO_MASK;
		}
	} else {
		exit(EXIT_FAILURE);
	}
#endif
}


//! @name getNumericValue
//!
//! @brief
//!
//!
//! @retval int
void ADC::getAllNumericValues(double adcOut[7]){
#ifdef WITH_HW
	uint32_t* adc_map = map.getMap();
    // delay for conversion
    struct timespec now, rem;
    now.tv_sec = 0;
    now.tv_nsec = 2;
    
	if (adc_map != 0){
		if (!adc_clock_initialized){
			exit(EXIT_FAILURE);
		} else {
			for (uint8_t pin = 0; pin < 7; pin++){
				// enable the step sequencer for this pin
				adc_map[(ADC_STEPENABLE-MMAP_OFFSET)/4] |= (0x01<<(((uint8_t)pin)+1));
				// return the the FIFO0 data register
                adcOut[pin] = static_cast<double>(adc_map[(ADC_FIFO0DATA-MMAP_OFFSET)/4] & ADC_FIFO_MASK);
                // sleep for conversion
                nanosleep(&now, &rem);
			}
		}
	} else {
		exit(EXIT_FAILURE);
	}
#endif
}
