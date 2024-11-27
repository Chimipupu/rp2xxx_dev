/**
 * @file app_filesystem.hpp
 * @author ちみ/Chimi(https://github.com/Chimipupu)
 * @brief File System(SD/SPIFS/FATFS) アプリ 実装
 * @version 0.1
 * @date 2024-11-13
 * 
 * @copyright Copyright (c) 2024 ちみ/Chimi(https://github.com/Chimipupu)
 * 
 */

#include "app_filesystem.hpp"

#ifdef __SD_TF_ENABLE__
#include <SD.h>

const char *p_test_write_txt = "sd write test";
const char *p_test_file_path = "/txt/plain/test.txt";
const char *p_wifi_config_file_path = "/sys/wifi_config.txt";

static void fs_init(void);
static void fs_test(void);
static void fs_dir_print(File dir, uint8_t tabs);
static bool fs_wifi_config_read(char *p_ssid, char *p_password);

static void fs_init(void)
{
    mcu_board_fs_init();
}

static void fs_test(void)
{
    DEBUG_PRINTF("SD card Test\n");

    if (SD.exists(p_test_file_path)) {
        DEBUG_PRINTF("test.txt exists\n");
    } else {
        DEBUG_PRINTF("test.txt doesn't exist\n");
        DEBUG_PRINTF("Creating test.txt\n");
    }

    DEBUG_PRINTF("SD card Write Test\n");
    File myFile = SD.open(p_test_file_path, FILE_WRITE);
    if (myFile) {
        DEBUG_PRINTF("Writing to test.txt...\n");
        myFile.seek(0);
        myFile.println("SD Write Test");
        myFile.close();
    } else {
        DEBUG_PRINTF("error opening test.txt\n");
    }

    DEBUG_PRINTF("SD card Read Test\n");
    myFile = SD.open(p_test_file_path, FILE_READ);
    if (myFile) {
        DEBUG_PRINTF("Read : ");
        while (myFile.available()) {
            DEBUG_PRINTF("%c", myFile.read());
        }
        myFile.close();
    } else {
        DEBUG_PRINTF("error opening /test.txt\n");
    }
}

static bool fs_wifi_config_read(char *p_ssid, char *p_password)
{
    bool result = false;

    DEBUG_PRINTF("WiFi Config File Read(@SD)\n");

    if (SD.exists(p_wifi_config_file_path)) {
        DEBUG_PRINTF("wifi_config.txt exists\n");
    } else {
        DEBUG_PRINTF("wifi_config.txt doesn't exist\n");
        return result;
    }

    File myFile = SD.open(p_wifi_config_file_path, FILE_READ);
    if (myFile) {
        String ssid = myFile.readStringUntil('\n');
        ssid.trim();
        ssid.toCharArray(p_ssid, ssid.length() + 1);

        String password = myFile.readStringUntil('\n');
        ssid.trim();
        password.toCharArray(p_password, password.length() + 1);

        result = true;
    } else {
        result = false;
    }

    myFile.close();
    return result;
}

static void fs_dir_print(File dir, uint8_t tabs)
{
    if (SD.exists(p_test_file_path)) {
        File entry = SD.open("/", FILE_READ);
        while (true)
        {
            File entry = dir.openNextFile();
            if (!entry) {
                // no file
                break;
            }

            DEBUG_PRINTF("%s", entry.name());
            if (entry.isDirectory()) {
                DEBUG_PRINTF("/");
                fs_dir_print(entry, tabs + 1);
            } else {
                DEBUG_PRINTF("\n");
            }
            entry.close();
        }

        entry.close();
    } else {
        DEBUG_PRINTF("No File Dir\n");
    }
}

void app_fs_test(void)
{
    fs_test();
}
#endif /* __SD_TF_ENABLE__ */

void app_fs_init(void)
{
#ifdef __SD_TF_ENABLE__
    fs_init();
#endif /* __SD_TF_ENABLE__ */
}

void app_fs_wifi_config_read(char *p_ssid, char *p_password)
{
#ifdef __SD_TF_ENABLE__
    bool result = false;
    result = fs_wifi_config_read(p_ssid, p_password);

    if (result != false) {
        DEBUG_PRINTF("SSID:");
        DEBUG_PRINTF("%s\n", p_ssid);
        DEBUG_PRINTF("Password:");
        DEBUG_PRINTF("%s\n", p_password);
    } else {
        DEBUG_PRINTF("No data(SSID & Password)\n");
    }
#endif /* __SD_TF_ENABLE__ */
}

void app_fs_dir_print(void)
{
#ifdef __SD_TF_ENABLE__
    File root = SD.open("/");
    fs_dir_print(root, 0);
#endif /* __SD_TF_ENABLE__ */
}