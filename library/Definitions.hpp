//!
//! @file: Definitions.hpp
//!
//! @author: constantin
//!
//! @date: 10-Apr-2015 8:29:01 AM
//!
//! @ingroup: retrainer/Definitions
//!
//! @brief Declaration of the constant collection Definitions
//!

//
// Copyright (c) TU Berlin
//
#if !defined(_DEFINITIONS_HEADER_)
#define _DEFINITIONS_HEADER_

#include <string>
#include <stdint.h>
#include <sstream>
#include <vector>

#include <boost/assign/list_of.hpp>

template <typename T>
inline std::string tostr(const T& t)
{
	std::ostringstream os;
	os << t;
	return os.str();
}

static const uint32_t MMAP_OFFSET = 0x44C00000;
// the end address of the map must be divisible by 4
static const uint32_t MMAP_SIZE = 0x48304260-MMAP_OFFSET;

/* Clock Module Memory Registers */
static const uint32_t CM_WKUP = 0x44E00400;
static const uint32_t CM_WKUP_ADC_TSC_CLKCTRL = CM_WKUP+0xBC;
static const uint32_t CM_WKUP_MODULEMODE_ENABLE =  (0x02);
static const uint32_t CM_WKUP_IDLEST_DISABLED = (0x03<<16);

static const uint32_t CM_PER = (0x44E00000);
static const uint32_t CM_PER_EPWMSS1_CLKCTRL = (CM_PER+0xCC);
static const uint32_t CM_PER_EPWMSS0_CLKCTRL = (CM_PER+0xD4);
static const uint32_t CM_PER_EPWMSS2_CLKCTRL = (CM_PER+0xD8);


/* GPIO Memory Registers */
static const uint8_t GPIO_REGISTER_SIZE = (4);

static const uint32_t GPIO0 = (0x44E07000);
static const uint32_t GPIO1 = (0x4804C000);
static const uint32_t GPIO2 = (0x481AC000);
static const uint32_t GPIO3 = (0x481AE000);

static const uint16_t GPIO_CLEARDATAOUT = (0x190);
static const uint16_t GPIO_SETDATAOUT = (0x194);
static const uint16_t GPIO_OE = (0x134);
static const uint16_t GPIO_DATAOUT = (0x13C);
static const uint16_t GPIO_DATAIN = (0x138);

/* Analog Digital Converter Memory Registers */
static const uint32_t ADC_TSC = (0x44E0D000);

static const uint32_t ADC_CTRL = (ADC_TSC+0x40);
static const uint32_t ADC_STEPCONFIG_WRITE_PROTECT_OFF = (0x01<<2);
static const uint32_t ADC_STEPENABLE = (ADC_TSC+0x54);

static const uint32_t ADCSTEPCONFIG1 = (ADC_TSC+0x64);
static const uint32_t ADCSTEPDELAY1 = (ADC_TSC+0x68);
static const uint32_t ADCSTEPCONFIG2 = (ADC_TSC+0x6C);
static const uint32_t ADCSTEPDELAY2 = (ADC_TSC+0x70);
static const uint32_t ADCSTEPCONFIG3 = (ADC_TSC+0x74);
static const uint32_t ADCSTEPDELAY3 = (ADC_TSC+0x78);
static const uint32_t ADCSTEPCONFIG4 = (ADC_TSC+0x7C);
static const uint32_t ADCSTEPDELAY4 = (ADC_TSC+0x80);
static const uint32_t ADCSTEPCONFIG5 = (ADC_TSC+0x84);
static const uint32_t ADCSTEPDELAY5 = (ADC_TSC+0x88);
static const uint32_t ADCSTEPCONFIG6 = (ADC_TSC+0x8C);
static const uint32_t ADCSTEPDELAY6 = (ADC_TSC+0x90);
static const uint32_t ADCSTEPCONFIG7 = (ADC_TSC+0x94);
static const uint32_t ADCSTEPDELAY7 = (ADC_TSC+0x98);
static const uint32_t ADCSTEPCONFIG8 = (ADC_TSC+0x9C);
static const uint32_t ADCSTEPDELAY8 = (ADC_TSC+0xA0);

