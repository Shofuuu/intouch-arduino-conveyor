#ifndef OPC_SETUP_H
#define OPC_SETUP_H

#include "avropc.h"

#define OPC_LOOP_PROCESS()  __opc.processOPCCommands()

#define SYSTEM_TARGET_A     gpio_isr_count[2]
#define SYSTEM_REALTIME_A   gpio_isr_count[0]

static bool cb_conveyor_a(const char *itemID, const opcOperation opcOP, const bool value){
    if(opcOP == opc_opwrite){
        if(value) gpio_set(GPIO_CONV_A);
        else gpio_reset(GPIO_CONV_A);

        if(!value){
            SYSTEM_REALTIME_A = 0;
            SYSTEM_TARGET_A = 0;
        }
    }

    return gpio_read(GPIO_CONV_A);
}

static bool cb_conveyor_b(const char *itemID, const opcOperation opcOP, const bool value){
    if(opcOP == opc_opwrite){
        if(value) gpio_set(GPIO_CONV_B);
        else gpio_reset(GPIO_BUZZER_B);

        if(!value) gpio_isr_count[1] = 0;
    }

    return gpio_read(GPIO_CONV_B);
}

static int cb_realtime_count(const char *itemID, const opcOperation opcOP, const int value){
    return (SYSTEM_REALTIME_A/2);
}

static bool cb_sensor_status_a(const char *itemID, const opcOperation opcOP, const bool value){
    return (gpio_enable_sys & (1 << 2)) && (PIND & ADDR_CONV_A);
}

static bool cb_sensor_status_b(const char *itemID, const opcOperation opcOP, const bool value){
    return (gpio_enable_sys & (1 << 3)) && (PIND & ADDR_CONV_B);
}

static int cb_system_target_a(const char *itemID, const opcOperation opcOP, const int value){
    if(opcOP == opc_opwrite){
        if((PIND & ADDR_CONV_A))
            SYSTEM_TARGET_A = value;
    }

    return value;
}

static OPCSerial __opc;

static void init_opc_setup(){
    __opc.setup();

    // Control conveyor
    __opc.addItem("conveyor_a", opc_readwrite, opc_bool, cb_conveyor_a);
    __opc.addItem("conveyor_b", opc_readwrite, opc_bool, cb_conveyor_b);

    // System parameter status
    __opc.addItem("realtime_count", opc_readwrite, opc_int, cb_realtime_count);
    __opc.addItem("sensor_status_a", opc_readwrite, opc_bool, cb_sensor_status_a);
    __opc.addItem("sensor_status_b", opc_readwrite, opc_bool, cb_sensor_status_b);
    __opc.addItem("system_target_a", opc_readwrite, opc_int, cb_system_target_a);
}

#endif // OPC_SETUP_H