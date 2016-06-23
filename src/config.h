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

#define MOTOR_SPEED 0x50

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

#define START_SWITCH_DATA PORTB
#define START_SWITCH_DATA_PIN PORTB1
#define START_SWITCH_INPUT PINB
#define START_SWITCH_INPUT_PIN PINB1

#define END_SWITCH_DATA PORTB
#define END_SWITCH_DATA_PIN PORTB2
#define END_SWITCH_INPUT PINB
#define END_SWITCH_INPUT_PIN PINB2

#define MOTOR_DATA_DIR DDRD
#define MOTOR_DATA_DIR_PIN DDD6
#define MOTOR_DATA PORTD
#define MOTOR_DATA_PIN PORTD6
#define MOTOR_OUTPUT_COMPARE OCR0A

