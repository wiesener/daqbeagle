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

static const std::vector<PIN> OUTPINS = boost::assign::list_of(P8_29)(P8_26)(P8_27)(P8_28)
													 (P8_14)(P8_16)(P8_18)(P8_12);
#ifdef WITH_HW
class DOUT{
public :
    DOUT(MAP& map, uint8_t* pin_enable, int32_t NUM)
    : NUM(NUM){
        this->gpios = new GPIO*[NUM];
        std::cout << "OUTPUTS: ";
        for (int i = 0; i < NUM; i++){
            PIN pin = (PIN) OUTPINS.at(pin_enable[i]-1); // Matlab counting
            this->gpios[i] = new GPIO(pin, output, map);
            std::cout << " " << pin.name;
        }
        std::cout << std::endl;
    };
    
    ~DOUT()
    {
        for (int i = 0; i < NUM; i++){
            delete this->gpios[i];
        }
        delete gpios;
    };
    
    GPIO** gpios;
    uint8_t NUM;
};
#endif

static void createDOUT(void** work, uint8_t* pin_enable, int32_t NUM)
{
#ifdef WITH_HW
	map.openMap();
    DOUT* dout = new DOUT(map, pin_enable, NUM);
    (*work) = (void *) dout;
#endif
}


static void deleteDOUT(void** work)
{
#ifdef WITH_HW
    DOUT* dout = (DOUT *) (*work);
    delete dout;
    map.closeMap();
#endif
}

static void outputDOUT(void** work, uint8_t* state)
{
#ifdef WITH_HW
    DOUT* dout = (DOUT *) (*work);
	for (int i = 0; i < dout->NUM; i++){
		dout->gpios[i]->setValue((bool) state[i]);
    }
#endif
}
