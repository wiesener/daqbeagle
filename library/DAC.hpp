#if !defined(_DAC_HEADER_)
#define _DAC_HEADER_

#include "Definitions.hpp"
#include "MAP.hpp"

class DAC
{

public:
   DAC(MAP& map);

   virtual ~DAC();

   double getVoltage(uint8_t pin);

   void setVoltage(double voltage, uint8_t pin);

private:
   //! reference to map
   MAP& map;

};
#endif // !defined(_DAC_HEADER_)
