// Add description here
//
// Author: N.N.
// Email: n.n@example.com
// Date: 1900-01-01

#include "Atmega88pUtils.h"

#include "config.h"

#include <avr/io.h>
#include <util/delay.h>

uint32_t indicatorCounter = 0;

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

    while (true) {
        if (indicatorCounter % INDICATOR_HALF_PERIOD == 0) {
            toggleIndicator();
        }
        indicatorCounter++;

        _delay_ms(LOOP_DELAY);
    }
}
