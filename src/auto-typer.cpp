// Fog mover
//
// Automatically types something on a mechanical typewriter by pulling the keys
// with coils.
//
// TODO: More detailed description
//
// Created on: 2016-04-22
// Author: Otto Urpelainen
// Email: oturpe@iki.fi

#include "Attiny2313Utils.h"

#include "config.h"

#include <avr/io.h>
#include <util/delay.h>

#ifdef DEBUG
#include "Debug.h"
#endif

/// \brief Turns the indicator led on of off
///
/// \param lit
///    If led is turned on. Otherwise it is turned off.
inline void setIndicator(bool lit) {
  if (lit)
    PORTD |= BV(PORTD0);
  else
    PORTD &= ~BV(PORTD0);
}

/// \brief
///    Never ending function that does not do anything excepts blinks the
///    indicator alarmingly.
inline void alarm() {
    while (true) {
        for(int i = 0;i < ALARM_HALF_PERIOD; i++) {
            _delay_us(LOOP_DELAY);
        }

        setIndicator(true);

        for(int i = 0;i < ALARM_HALF_PERIOD; i++) {
            _delay_us(LOOP_DELAY);
        }

        setIndicator(false);
    }
}

/// \brief
///    Reads sensors and sets the direction of rotation accordingly.
inline void readSensors() {
    bool bottomReached = PINB & BV(PINB0);
    bool topReached = PINB & BV(PINB1);

    if (topReached && bottomReached) {
        // Something is wrong with sensors. Stop.
        alarm();
    }

    if (topReached) {
        PORTD |= BV(PORTD3);
    }
    else if (bottomReached) {
        PORTD &= ~BV(PORTD3);
    }

}

/// \brief
///    Moves the motor one step ahead
inline void step() {
    PORTD |= BV(PORTD4);
    _delay_us(50);
    PORTD &= ~BV(PORTD4);
}

int main() {
    #ifdef DEBUG
        /* TODO: implement debugging
        Debug debug(DEBUG_FREQ);
        */
    #endif

    // Set output pins:
    //    D0 (indicator)
    //    D3 (motor dir input)
    //    D4 (motor step input)
        DDRD |= BV(DDD0) | BV(DDD3) | BV(DDD4);

    bool indicatorLit = false;
    uint16_t counter = 0;
    while(true) {
        counter += 1;
        _delay_us(LOOP_DELAY);

        if(counter % INDICATOR_HALF_PERIOD == 0) {
            indicatorLit = !indicatorLit;
            setIndicator(indicatorLit);
        }

        if(counter % STEP_PERIOD == 0) {
            readSensors();
            step();
        }
    }
}
