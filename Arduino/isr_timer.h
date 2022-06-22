#ifndef ISR_TIMER_H
#define ISR_TIMER_H

#include <TimerOne.h>

static volatile uint16_t isr_timer_count = 0;

void isr_timer(){
    // Executed once every 200ms
    if((isr_timer_count % 200) == 0 || (isr_timer_count % 200) == 200){
        if((gpio_enable_sys & (1 << 0)) && gpio_read(GPIO_CONV_A)){
            gpio_enable_sys &= ~(1 << 0);
            gpio_isr_count[0]++;
        }

        if((gpio_enable_sys & (1 << 1)) && gpio_read(GPIO_CONV_B)){
            gpio_enable_sys &= ~(1 << 1);
            gpio_isr_count[1]++;
        }
    }

    // Executed once every 1500ms
    if((isr_timer_count % 1500) == 0 || (isr_timer_count % 1500) == 1500){
        if( (gpio_enable_sys & (1 << 2)) && gpio_read(GPIO_CONV_A)){
            gpio_enable_sys &= ~(1 << 2);
        }

        if( (gpio_enable_sys & (1 << 3)) && gpio_read(GPIO_CONV_B)){
            gpio_enable_sys &= ~(1 << 3);
        }
    }

    // Executed once every 2ms
    if((isr_timer_count % 2) == 0){
        OPC_LOOP_PROCESS();
    }

    if(isr_timer_count <= 7500) isr_timer_count++;
    else isr_timer_count = 0;
}

static void init_isr_timer(){
  Timer1.initialize(1000);
  Timer1.attachInterrupt(isr_timer);
}

#endif // ISR_TIMER_H