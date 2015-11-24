#include <DAC.hpp>
using namespace std;

DAC::DAC(MAP& map)
	: map(map)
{
#ifdef WITH_HW
	uint32_t* pwm_map = map.getMap();

	if (pwm_map != 0){
		setVoltage(0.0, AOUT1);
        setVoltage(0.0, AOUT2);
	} else {
		printf("Error \n");
		exit(EXIT_FAILURE);
	}
#endif
}

DAC::~DAC(){
    uint32_t* pwm_map = map.getMap();
	if (pwm_map != 0){
		setVoltage(0.0, AOUT1);
        setVoltage(0.0, AOUT2);
	} else {
		printf("Error \n");
		exit(EXIT_FAILURE);
	}
}

double DAC::getVoltage(uint8_t pin){
#ifdef WITH_HW
	uint32_t* pwm_map = map.getMap();
	if (pwm_map != 0){
		if (pin == AOUT1){
			return ((double) ((pwm_map[(EHRPWM1_CMPA - MMAP_OFFSET)/4] & 0xFFFF0000) >> 16));
		}
		else if (pin == AOUT2) {
			return ((double) (pwm_map[(EHRPWM1_CMPB - MMAP_OFFSET)/4] & 0x0000FFFF));
		}
		else{
            return -1;
        }
	} else {
		exit(EXIT_FAILURE);
	}
#endif
}

void DAC::setVoltage(double voltage, uint8_t pin){
#ifdef WITH_HW
	uint32_t* pwm_map = map.getMap();
	if (pwm_map != 0){
		uint32_t duty = (uint32_t) (voltage/5.0 * 100.0); // (voltage/3.3V * period), period = 1Mhz
		if (pin == AOUT1){
			pwm_map[(EHRPWM1_CMPA - MMAP_OFFSET)/4] &= 0x0000FFFF;
			pwm_map[(EHRPWM1_CMPA - MMAP_OFFSET)/4] |= duty << 16;
		}
		else if (pin == AOUT2) {
			pwm_map[(EHRPWM1_CMPB - MMAP_OFFSET)/4] &= 0xFFFF0000;
			pwm_map[(EHRPWM1_CMPB - MMAP_OFFSET)/4] |= duty;
		}
	} else {
		exit(EXIT_FAILURE);
	}
#endif
}