static const uint16_t ADC_AVG0 = (0x000);
static const uint16_t ADC_AVG2 = (0x001);
static const uint16_t ADC_AVG4 = (0x010);
static const uint16_t ADC_AVG8 = (0x011);
static const uint16_t ADC_AVG16 = (0x100);

static const uint32_t ADC_FIFO0DATA = (ADC_TSC+0x100);
static const uint16_t ADC_FIFO_MASK = (0xFFF);

/* EHRPWM1 Module Memory Registers */
static const uint32_t EHRPWM1_TBCTL = 0x48302200;
static const uint32_t EHRPWM1_CMPA = EHRPWM1_TBCTL+0x12;
static const uint32_t EHRPWM1_CMPHRMA = EHRPWM1_TBCTL+0x10;
static const uint32_t EHRPWM1_CMPB = EHRPWM1_TBCTL+0x14;

/* EHRPWM2 Module Memory Registers */
static const uint32_t EHRPWM2_TBCTL = 0x48304200;
static const uint32_t EHRPWM2_CMPHRMA = EHRPWM2_TBCTL+0x10;
static const uint32_t EHRPWM2_CMPA = EHRPWM2_TBCTL+0x12;
static const uint32_t EHRPWM2_CMPB = EHRPWM2_TBCTL+0x14;
static const uint32_t EHRPWM2_TBPRD = EHRPWM2_TBCTL+0xA;

enum aoutName
{
	AOUT1 = 1,
	AOUT2 = 2
};

enum pwmName
{
	PWM1 = 1,
	PWM2 = 2
};

//! @brief This enum is used for selecting ADC input.
enum adcName
{
  AIN0 = 0,
  AIN1 = 1,
  AIN2 = 2,
  AIN3 = 3,
  AIN4 = 4,
  AIN5 = 5,
  AIN6 = 6
};

typedef struct s_PIN {
  std::string name;   /*!< readable name of pin, i.e.: "GPIO1_21", see beaglebone user guide */
  uint32_t gpio_bank; /*!< which of the four gpio banks is this pin in, i.e.: GPIO1, r 0x4804C000 */
  uint8_t gpio; /*!< pin number on the am335x processor */
  uint8_t bank_id; /*!< pin number within each bank, should be 0-31 */
  std::string mux;    /*!< file name for setting mux */
} PIN;


static const PIN P9_22 = {"P9_22",   GPIO0,     2,      2,   "spi0_sclk"};
static const PIN P9_21 = {"P9_21",   GPIO0,     3,      3,   "spi0_d0"};
static const PIN P9_18 = {"P9_18",    GPIO0,     4,      4,   "spi0_d1"};
static const PIN P9_17 = {"P9_17",    GPIO0,     5,      5,   "spi0_cs0"};
static const PIN P9_42 = {"P9_42",     GPIO0,     7,      7,   "ecap0_in_pwm0_out"};
static const PIN P8_35 = {"P8_35",  GPIO0,     8,  	8,	 "lcd_data12"};
static const PIN P8_33 = {"P8_33",  GPIO0,     9,  	9,	 "lcd_data13"};
static const PIN P8_31 = {"P8_31",  GPIO0,     10, 	10,	 "lcd_data14"};
static const PIN P8_32 = {"P8_32",  GPIO0,     11, 	11,	 "lcd_data15"};
static const PIN P9_26 = {"P9_26",   GPIO0,     14,     14,  "uart1_rxd"};
static const PIN P9_24 = {"P9_24",   GPIO0,     15,     15,  "uart1_txd"};

static const PIN P9_41 = {"P9_41",     GPIO0,     20,     20,  "xdma_event_intr1"};
static const PIN P8_19 = {"P8_19",    GPIO0,     22, 	22,	 "gpmc_ad8"};
static const PIN P8_13 = {"P8_13",    GPIO0,     23, 	23,	 "gpmc_ad9"};
static const PIN P8_14 = {"P8_14",    GPIO0,     26, 	26,	 "gpmc_ad10"};
static const PIN P8_17 = {"P8_17",    GPIO0,     27, 	27,	 "gpmc_ad11"};

