/**
 * @file app_ir.cpp
 * @author ちみ/Chimi(https://github.com/Chimipupu)
 * @brief 赤外線リモコン アプリ
 * @version 0.1
 * @date 2024-11-22
 * 
 * @copyright Copyright (c) 2024 ちみ/Chimi(https://github.com/Chimipupu)
 * 
 */

#include "app_ir.hpp"
#define IR_RX_PIN    15

#ifdef __IR_ENABLE__
#include <IRremote.hpp>
#endif /* __IR_ENABLE__ */

static void ir_decode(uint16_t command);

static void ir_decode(uint16_t command)
{
#ifdef __IR_ENABLE__
    switch (command)
    {
        case IR_RX_BTN_COMMAND_0:
            DEBUG_RTOS_PRINTF("IR RX BTN0 Command\n");
            break;
        case IR_RX_BTN_COMMAND_1:
            DEBUG_RTOS_PRINTF("IR RX BTN1 Command\n");
            break;
        case IR_RX_BTN_COMMAND_2:
            DEBUG_RTOS_PRINTF("IR RX BTN2 Command\n");
            break;
        case IR_RX_BTN_COMMAND_3:
            DEBUG_RTOS_PRINTF("IR RX BTN3 Command\n");
            break;
        case IR_RX_BTN_COMMAND_4:
            DEBUG_RTOS_PRINTF("IR RX BTN4 Command\n");
            break;
        case IR_RX_BTN_COMMAND_5:
            DEBUG_RTOS_PRINTF("IR RX BTN5 Command\n");
            break;
        case IR_RX_BTN_COMMAND_6:
            DEBUG_RTOS_PRINTF("IR RX BTN6 Command\n");
            break;
        case IR_RX_BTN_COMMAND_7:
            DEBUG_RTOS_PRINTF("IR RX BTN7 Command\n");
            break;
        case IR_RX_BTN_COMMAND_8:
            DEBUG_RTOS_PRINTF("IR RX BTN8 Command\n");
            break;
        case IR_RX_BTN_COMMAND_9:
            DEBUG_RTOS_PRINTF("IR RX BTN9 Command\n");
            break;
        case IR_RX_BTN_COMMAND_kome_:
            DEBUG_RTOS_PRINTF("IR RX BTN * Command\n");
            break;
        case IR_RX_BTN_COMMAND_SHARP:
            DEBUG_RTOS_PRINTF("IR RX BTN # Command\n");
            break;
        case IR_RX_BTN_COMMAND_UP:
            DEBUG_RTOS_PRINTF("IR RX BTN UP Command\n");
            break;
        case IR_RX_BTN_COMMAND_DOWN:
            DEBUG_RTOS_PRINTF("IR RX BTN DOWN Command\n");
            break;
        case IR_RX_BTN_COMMAND_LEFT:
            DEBUG_RTOS_PRINTF("IR RX BTN LEFT Command\n");
            break;
        case IR_RX_BTN_COMMAND_RIGHT:
            DEBUG_RTOS_PRINTF("IR RX BTN RIGHT Command\n");
            break;
        case IR_RX_BTN_COMMAND_OK:
            DEBUG_RTOS_PRINTF("IR RX BTN OK Command\n");
            break;
        default:
            break;
    }
#endif /* __IR_ENABLE__ */
}

void app_ir_init(void)
{
#ifdef __IR_ENABLE__
    // IrReceiver.begin(IR_RX_PIN);
    IrReceiver.begin(IR_RX_PIN, DISABLE_LED_FEEDBACK);
#endif /* __IR_ENABLE__ */
}

void app_ir_main(void)
{
#ifdef __IR_ENABLE__
    if (IrReceiver.decode()) {
        ir_decode(IrReceiver.decodedIRData.command);
    }
#endif /* __IR_ENABLE__ */
}

