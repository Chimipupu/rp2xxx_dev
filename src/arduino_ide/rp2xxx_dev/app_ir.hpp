/**
 * @file app_ir.hpp
 * @author ちみ/Chimi(https://github.com/Chimipupu)
 * @brief 赤外線リモコン アプリ ヘッダー
 * @version 0.1
 * @date 2024-11-22
 * 
 * @copyright Copyright (c) 2024 ちみ/Chimi(https://github.com/Chimipupu)
 * 
 */

#ifndef APP_IR_HPP
#define APP_IR_HPP

#include "common.hpp"

#define IR_RX_BTN_COMMAND_0        0x19 // リモコンボタン「0」(NEC/0xE619FF00/32bit LSB first)
#define IR_RX_BTN_COMMAND_1        0x45 // リモコンボタン「1」(NEC/0xBA45FF00/32bit LSB first)
#define IR_RX_BTN_COMMAND_2        0x46 // リモコンボタン「2」(NEC/0xB946FF00/32bit LSB first)
#define IR_RX_BTN_COMMAND_3        0x47 // リモコンボタン「3」(NEC/0xB847FF00/32bit LSB first)
#define IR_RX_BTN_COMMAND_4        0x44 // リモコンボタン「4」(NEC/0xBB44FF00/32bit LSB first)
#define IR_RX_BTN_COMMAND_5        0x40 // リモコンボタン「5」(NEC/0xBF40FF00/32bit LSB first)
#define IR_RX_BTN_COMMAND_6        0x43 // リモコンボタン「6」(NEC/0xBC43FF00/32bit LSB first)
#define IR_RX_BTN_COMMAND_7        0x07 // リモコンボタン「7」(NEC/0xF807FF00/32bit LSB first)
#define IR_RX_BTN_COMMAND_8        0x15 // リモコンボタン「8」(NEC/0xEA15FF00/32bit LSB first)
#define IR_RX_BTN_COMMAND_9        0x09 // リモコンボタン「9」(NEC/0xF609FF00/32bit LSB first)
#define IR_RX_BTN_COMMAND_kome_    0x16 // リモコンボタン「*」(NEC/0xE916FF00/32bit LSB first)
#define IR_RX_BTN_COMMAND_SHARP    0xD0 // リモコンボタン「#」(NEC/0xF20DFF00/32bit LSB first)
#define IR_RX_BTN_COMMAND_UP       0x18 // リモコンボタン「上」(NEC/0xE718FF00/32bit LSB first)
#define IR_RX_BTN_COMMAND_DOWN     0x52 // リモコンボタン「下」(NEC/0xAD52FF00/32bit LSB first)
#define IR_RX_BTN_COMMAND_LEFT     0x08 // リモコンボタン「左」(NEC/0xF708FF00/32bit LSB first)
#define IR_RX_BTN_COMMAND_RIGHT    0x5A // リモコンボタン「右」(NEC/0xA55AFF00/32bit LSB first)
#define IR_RX_BTN_COMMAND_OK       0x1C // リモコンボタン「OK」(NEC/0xE31CFF00/32bit LSB first)

void app_ir_init(void);
void app_ir_main(void);

#endif /* APP_IR_HPP */