static const PIN P9_11 = {"P9_11",   GPIO0,     30,     30,  "gpmc_wait0"};
static const PIN P9_13 = {"P9_13",   GPIO0,     31,     31,  "gpmc_wpn"};
static const PIN P8_25 = {"P8_25",     GPIO1,     32, 	0,	 "gpmc_ad0"};
static const PIN P8_24 = {"P8_24",     GPIO1,     33, 	1,	 "gpmc_ad1"};
static const PIN P8_5  = {"P8_5",     GPIO1,     34, 	2,	 "gpmc_ad2"};
static const PIN P8_6  = {"P8_6",     GPIO1,     35, 	3,	 "gpmc_ad3"};
static const PIN P8_23 = {"P8_23",     GPIO1,     36, 	4,	 "gpmc_ad4"};
static const PIN P8_22 = {"P8_22",     GPIO1,     37, 	5,	 "gpmc_ad5"};
static const PIN P8_3  = {"P8_3",	 GPIO1,     38, 	6,	 "gpmc_ad6"};
static const PIN P8_4  = {"P8_4",     GPIO1,     39, 	7,	 "gpmc_ad7"};

static const PIN P8_12 = {"P8_12",    GPIO1,     44, 	12,	 "gpmc_ad12"};
static const PIN P8_11 = {"P8_11",    GPIO1,     45, 	13,	 "gpmc_ad13"};
static const PIN P8_16 = {"P8_16",    GPIO1,     46, 	14,	 "gpmc_ad14"};
static const PIN P8_15 = {"P8_15",    GPIO1,     47, 	15,	 "gpmc_ad15"};
static const PIN P9_15 = {"P9_15",    GPIO1,     48,     16,  "mii1_rxd3"};
static const PIN P9_23 = {"P9_23",    GPIO1,     49,     17,  "gpmc_a1"};
static const PIN P9_16 = {"P9_16",    GPIO1,     51,     19,  "gpmc_a3"};
static const PIN P9_14 = {"P8_14",    GPIO1,     50,     18,  "gpmc_a2"};


static const PIN P9_12 = {"P9_12",    GPIO1,     60,     28,  "gpmc_ben1"};
static const PIN P8_26 = {"P8_26",    GPIO1,     61, 	29,	 "gpmc_csn0"};
static const PIN P8_21 = {"P8_21",    GPIO1,     62, 	30,	 "gpmc_csn1"};
static const PIN P8_20 = {"P8_20",    GPIO1,     63, 	31,	 "gpmc_csn2"};
static const PIN P8_18 = {"P8_18",     GPIO2,     65, 	1,	 "gpmc_clk"};
static const PIN P8_7  = {"P8_7",      GPIO2,     66, 	2, 	 "gpmc_advn_ale"};
static const PIN P8_8  = {"P8_8",      GPIO2,     67, 	3,	 "gpmc_oen_ren"};
static const PIN P8_10 = {"P8_10",      GPIO2,     68, 	4,	 "gpmc_wen"};
static const PIN P8_9  = {"P8_9",      GPIO2,     69, 	5,	 "gpmc_ben0_cle"};
static const PIN P8_45 = {"P8_45",     GPIO2,     70, 	6,	 "lcd_data0"};
static const PIN P8_46 = {"P8_46",     GPIO2,     71, 	7,	 "lcd_data1"};
static const PIN P8_43 = {"P8_43",     GPIO2,     72, 	8,	 "lcd_data2"};
static const PIN P8_44 = {"P8_44",     GPIO2,     73, 	9,	 "lcd_data3"};
static const PIN P8_41 = {"P8_41",    GPIO2,     74, 	10,	 "lcd_data4"};
static const PIN P8_42 = {"P8_42",    GPIO2,     75, 	11,	 "lcd_data5"};
static const PIN P8_39 = {"P8_39",    GPIO2,     76, 	12,	 "lcd_data6"};
static const PIN P8_40 = {"P8_40",    GPIO2,     77, 	13,	 "lcd_data7"};
static const PIN P8_37 = {"P8_37",   GPIO2,     78, 	14,	 "lcd_data8"};
static const PIN P8_38 = {"P8_38",   GPIO2,     79, 	15,	 "lcd_data9"};
static const PIN P8_36 = {"P8_36",  GPIO2,     80, 	16,	 "lcd_data10"};
static const PIN P8_34 = {"P8_34",  GPIO2,     81, 	17,	 "lcd_data11"};
static const PIN P8_27 = {"P8_27",    GPIO2,     86, 	22,	 "lcd_vsync"};
static const PIN P8_29 = {"P8_29",    GPIO2,     87, 	23,	 "lcd_hsync"};
static const PIN P8_28 = {"P8_28",    GPIO2,     88, 	24,	 "lcd_pclk"};
static const PIN P8_30 = {"P8_30",    GPIO2,     89, 	25,	 "lcd_ac_bias_en"};

