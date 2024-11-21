/**
 * @file app_bluetooth.cpp
 * @author ちみ/Chimi(https://github.com/Chimipupu)
 * @brief Bluetooth アプリ 実装
 * @version 0.1
 * @date 2024-11-21
 * 
 * @copyright Copyright (c) 2024 ちみ/Chimi(https://github.com/Chimipupu)
 * 
 */

#include "app_bluetooth.hpp"
#include "SerialBT.h"

/**
 * @brief Bluetoothアプリ初期化関数
 * 
 */
void app_bluetooth_init(void)
{
    SerialBT.begin();
    DEBUG_PRINT_INIT(DEBUG_UART_BAUDRATE);
    GPIO_OUTPUT(OB_LED_PIN, LOW);
}

/**
 * @brief Bluetoothアプリ メイン関数
 * 
 */
void app_bluetooth_main(void)
{
    if (SerialBT.available()) {
        byte val;
        SerialBT.readBytes(&val, 1);

        if (val == 'a') {
            SerialBT.println("BT A");
        } if (val == 'b') {
            SerialBT.println("BT B");
        }
    }
}
