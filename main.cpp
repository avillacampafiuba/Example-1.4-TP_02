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

        if ( aButton && bButton && !cButton && !dButton) { //1100 -> 12 -> 0xC
            alarmState = OFF;
        }
    }

    #endif

    #if (TEST_X == TEST_BUS)
        //En este caso, podria ser conveniente usar PortIn para gasDetector y overTempDetector, pero dado que D2 y D3 no pertenecen al mismo puerto
        //no es posible, una opcion seria cambiar los pines para que esten en ese puerto y simplificar la condicion de estas entradas.

        // Usamos BusIn tanto para las alarmas como para la desactivación.

        BusIn buttonBus(D4, D5, D6, D7); // Pines de los botones en un BusIn
        BusIn Alarmas(D2, D3);

        DigitalOut alarmLed(LED1);

        buttonBus.mode(PullDown);
        Alarmas.mode(PullDown);

        alarmLed = OFF;

        bool alarmState = OFF;

        int gasDetector, overTempDetector, medicion_alarmas;

        while (true) {

            medicion_alarmas = Alarmas.read();
            gasDetector = medicion_alarmas & 0b00000001;
            overTempDetector = (medicion_alarmas & 0b00000010) >> 1;
            
            if (gasDetector || overTempDetector) {
                alarmState = ON;
            }

            alarmLed = alarmState;

            if (buttonBus == 0xC) { // Si los botones son 1100  (0xC en hexa)
                alarmState = OFF;
            }

            printf("gasDetector: %d\n", gasDetector);
            printf("overTempDetector: %d\n", overTempDetector);
            printf("alarmLED: %d\n\n", alarmLed.read());
        }
    #endif
}
