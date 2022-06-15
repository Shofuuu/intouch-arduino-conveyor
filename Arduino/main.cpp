#include <Arduino.h>
#include "gpio.h"
#include "opc_setup.h"
#include "isr_timer.h"

void setup() {
    Serial.begin(9600);
    while(!Serial);

    init_opc_setup();
    init_gpio_setup();
    init_isr_timer();
}

void loop() { /* Leave it Empty*/ }