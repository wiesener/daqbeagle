curPath = pwd;
numOfBlocks = 1; % DIN, DOUT, AIN, AOUT, PWM

% initialize structure
def = struct([]);

% generate AINblock files
def{1} = legacy_code('initialize');
def{1}.SFunctionName = 'AIN';
def{1}.StartFcnSpec  = 'createADC(void** work1)';
def{1}.OutputFcnSpec = ' outputADC(void** work1, double y1[7])';
def{1}.TerminateFcnSpec = 'deleteADC(void** work1)';
def{1}.IncPaths = {strcat(curPath)};
def{1}.SrcPaths = {strcat(curPath)};
def{1}.HeaderFiles   = {'ADC.hpp', 'ADCblock.hpp', 'MAPhelper.hpp', 'MAP.hpp', 'Definitions.hpp'};
def{1}.SourceFiles   = {'ADC.cpp', 'MAP.cpp'};
def{1}.Options.language = 'C++';
def{1}.SampleTime = 'parameterized';
def{1}.Options.useTlcWithAccel = false;
legacy_code('generate_for_sim', def{1});
legacy_code('sfcn_tlc_generate', def{1});

% generate DOUTblock - digital output
def{2} = legacy_code('initialize');
def{2}.SFunctionName = 'DOUT';
def{2}.StartFcnSpec  = 'createDOUT(void** work1, uint8 p1[], int32 size(p1, 1))';
def{2}.OutputFcnSpec = 'outputDOUT(void** work1, uint8 u1[size(p1, 1)])';
def{2}.TerminateFcnSpec = 'deleteDOUT(void** work1)';
def{2}.IncPaths = {curPath};
def{2}.SrcPaths = {curPath};
def{2}.HeaderFiles   = {'GPIO.hpp', 'DOUTblock.hpp', 'MAPhelper.hpp', 'MAP.hpp', 'Definitions.hpp'};
def{2}.SourceFiles   = {'GPIO.cpp', 'MAP.cpp'};
def{2}.Options.language = 'C++';
def{2}.SampleTime = 'parameterized';
def{2}.Options.useTlcWithAccel = false;
legacy_code('generate_for_sim', def{2});
legacy_code('sfcn_tlc_generate', def{2});

% generate DINblock - digital input
def{3} = legacy_code('initialize');
def{3}.SFunctionName = 'DIN';
def{3}.StartFcnSpec  = 'createDIN(void** work1, uint8 p1[], int32 size(p1, 1))';
def{3}.OutputFcnSpec = 'outputDIN(void** work1, uint8 y1[size(p1, 1)])';
def{3}.TerminateFcnSpec = 'deleteDIN(void** work1)';
def{3}.IncPaths = {curPath};
def{3}.SrcPaths = {curPath};
def{3}.HeaderFiles   = {'GPIO.hpp', 'DINblock.hpp', 'MAPhelper.hpp', 'MAP.hpp', 'Definitions.hpp'};
def{3}.SourceFiles   = {'GPIO.cpp', 'MAP.cpp'};
def{3}.Options.language = 'C++';
def{3}.SampleTime = 'parameterized';
def{3}.Options.useTlcWithAccel = false;
legacy_code('generate_for_sim', def{3});
legacy_code('sfcn_tlc_generate', def{3});

% generate AOUTblock files
def{4} = legacy_code('initialize');
def{4}.SFunctionName = 'AOUT';
def{4}.StartFcnSpec  = 'createAOUT(void** work1)';
def{4}.OutputFcnSpec = 'void outputAOUT(void** work1, double u1[2])';
def{4}.TerminateFcnSpec = 'deleteAOUT(void** work1)';
def{4}.IncPaths = {strcat(curPath)};
def{4}.SrcPaths = {strcat(curPath)};
def{4}.HeaderFiles   = {'DAC.hpp', 'DACblock.hpp', 'MAPhelper.hpp', 'MAP.hpp', 'Definitions.hpp'};
def{4}.SourceFiles   = {'DAC.cpp', 'MAP.cpp'};
def{4}.Options.language = 'C++';
def{4}.SampleTime = 'parameterized';
def{4}.Options.useTlcWithAccel = false;
legacy_code('generate_for_sim', def{4});
legacy_code('sfcn_tlc_generate', def{4});

% generate PWMblock files
def{5} = legacy_code('initialize');
def{5}.SFunctionName = 'PWM';
def{5}.StartFcnSpec  = 'createPWM(void** work1, double p1)';
def{5}.OutputFcnSpec = 'void outputPWM(void** work1, double u1[2])';
def{5}.TerminateFcnSpec = 'deletePWM(void** work1)';
def{5}.IncPaths = {strcat(curPath)};
def{5}.SrcPaths = {strcat(curPath)};
def{5}.HeaderFiles   = {'EHRPWM2.hpp', 'PWMblock.hpp', 'MAPhelper.hpp', 'MAP.hpp', 'Definitions.hpp'};
def{5}.SourceFiles   = {'EHRPWM2.cpp', 'MAP.cpp'};
def{5}.Options.language = 'C++';
def{5}.SampleTime = 'parameterized';
def{5}.Options.useTlcWithAccel = false;
legacy_code('generate_for_sim', def{5});
legacy_code('sfcn_tlc_generate', def{5});

% generate rtwmakecfg script
legacy_code('rtwmakecfg_generate', cell2mat(def));
addpath(curPath);
