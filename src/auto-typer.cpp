// Mechanical typewriter automation
//
// Author: Otto Urpelainen
// Email: oturpe@iki.fi
// Date: 2016-06-22

#include "Atmega8Utils.h"

#include "config.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>

/// \brief
///    Toggles the indicator led state.
void toggleIndicator() {
    static bool lit;

    if (lit) {
        INDICATOR_DATA &= ~BV(INDICATOR_DATA_PIN);
    }
    else {
        INDICATOR_DATA |= BV(INDICATOR_DATA_PIN);
    }

    lit = !lit;
}


enum Phase {
    TYPING,
    RETURNING
};
Phase phase = TYPING;

ISR(PCINT0_vect)
{
    if (END_SWITCH_INPUT & BV(END_SWITCH_INPUT_PIN)) {
        phase = RETURNING;
        MOTOR_OUTPUT_COMPARE = 0x00;
    }

    if (START_SWITCH_INPUT & BV(START_SWITCH_INPUT_PIN)) {
        phase = TYPING;
    }
}

int main() {
    INDICATOR_DATA_DIR |= BV(INDICATOR_DATA_DIR_PIN);

    // Coils as output
    COIL_1_DATA_DIR |= BV(COIL_1_DATA_DIR_PIN);
    COIL_2_DATA_DIR |= BV(COIL_2_DATA_DIR_PIN);
    COIL_3_DATA_DIR |= BV(COIL_3_DATA_DIR_PIN);
    COIL_4_DATA_DIR |= BV(COIL_4_DATA_DIR_PIN);
    COIL_5_DATA_DIR |= BV(COIL_5_DATA_DIR_PIN);

    // Pullups for switches
    START_SWITCH_DATA |= BV(START_SWITCH_DATA_PIN);
    END_SWITCH_DATA |= BV(END_SWITCH_DATA_PIN);

    // Enable pin change interrupts for switch pins
    PCMSK0 |= BV(PCINT1) | BV(PCINT2);
    PCICR |= BV(PCIE0);
    sei();

    // Enable motor phase correct non-inverting pwm output
    Atmega8::initializeTimer0(
        Atmega8::PSV_8,
        Atmega8::PWM_PHASE_CORRECT,
        Atmega8::TOP_00FF
    );
    MOTOR_DATA_DIR |= BV(MOTOR_DATA_DIR_PIN);
    TCCR0A |= BV(COM0A1);

    uint16_t indicatorCounter = 0;
    uint16_t coilWait = COIL_WAIT_INITIAL;
    bool coilPulling = false;
    uint8_t activeCoil = 1;

    // Recover from condition where carriage is at the end in the beginning.
    if (END_SWITCH_INPUT & BV(END_SWITCH_INPUT_PIN)) {
        phase = RETURNING;
    }

    while (true) {
        if (indicatorCounter % INDICATOR_HALF_PERIOD == 0) {
            toggleIndicator();
        }
        indicatorCounter++;

        if (coilWait > 0) {
            coilWait--;
        }
        else if (coilPulling) {
            switch (activeCoil) {
            case 1:
                COIL_1_DATA &= ~BV(COIL_1_DATA_PIN);
                break;
            case 2:
                COIL_2_DATA &= ~BV(COIL_2_DATA_PIN);
                break;
            case 3:
                COIL_3_DATA &= ~BV(COIL_3_DATA_PIN);
                break;
            case 4:
                COIL_4_DATA &= ~BV(COIL_4_DATA_PIN);
                break;
            case 5:
                COIL_5_DATA &= ~BV(COIL_5_DATA_PIN);
                break;
            }

            coilPulling = false;
            activeCoil = rand() % (COIL_COUNT + 1);
            uint8_t uncertainty = COIL_MAX_OFF_PERIOD - COIL_MIN_OFF_PERIOD;
            coilWait = COIL_MIN_OFF_PERIOD + (rand() % uncertainty);
        }
        else if (phase == TYPING) {
            switch (activeCoil) {
            case 1:
                COIL_1_DATA |= BV(COIL_1_DATA_PIN);
                break;
            case 2:
                COIL_2_DATA |= BV(COIL_2_DATA_PIN);
                break;
            case 3:
                COIL_3_DATA |= BV(COIL_3_DATA_PIN);
                break;
            case 4:
                COIL_4_DATA |= BV(COIL_4_DATA_PIN);
                break;
            case 5:
                COIL_5_DATA |= BV(COIL_5_DATA_PIN);
                break;
            }

            coilPulling = true;
            uint8_t uncertainty = COIL_MAX_ON_PERIOD - COIL_MIN_ON_PERIOD;
            coilWait = COIL_MIN_ON_PERIOD + (rand() % uncertainty);
        }

        MOTOR_OUTPUT_COMPARE = (phase == RETURNING) ? MOTOR_SPEED : 0x00;

        _delay_ms(LOOP_DELAY);
    }
}
