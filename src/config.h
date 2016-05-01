// Cpu frequency for util/delay.h
#define F_CPU 8000000

// Half of delay in main execution loop, given in microseconds.
#define LOOP_DELAY 50

// Half length of indicator led on-off sequence. In other words, the time
// the indicator is lit and darkened. Given in units of LOOP_DELAY.
#define INDICATOR_HALF_PERIOD 8000

// Half length of indicator led on-off sequence when in sensor alarm move. In
// other words, the time the indicator is lit and darkened. Given in units of
// LOOP_DELAY.
#define ALARM_HALF_PERIOD 1200

// Time between stepping the motor. Given in units of LOOP_DELAY
#define STEP_PERIOD 4

//Enables debug messaging
#define DEBUG
