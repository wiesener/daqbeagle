//!
//! @file: GPIO.hpp
//!
//! @author: constantin
//!
//! @date: 08-Apr-2015 5:37:13 PM
//!
//! @ingroup: retrainer/GPIO
//!
//! @brief Declaration of the element collection GPIO
//!

//
// Copyright (c) TU Berlin
//
#if !defined(_GPIO_HEADER_)
#define _GPIO_HEADER_

#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <fcntl.h>
#include <sys/mman.h>
#include "Definitions.hpp"
#include "MAP.hpp"

//! @brief Interacts with end user, to use GPIO.  This class is end node to use
//! GPIO. End users interact with gpio pins from this class. It includes public
//! functions to set and get properties of GPIO.
class GPIO
{

public:

   //! @name GPIO
   //! 
   //! @brief Constructor of GPIO class.  This function initializes CoreGPIO class
   //! with entered parameters and errorGPIO struct. Then it sets value file path
   //! variable.
   GPIO(PIN pin, direction dir, MAP& map);

   //! @name ~GPIO
   //! 
   //! @brief Destructor of GPIO class.  This function deletes errorGPIO struct
   //! pointer.
   //! 
   //! 
   //! @retval
   virtual ~GPIO();


   //! @name getValue
   //! 
   //! @brief Reads value of gpio pin as int type.
   //!
   //! @retval int
   int getValue();

   //! @name setValue
   //! 
   //! @brief Sets value of GPIO pin. If pin direction is not output, function returns
   //! with false value. If working mode is selected SecureMode, this function checks
   //! pin ready state by calling isReady() function. If pin is not ready, function
   //! returns with false value. If working mode is selected FastMode, ready state
   //! checking will skip. Then the input parameter is converted to 1 or 0 and this
   //! value is saved to value file.
   //! 
   //! @param  state
   //! @retval bool
   bool setValue(const bool state);

   //! @name toggleValue
   //! 
   //! @brief Toggles value of GPIO pin.  If pin direction is output, this function
   //! sets pin value to 1 or 0, by value of current state.
   //!
   //! @retval bool
   bool toggleValue();

private:
   //! reference to the global memory map
   MAP& map;

   //! pin which should be configured
   PIN pin;

   //! direction
   direction dir;
};
#endif // !defined(_GPIO_HEADER_)
