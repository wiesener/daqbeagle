//!
//! @file: GPIO.hpp
//!
//! @author: constantin
//!
//! @date: 08-Apr-2015 5:37:13 PM
//!
//! @ingroup: retrainer/GPIO
//!
//! @brief Implementation of the element collection GPIO
//!

//
// Copyright (c) TU Berlin
//
#include "GPIO.hpp"


//! @name GPIO
//! 
//! @brief Constructor of GPIO class.  This function initializes CoreGPIO class
//! with entered parameters and errorGPIO struct. Then it sets value file path
//! variable.
//! 
//! @param  pn
//! @param  pd
//! @param  wm
//! @retval
GPIO::GPIO(const PIN pin, direction dir, MAP& map)
	: pin(pin), map(map), dir(dir)
{
#ifdef WITH_HW
#ifdef USE_STARTUP_FILE // in case of a startup file the whole config is done there
	std::ofstream expFile;
	std::ofstream dirFile;

	// open export file and set pin to export list
	expFile.open(EXPORT_PATH.c_str(), std::ios::out);
	if(!expFile.is_open()) {
		perror("Cannot open export file.");
		exit(1);
	}
	expFile << static_cast<int>(pin.gpio);
	expFile.close();

	// open direction file and set direction
	std::string path = DIRECTION_PATH + tostr(static_cast<int>(pin.gpio)) + "/direction";
	dirFile.open(path.c_str(), std::ios::out);
	if(!dirFile.is_open()) {
		perror("Cannot open direction file.");
		exit(2);
	}
	dirFile << dirArr[static_cast<uint8_t>(dir)];
	dirFile.close();
#endif
#endif
}

//! @name ~GPIO
//! 
//! @brief Destructor of GPIO class.
//! 
//! 
//! @retval
GPIO::~GPIO(){
}


//! @name getValue
//! 
//! @brief Reads value of gpio pin and returns it as int
//! 
//! 
//! @retval int
int GPIO::getValue(){
#ifdef WITH_HW
	uint32_t* gpio_map = map.getMap();
	if ((this->dir == input) || (gpio_map != 0)){
		return (gpio_map[(pin.gpio_bank-MMAP_OFFSET+GPIO_DATAIN)/4] & (1<<pin.bank_id))>>pin.bank_id;
	} else {
		return -1;
	}
#endif
}


//! @name setValue
//! 
//! @brief Sets value of GPIO pin. If pin direction is not output, function returns
//! with false value.
//! 
//! @param  state
//! @retval bool
bool GPIO::setValue(const bool state){
#ifdef WITH_HW
	if (this->dir == output){
		uint32_t* gpio_map = map.getMap();
		if (gpio_map != 0){
			gpio_map[(pin.gpio_bank-MMAP_OFFSET+GPIO_OE)/4] &= ~(1<<pin.bank_id);
			if(state){
				gpio_map[(pin.gpio_bank-MMAP_OFFSET+GPIO_DATAOUT)/4] |= 1<<pin.bank_id;
			}
			else{
				gpio_map[(pin.gpio_bank-MMAP_OFFSET+GPIO_DATAOUT)/4] &= ~(1<<pin.bank_id);
			}
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
#endif
}



//! @name toggleValue
//! 
//! @brief Toggles value of GPIO pin.  If pin direction is not output, this function
//! returns false
bool GPIO::toggleValue(){
#ifdef WITH_HW
	if (this->dir == output){
		uint32_t* gpio_map = map.getMap();
		if (gpio_map != 0){
			gpio_map[(pin.gpio_bank-MMAP_OFFSET+GPIO_OE)/4] &= ~(1<<pin.bank_id);
			gpio_map[(pin.gpio_bank-MMAP_OFFSET+GPIO_DATAOUT)/4] ^= 1<<pin.bank_id;
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
#endif
}
