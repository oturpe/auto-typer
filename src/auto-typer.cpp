// Mechanical typewriter automation
//
// Author: Otto Urpelainen
// Email: oturpe@iki.fi
// Date: 2016-06-22

#include "Atmega88pUtils.h"

#include "config.h"

#include <avr/io.h>
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


int main() {
    INDICATOR_DATA_DIR |= BV(INDICATOR_DATA_DIR_PIN);

    COIL_1_DATA_DIR |= BV(COIL_1_DATA_DIR_PIN);
    COIL_2_DATA_DIR |= BV(COIL_2_DATA_DIR_PIN);
    COIL_3_DATA_DIR |= BV(COIL_3_DATA_DIR_PIN);
    COIL_4_DATA_DIR |= BV(COIL_4_DATA_DIR_PIN);
    COIL_5_DATA_DIR |= BV(COIL_5_DATA_DIR_PIN);

    uint16_t indicatorCounter = 0;
    uint16_t coilWait = COIL_WAIT_INITIAL;
    bool coilPulling = false;
    uint8_t activeCoil = 1;

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
        else {
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

        _delay_ms(LOOP_DELAY);
    }
}
