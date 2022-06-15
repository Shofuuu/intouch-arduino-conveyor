#ifndef GPIO_H
#define GPIO_H

#define GPIO_BUZZER_A   4
#define GPIO_BUZZER_B   5
#define GPIO_CONV_A     6
#define GPIO_CONV_B     7
#define GPIO_LED_ID_A   8
#define GPIO_LED_ID_B   9
#define GPIO_PROX_A     2
#define GPIO_PROX_B     3

static volatile uint8_t gpio_isr_count[3] = {0};
static volatile uint8_t gpio_enable_sys = 0x00;

static void isr_proximity_a(void){
    gpio_enable_sys |= (1 << 0) | (1 << 2);
}

static void isr_proximity_b(void){
    gpio_enable_sys |= (1 << 1) | (1 << 3);
}

static void init_gpio_setup(){
    const uint8_t out_pin_map[] = {GPIO_BUZZER_A, GPIO_BUZZER_B, GPIO_CONV_A, GPIO_CONV_B, GPIO_LED_ID_A, GPIO_LED_ID_B};
    const uint8_t in_pin_map[] = {GPIO_PROX_A, GPIO_PROX_B};

    for(uint8_t pin=0;pin<sizeof(out_pin_map);pin++){
        pinMode(out_pin_map[pin], OUTPUT);
    }
    for(uint8_t pin=0;pin<sizeof(in_pin_map);pin++){
        pinMode(in_pin_map[pin], INPUT);
    }

    attachInterrupt(digitalPinToInterrupt(2), isr_proximity_a, FALLING);
    attachInterrupt(digitalPinToInterrupt(3), isr_proximity_b, FALLING);
}

#endif // GPIO_H