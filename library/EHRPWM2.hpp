#if !defined(_EHRPWM2_HEADER_)
#define _EHRPWM2_HEADER_

#include "Definitions.hpp"
#include "MAP.hpp"

class EHRPWM2
{

public:
   EHRPWM2(MAP& map, double period);

   virtual ~EHRPWM2();

   int getDuty(uint8_t pin);

   void setDuty(double duty, uint8_t pin);

   int getPeriod();

   void setPeriod(double period);

private:
   //! reference to map
   MAP& map;
};
#endif // !defined(_EHRPWM2_HEADER_)