static const PIN P9_25 = {"P9_25",    GPIO3,    117,     21,  "mcasp0_ahclkx"};

static const std::string SLOTS_PATH = "/sys/devices/bone_capemgr.9/slots";


static const std::vector<PIN> gpios = boost::assign::list_of(P9_22)(P9_21)
				(P9_18)(P9_17)(P9_42)(P8_35)(P8_33)(P8_31)(P8_32)(P9_26)(P9_24)(P9_41)
				(P8_19)(P8_13)(P8_14)(P8_17)(P9_11)(P9_13)(P8_25)(P8_24)(P8_5)(P8_6)(P8_23)
				(P8_22)(P8_3)(P8_4)(P8_12)(P8_11)(P8_16)(P8_15)(P9_15)(P9_23)(P9_16)(P9_12)
				(P8_26)(P8_21)(P8_20)(P8_18)(P8_7)(P8_8)(P8_10)(P8_9)(P8_45)(P8_46)(P8_43)
				(P8_44)(P8_41)(P8_42)(P8_39)(P8_40)(P8_37)(P8_38)(P8_36)(P8_34)(P8_27)(P8_29)
				(P8_28)(P8_30)(P9_25);

class MatchesGPIOname
{
    std::string _NAME;

public:
    MatchesGPIOname(const std::string &NAME) : _NAME(NAME) {}

    bool operator()(const PIN &pin) const
    {
        return pin.name == _NAME;
    }
};

enum direction
{
	output = 0,
	input = 1,
	bothDirection = (input | output)
};
static const std::string dirArr[2] = {"out", "in"};
static const uint8_t PULLUP = 1;
static const uint8_t PULLDOWN = 0;
static const uint8_t DISABLED = 2;

static const std::string EXPORT_PATH = "/sys/class/gpio/export";
static const std::string UNEXPORT_PATH = "/sys/class/gpio/unexport";
static const std::string DIRECTION_PATH = "/sys/class/gpio/gpio";

//! @brief This enum is used for setting digital output value.
enum digitalValue
{
  low = 0,
  high = 1
};

//! @brief This enum is used for selecting working mode.
enum workingMode
{
  SecureMode = 0,
  FastMode = 1
};

static const std::string DEFAULT_CAPE_MGR_NUMBER = "8";
static const std::string DEFAULT_HELPER_NUMBER = "14";
static const std::string DEFAULT_OCP_NUMBER = "2";
static const std::string DEFAULT_SPI0_PINMUX = "48030000";
static const std::string DEFAULT_SPI1_PINMUX = "481a0000";
static const int FILE_COULD_NOT_OPEN_INT = -1;
static const std::string FILE_COULD_NOT_OPEN_STRING = "File Couldn\'t Open";
static const int GPIO_PIN_NOT_READY_INT = -2;
static const std::string GPIO_PIN_NOT_READY_STRING = "Gpio Pin Isn\'t Ready";
static const std::string PWM_TEST_NAME_NOT_FOUND = "PwmTestNameError";
static const std::string SEARCH_DIR_NOT_FOUND = "Not Found";
static const std::string UART_READ_FAILED = "UartReadError";
static const std::string UART_WRITE_FAILED = "UartWriteError";

