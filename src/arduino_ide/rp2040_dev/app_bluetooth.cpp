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
#ifdef __MCU_BOARD_PICO_W__
#include "SerialBT.h"
#endif /* __MCU_BOARD_PICO_W__ */

/**
 * @brief Bluetoothアプリ初期化関数
 * 
 */
void app_bluetooth_init(void)
{
#ifdef __MCU_BOARD_PICO_W__
    SerialBT.begin();
    GPIO_OUTPUT(OB_LED_PIN, LOW);
#endif /* __MCU_BOARD_PICO_W__ */
}

/**
 * @brief Bluetoothアプリ メイン関数
 * 
 */
void app_bluetooth_main(void)
{
#ifdef __MCU_BOARD_PICO_W__
    if (SerialBT.available()) {
        byte val;
        SerialBT.readBytes(&val, 1);

        if (val == 'a') {
            SerialBT.println("BT A");
        } if (val == 'b') {
            SerialBT.println("BT B");
        }
    }
#endif /* __MCU_BOARD_PICO_W__ */
}
