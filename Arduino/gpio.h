#ifndef GPIO_H
#define GPIO_H

#define ADDR_BUZZER_A   (1 << 0)
#define ADDR_BUZZER_B   (1 << 1)
#define ADDR_CONV_A     (1 << 6)
#define ADDR_CONV_B     (1 << 7)
#define ADDR_LED_ID_A   (1 << 0)
#define ADDR_LED_ID_B   (1 << 1)

#define ADDR_PORT_CONV      PORTD
#define ADDR_PORT_LED       PORTB
#define ADDR_PORT_BUZZER    PORTC

#define ADDR_PIN_CONV      PIND
#define ADDR_PIN_LED       PINB
#define ADDR_PIN_BUZZER    PINC

#define GPIO_PROX_A     2
#define GPIO_PROX_B     3

#define GPIO_BUZZER_A   0
#define GPIO_BUZZER_B   1
#define GPIO_CONV_A     2
#define GPIO_CONV_B     3
#define GPIO_LED_ID_A   4
#define GPIO_LED_ID_B   5

static volatile uint8_t gpio_isr_count[3] = {0};
static volatile uint8_t gpio_enable_sys = 0x00;

static void isr_proximity_a(void){
    gpio_enable_sys |= (1 << 0) | (1 << 2);
}

static void isr_proximity_b(void){
    gpio_enable_sys |= (1 << 1) | (1 << 3);
}

static void init_gpio_setup(){
    DDRD |= ADDR_CONV_A | ADDR_CONV_B;
    DDRB |= ADDR_LED_ID_A | ADDR_LED_ID_B;
    DDRC |= ADDR_BUZZER_A | ADDR_BUZZER_B;

    attachInterrupt(digitalPinToInterrupt(GPIO_PROX_A), isr_proximity_a, FALLING);
    attachInterrupt(digitalPinToInterrupt(GPIO_PROX_B), isr_proximity_b, FALLING);
}

static void gpio_set(uint8_t gpio){
    /*
    * GPIO List :
    * 0 : Buzzer A
    * 1 : Buzzer B
    * 2 : Conveyor A
    * 3 : Conveyor B
    * 4 : LED ID A
    * 5 : LED ID B
    */

    switch(gpio){
        case GPIO_BUZZER_A:
            ADDR_PORT_BUZZER |= ADDR_BUZZER_A;
        break;

        case GPIO_BUZZER_B:
            ADDR_PORT_BUZZER |= ADDR_BUZZER_B;
        break;

        case GPIO_CONV_A:
            ADDR_PORT_CONV |= ADDR_CONV_A;
        break;

        case GPIO_CONV_B:
            ADDR_PORT_CONV |= ADDR_CONV_B;
        break;

        case GPIO_LED_ID_A:
            ADDR_PORT_LED |= ADDR_LED_ID_A;
        break;

        case GPIO_LED_ID_B:
            ADDR_PORT_LED |= ADDR_LED_ID_B;
        break;
    }
}

static void gpio_reset(uint8_t gpio){
    /*
    * GPIO List :
    * 0 : Buzzer A
    * 1 : Buzzer B
    * 2 : Conveyor A
    * 3 : Conveyor B
    * 4 : LED ID A
    * 5 : LED ID B
    */

    switch(gpio){
        case GPIO_BUZZER_A:
            ADDR_PORT_BUZZER &= ~ADDR_BUZZER_A;
        break;

        case GPIO_BUZZER_B:
            ADDR_PORT_BUZZER &= ~ADDR_BUZZER_B;
        break;

        case GPIO_CONV_A:
            ADDR_PORT_CONV &= ~ADDR_CONV_A;
        break;

        case GPIO_CONV_B:
            ADDR_PORT_CONV &= ~ADDR_CONV_B;
        break;

        case GPIO_LED_ID_A:
            ADDR_PORT_LED &= ~ADDR_LED_ID_A;
        break;

        case GPIO_LED_ID_B:
            ADDR_PORT_LED &= ~ADDR_LED_ID_B;
        break;
    }
}

static uint8_t gpio_read(uint8_t gpio){
    /*
    * GPIO List :
    * 0 : Buzzer A
    * 1 : Buzzer B
    * 2 : Conveyor A
    * 3 : Conveyor B
    * 4 : LED ID A
    * 5 : LED ID B
    */

    switch(gpio){
        case GPIO_BUZZER_A:
            return (ADDR_PIN_BUZZER & ADDR_BUZZER_A);
        break;

        case GPIO_BUZZER_B:
            return (ADDR_PIN_BUZZER & ADDR_BUZZER_B);
        break;

        case GPIO_CONV_A:
            return (ADDR_PIN_CONV & ADDR_CONV_A);
        break;

        case GPIO_CONV_B:
            return (ADDR_PIN_CONV & ADDR_CONV_B);
        break;

        case GPIO_LED_ID_A:
            return (ADDR_PIN_LED & ADDR_LED_ID_A);
        break;

        case GPIO_LED_ID_B:
            return (ADDR_PIN_LED & ADDR_LED_ID_B);
        break;

        default:
            return 0;
        break;
    }
}

#endif // GPIO_H