//! @brief This enum is used for setting character size.
enum characterSize
{
  Char5 = 5,
  Char6 = 6,
  Char7 = 7,
  Char8 = 8,
  CharDefault = 0
};

//! @brief This enum is used for setting parity.
enum parity
{
  ParityNo = 0,
  ParityOdd = 1,
  ParityEven = 2,
  ParityDefault = -1
};

//! @brief This enum is used for setting stop bit(s) size.
enum stopBits
{
  StopOne = 1,
  StopTwo = 2,
  StopDefault = -1
};

//! @brief This enum is used for setting PWM polarity.
enum polarityType
{
  straight = 0,
  reverse = 1
};

//! @brief This enum is used for selecting time type (like PWM::setPeriodTime()
//! function).
enum timeType
{
  picosecond = -12,
  nanosecond = -9,
  microsecond = -6,
  milisecond = -3,
  second = 1
};

//! @brief This enum is used for setting run state (like PWM).
enum runValue
{
  stop = 0,
  run = 1
};

//! @brief This enum is used for setting i2c name.
enum i2cName
{
  I2C_0 = 0,
  I2C_1 = 1
};

//! @brief This enum is used for selecting i2c bus transaction type.
enum transactionType
{
  SMBUS_QUICK = 0,
  SMBUS_BYTE = 1,
  SMBUS_BYTE_DATA = 2,
  SMBUS_WORD_DATA = 3,
  SMBUS_PROC_CALL = 4,
  SMBUS_BLOCK_DATA = 5,
  SMBUS_I2C_BLOCK_BROKEN = 6,
  SMBUS_BLOCK_PROC_CALL = 7,
  SMBUS_I2C_BLOCK_DATA = 8
};

//! @brief This enum is used for setting spi name.
enum spiName
{
  SPI0_0 = 0,
  SPI0_1 = 1,
  SPI1_0 = 2,
  SPI1_1 = 3
};

//! @brief This enum is used for setting spi mode.
enum spiMode
{
  SpiDefault = 0x00,
  SpiPhase = 0x01,
  SpiPolarity = 0x02,
  SpiChipSelectHigh = 0x04,
  SpiLsbFirst = 0x08,
  Spi3Wire = 0x10,
  SpiLoop = 0x20,
  SpiNoChipSelect = 0x40,
  SpiReady = 0x80,
  SpiMode0 = (0|0),
  SpiMode1 = (0|SpiPhase),
  SpiMode2 = (SpiPolarity|0),
  SpiMode3 = (SpiPolarity|SpiPhase)
};

//! @brief This enum is used for selecting file open mode.
enum openMode
{
  ReadOnly = 0,
  WriteOnly = 1,
  ReadWrite = 2,
  Append = 4,
  Truncate = 8,
  NonBlock = 16
};

//! @brief This enum is used for selecting UART name.
enum uartName
{
  UART1 = 1,
  UART2 = 2,
  UART4 = 4,
  UART5 = 5
};

//! @brief This enum is used for selecting apply mode of uart property's changes.
enum uartApplyMode
{
  ApplyNow = 0,
  ApplyDrain = 1,
  ApplyFlush = 2
};

//! @brief This enum is used for setting baud rate.
enum baudRate
{
  Baud0 = 0,
  Baud50 = 1,
  Baud75 = 2,
  Baud110 = 3,
  Baud134 = 4,
  Baud150 = 5,
  Baud200 = 6,
  Baud300 = 7,
  Baud600 = 8,
  Baud1200 = 9,
  Baud1800 = 10,
  Baud2400 = 11,
  Baud4800 = 12,
  Baud9600 = 13,
  Baud19200 = 14,
  Baud38400 = 15
};

static const float ADC_CONSTANT = 0.819824219F; //In mV per count
static const uint8_t DATA_UPPER_BYTE_MASK  = 0xF;
#endif // !defined(_DEFINITIONS_HEADER_)
