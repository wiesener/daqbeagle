/*
 * GPO_BBB.hpp
 *
 *  Created on: Apr 10, 2015
 *      Author: constantin
 */
#include "MAPhelper.hpp"
#include "GPIO.hpp"
#include <stdint.h>
#include <string>
#include <algorithm>    // std::find_if
#include <vector>       // std::vector
#include <boost/assign/list_of.hpp>
#include <iostream>

// External declaration for class instance global storage
extern MAP map;

static const std::vector<PIN> INPINS = boost::assign::list_of(P8_33)(P8_42)(P8_41)(P8_43)
													 (P8_40)(P8_44)(P8_39)(P8_45);

#ifdef WITH_HW
class DIN{
public :
    DIN(MAP& map, uint8_t* pin_enable, int32_t NUM)
    : NUM(NUM){
        this->gpios = new GPIO*[NUM];
        std::cout << "INPUTS: ";
        for (int i = 0; i < NUM; i++){
            PIN pin = (PIN) INPINS.at(pin_enable[i]-1); // Matlab counting
            this->gpios[i] = new GPIO(pin, input, map);
            std::cout << " " << pin.name;
        }
        this->oe = new GPIO(P8_30, output, map);
        this->oe->setValue(true); // enable all pins.
        std::cout << std::endl;
    };
    
    ~DIN()
    {
        for (int i = 0; i < NUM; i++){
            delete this->gpios[i];
        }
        delete this->oe;
        delete gpios;
    };
    
    GPIO** gpios;
    GPIO* oe;
    uint8_t NUM;
};
#endif

static void createDIN(void** work, uint8_t* pin_enable, int32_t NUM)
{
#ifdef WITH_HW
	map.openMap();
    DIN* din = new DIN(map, pin_enable, NUM);
    (*work) = (void *) din;
#endif
}


static void deleteDIN(void** work)
{
#ifdef WITH_HW
    DIN* din = (DIN *) (*work);
    delete din;
    map.closeMap();
#endif
}

static void outputDIN(void** work, uint8_t* state)
{
#ifdef WITH_HW
    DIN* din = (DIN *) (*work);
	for (int i = 0; i < din->NUM; i++){
		state[i] = (uint8_t) (din->gpios[i]->getValue());
    }
#endif
}
