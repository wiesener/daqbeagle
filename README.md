# daqbeagle
The daqbeagle is a data aquisition device for analog and digital signals and aswell combined 
with real-time capable target for simulink/matlab external mode. 
Together with a small shield it consists of three parts:

## 1. ERT linux target for beaglebone black
The targte is based on the lintarget from http://lintarget.sourceforge.net/. The main modifications are:
- bugfixes for multipla sample rates
- changed policy for C++ usage
- CTRL+C signal listener for safe abort of application
- Compile flags for non-external mode simulation

## 2. DAQ library for beaglebone black
The library consists of 5 blocks for data aquisition of

- 7 ADC channels at 12 bit
- 8 digital outputs
- 8 digital inputs
- 2 PWM outputs
- 2 DAC outputs (only working with shield or lowpass filter)

All blocks are build using the legacy code tool. So first the daqbeagle.m script has to be executed.
Inside the blocks one memory map for all blocks is used. So the device tree overlay is only used for 
configuration. This makes it possible to run the blocks up to 1 kHz with only slight overruns. 

## 3. DAQ shield for beaglebone black.
The shield is a small (8x8 cm) pcb which includes level-shifters for the ADC (-5V-5V, -10-10V), 
logic level shifters (3.3V -> 5V) and the output lowpass filter for the DAC. Furthermore it is needed to have 
an tranceiver for all sysconfig pins at the P8 header of the BBB to use them after boot.
Inside the beaglebone folder there are all config and dtbo files included which are needed to run the shield.
 
The software is released under GPL.