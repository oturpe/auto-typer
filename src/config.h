// This is the configuration file. Ideally, any configuration and calibration
// of the device should be done by changing this file only.

// Needed by util/delay.h
#define F_CPU 1000000UL

// Delay between two executions of main loop, given in millisecond.
#define LOOP_DELAY 50

// Half length of one complete indicator period. In other words, the time the
// indicator spends on and off. Given in units of LOOP_DELAY.
#define INDICATOR_HALF_PERIOD 10

// The number of coils
#define COIL_COUNT 5

// Coil duty cycle. Given in units of LOOP_DELAY
#define COIL_1_OFF_PERIOD 20
#define COIL_1_ON_PERIOD 5

#define COIL_WAIT_INITIAL 50

#define COIL_MIN_OFF_PERIOD 2
#define COIL_MAX_OFF_PERIOD 12
#define COIL_MIN_ON_PERIOD 2
#define COIL_MAX_ON_PERIOD 3

// Indicator pin data direction and data ports and pins
#define INDICATOR_DATA_DIR DDRB
#define INDICATOR_DATA_DIR_PIN DDB0
#define INDICATOR_DATA PORTB
#define INDICATOR_DATA_PIN PORTB0

// Coil data direction and data ports and pins
#define COIL_1_DATA_DIR DDRD
#define COIL_1_DATA_DIR_PIN DDD1
#define COIL_1_DATA PORTD
#define COIL_1_DATA_PIN PORTD1

#define COIL_2_DATA_DIR DDRD
#define COIL_2_DATA_DIR_PIN DDD2
#define COIL_2_DATA PORTD
#define COIL_2_DATA_PIN PORTD2

#define COIL_3_DATA_DIR DDRD
#define COIL_3_DATA_DIR_PIN DDD3
#define COIL_3_DATA PORTD
#define COIL_3_DATA_PIN PORTD3

#define COIL_4_DATA_DIR DDRD
#define COIL_4_DATA_DIR_PIN DDD4
#define COIL_4_DATA PORTD
#define COIL_4_DATA_PIN PORTD4

#define COIL_5_DATA_DIR DDRD
#define COIL_5_DATA_DIR_PIN DDD5
#define COIL_5_DATA PORTD
#define COIL_5_DATA_PIN PORTD5
