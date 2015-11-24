//!
//! @file: ADC.hpp
//!
//! @author: constantin
//!
//! @date: 08-Apr-2015 4:19:47 PM
//!
//! @ingroup: retrainer/ADC
//!
//! @brief Declaration of the element collection ADC
//!

//
// Copyright (c) TU Berlin
//
#if !defined(_ADC_HEADER_)
#define _ADC_HEADER_

#include "Definitions.hpp"
#include "MAP.hpp"


//! @brief Interacts with end user, to use ADC.  This class is end node to use
//! analog inputs. End users interact with analog inputs from this class. It
//! includes public functions for reading analog values.
class ADC
{

public:
   //! @name ADC constructor
   //! 
   //! @brief
   ADC(MAP& map);

   //! @name ~ADC
   //! 
   //! @brief
   //! 
   //! 
   //! @retval
   virtual ~ADC();

   //! @name getNumericValue
   //! 
   //! @brief
   //! 
   //! 
   //! @retval int
   int getNumericValue(adcName pin);

   //! @name getAllNumericValue
   //!
   //! @brief
   //!
   //!
   //! @retval adcOut pointer to write data in
   void getAllNumericValues(double adcOut[6]);

private:
   //! reference to map
   MAP& map;
   //! adc clock initialized
   bool adc_clock_initialized;

};
#endif // !defined(_ADC_HEADER_)
