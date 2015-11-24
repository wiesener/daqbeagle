#include <EHRPWM2.hpp>
using namespace std;

EHRPWM2::EHRPWM2(MAP& map, double frequency)
	: map(map)
{
#ifdef WITH_HW
	uint32_t* pwm_map = map.getMap();

	if (pwm_map != 0){
		// set period to user interface value
		setPeriod(1000000.0 / frequency);
		
        // duty cycle of PWM1 and PWM2
        setDuty(0.0, PWM1);
        setDuty(0.0, PWM2);

	} else {
		printf("Error \n");
		exit(EXIT_FAILURE);
	}
#endif
}

EHRPWM2::~EHRPWM2(){
    setDuty(0.0, PWM1);
    setDuty(0.0, PWM2);
}

int EHRPWM2::getDuty(uint8_t pin){
#ifdef WITH_HW
	uint32_t* pwm_map = map.getMap();
	if (pwm_map != 0){
		if (pin == PWM1){
			return (pwm_map[(EHRPWM2_CMPA - MMAP_OFFSET)/4] & 0xFFFF0000) >> 16;
		}
		else if (pin == PWM2) {
			return pwm_map[(EHRPWM2_CMPB - MMAP_OFFSET)/4] & 0x0000FFFF;
		}
		else return -1;
	} else {
		exit(EXIT_FAILURE);
	}
#endif
}

void EHRPWM2::setDuty(double duty, uint8_t pin){
#ifdef WITH_HW
	uint32_t* pwm_map = map.getMap();
	if (pwm_map != 0){
		if (pin == PWM1){
			pwm_map[(EHRPWM2_CMPA - MMAP_OFFSET)/4] &= 0x0000FFFF;
			pwm_map[(EHRPWM2_CMPA - MMAP_OFFSET)/4] |= ((uint32_t) duty) << 16;
		}
		else if (pin == PWM2) {
			pwm_map[(EHRPWM2_CMPB - MMAP_OFFSET)/4] &= 0xFFFF0000;
			pwm_map[(EHRPWM2_CMPB - MMAP_OFFSET)/4] |= ((uint32_t) duty);
		}
	} else {
		exit(EXIT_FAILURE);
	}
#endif
}


int EHRPWM2::getPeriod(){
#ifdef WITH_HW
	uint32_t* pwm_map = map.getMap();
	if (pwm_map != 0){
		return (pwm_map[(EHRPWM2_TBPRD - MMAP_OFFSET)/4] & 0xFFFF0000) >> 16;
	} else {
		exit(EXIT_FAILURE);
	}
#endif
}

void EHRPWM2::setPeriod(double period){
#ifdef WITH_HW
	uint32_t* pwm_map = map.getMap();
	if (pwm_map != 0){
		// set period register
		// set the TBPRD register to zero
		pwm_map[(EHRPWM2_TBPRD - MMAP_OFFSET)/4] &= 0x0000FFFF;
		// set new period
		pwm_map[(EHRPWM2_TBPRD - MMAP_OFFSET)/4] |= ((uint32_t) period) << 16;
	} else {
		exit(EXIT_FAILURE);
	}
#endif
}
