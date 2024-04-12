#include "mbed.h"
#include "arm_book_lib.h"

#define TEST_DIG 0 
#define TEST_BUS 1 
#define TEST_X (TEST_BUS) 

int main()
{
    #if (TEST_X == TEST_DIG)
    DigitalIn gasDetector(D2);
    DigitalIn overTempDetector(D3);
    DigitalIn aButton(D4);
    DigitalIn bButton(D5);
    DigitalIn cButton(D6);
    DigitalIn dButton(D7);

    DigitalOut alarmLed(LED1);

    gasDetector.mode(PullDown);
    overTempDetector.mode(PullDown);
    aButton.mode(PullDown);
    bButton.mode(PullDown);
    cButton.mode(PullDown);
    dButton.mode(PullDown);

    alarmLed = OFF;

    bool alarmState = OFF;

    while (true) {

        if ( gasDetector || overTempDetector ) {
            alarmState = ON;
        }

        alarmLed = alarmState;

        if ( aButton && bButton && !cButton && !dButton) {
            alarmState = OFF;
        }
    }

    #endif

    #if (TEST_X == TEST_BUS)

    #endif
}