/**
 * @file app_filesystem.hpp
 * @author ちみ/Chimi(https://github.com/Chimipupu)
 * @brief File System(SD/SPIFS/FATFS)ヘッダ
 * @version 0.1
 * @date 2024-11-13
 * 
 * @copyright Copyright (c) 2024 ちみ/Chimi(https://github.com/Chimipupu)
 * 
 */

#ifndef APP_FILESYSTEM_HPP
#define APP_FILESYSTEM_HPP
#include "common.hpp"

void app_fs_init(void);
void app_fs_test(void);
void app_fs_dir_print(void);

#ifdef __WIFI_ENABLE__
void app_fs_wifi_config_read(char *p_ssid, char *p_password);
#endif /* __WIFI_ENABLE__ */

#ifdef __EEPROM_ENABLE__
void app_fs_eeprom_print(uint16_t size);
#endif /* __EEPROM_ENABLE__ */

#endif /* APP_FILESYSTEM_HPP */