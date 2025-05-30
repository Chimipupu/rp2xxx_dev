# 📍RP2040 & RP2350 評価F/W

## 📍開発環境

- 📍統合開発環境 (IDE)
  - 📍[Arduino IDE v2.3.6🔗](https://github.com/arduino/arduino-ide/releases/tag/2.3.6)
  - 📚ボード
    - [arduino-pico v4.5.3🔗](https://github.com/earlephilhower/arduino-pico/releases/tag/4.5.3)
  - 📚外部ライブラリ
    - [LovyanGFX v1.2.7🔗](https://github.com/lovyan03/LovyanGFX/releases/tag/1.2.7)
    - [Adafruit_BME280_Library v2.3.0🔗](https://github.com/adafruit/Adafruit_BME280_Library/releases/tag/2.3.0)

- 📍基板

  - 📍RP2040
    - 📍[Raspberry Pi Pico🔗](https://www.raspberrypi.com/products/raspberry-pi-pico/)
    - 📍[Raspberry Pi Pico W🔗](https://www.raspberrypi.com/documentation/microcontrollers/pico-series.html#raspberry-pi-pico-w)
    - 📍[VCC-GND YD-RP2040🔗](https://www.aliexpress.us/item/1005004004120604.html?gatewayAdapt=4itemAdapt)
    - 📍[XIAO RP2040🔗](https://wiki.seeedstudio.com/XIAO-RP2040/)

  - 📍RP2350
    - 📍[Raspberry Pi Pico 2🔗](https://www.raspberrypi.com/products/raspberry-pi-pico-2/)
    - 📍[Pimoroni Pico Plus 2🔗](https://shop.pimoroni.com/products/pimoroni-pico-plus-2?variant=42092668289107/)

- 📍拡張基板
  - 📍[Pimoroni Pico VGA Demo Base🔗](https://shop.pimoroni.com/products/pimoroni-pico-vga-demo-base)
  - 📍[XIAO Expansion Board🔗](https://wiki.seeedstudio.com/Seeeduino-XIAO-Expansion-Board/)

- 📍CPU ... [RP2040🔗](https://www.raspberrypi.com/products/rp2040/)
  - 📍CPU0 ... [ARM Cortex-M0+🔗](https://www.arm.com/ja/products/silicon-ip-cpu/cortex-m/cortex-m0-plus)
  - 📍CPU1 ... [ARM Cortex-M0+🔗](https://www.arm.com/ja/products/silicon-ip-cpu/cortex-m/cortex-m0-plus)
- 📍CPU ... [RP2350🔗](https://www.raspberrypi.com/products/rp2350/)
  - 📍CPU0 ... [ARM Cortex-M33🔗](https://www.arm.com/ja/products/silicon-ip-cpu/cortex-m/cortex-m33)
  - 📍CPU1 ... [ARM Cortex-M33🔗](https://www.arm.com/ja/products/silicon-ip-cpu/cortex-m/cortex-m33)

- 📍OS ... [FreeRTOS🔗](https://www.freertos.org/)
  - 📍CPU0 ... 📚FreeRTOS (搭載済み)
  - 📍CPU1 ... 📚FreeRTOS (搭載済み)

- 📍センサ（I2C接続）
  - 📍[BME280🔗](https://www.bosch-sensortec.com/products/environmental-sensors/humidity-sensors-bme280/) (湿度、温度、気圧センサ)
  - 📍[AT24C32🔗](https://www.microchip.com/en-us/product/AT24C32) (32Kbit EEPROM)
  - 📍[DS3231🔗](https://www.bosch-sensortec.com/products/environmental-sensors/humidity-sensors-bme280/) (TCXO ±2ppm RTC⏰️)

## Ver1.0.4

<div align="center">
  <img width="500" src="/doc/img/chimi_os_opmsg_ver1.0.4.png">
</div>

<table>
  <tr>
    <td><img src="/doc/img/IMG_20241109_031836.jpg"></td>
    <td><img src="/doc/img/IMG_20241109_031118.jpg"></td>
  </tr>
</table>

## 📍実装機能

**凡例(✅実装＆テスト完了、🆗実装済み、🚩TODO、❌TBD)**

### OS(FreeRTOS)

- 📍CPU
  - 📍Core0 ... ドライバCPU
    - 📍OS ... FreeRTOS
      - ✅Core0メインタスク
        - 🚩TODO
      - ✅センサータスク
        - ✅BME280から湿度、温度、気圧を取得
      - ✅Bluetoothタスク📶
        - ✅Bluetoothシリアル
      - ✅ボタンタスク
        - 🚩ボタン処理
          - 🚩ボタン単押し ... TODO
          - 🚩ボタン複数押し判定 ... TODO
          - 🚩ボタン長押し判定 ... TODO
          - 🚩ボタン超長押し判定 ... TODO
  - 📍Core1 ... アプリCPU
    - 📍OS ... FreeRTOS
      - ✅Core1メインタスク
        - 🚩TODO
      - ✅センサータスク
        - ✅BME280 湿度、温度、気圧センサ (@I2C)
      - ✅OLEDタスク
        - 英語、日本語、科学計算の結果をOLEDに表示(@I2C)
      - ✅モニタプログラムタスク(@USBシリアル)
        - ✅RTCのR/W
        - ✅EEPROMのR/W
        - ✅S/Wリセット
        - ✅計算アプリ
          - マンデルブロ集合、円周率π、自然数の底e、黄金比、フィボナッチ数列、高速逆平方根
        - ✅システムレジスタ表示
          - SYSINFO/M0PLUS or M33/SIOのCPUIDレジスタRead
        - ✅SDカードのR/W(@SPI)
        - ✅ベンチマークテスト
          - ✅四則演算（整数、浮動小数 float & double）
          - ✅sin, cos, tan, atan2, sqrt
          - ✅メモリ, GPIOトグル
### ペリフェラル

- 📍I2C
  - ✅(センサー)BME280から湿度、温度、気圧を取得
  - ✅(EEPROM)AT24C32のR/W
  - ✅(RTC)DS3231からRTCの時刻をR/W

- 📍SPI
  - ✅SDカードのR/W、ディレクトリ表示

- 📍GPIO
  - 📍RGB LED (NeoPixel)　
    - ✅赤🔴 : 初期化中、オフライン状態(WiFi,Bluetooth未接続)
    - ✅青🔵 : オンライン状態（WiFi,Bluetooth接続中）
    - ✅緑🟢 : F/W正常（FreeRTOSで処理中）
    - ✅白⚪ : F/W正常（FreeRTOSはアイドル状態）
    - ✅紫🟣 : F/Wエラー

- 📍割込み(IRQ)
  - ✅タイマーIRQ⏰
    - ✅アラーム 0 ⏰(TIMER_IRQ_0) ... 1ms周期
    - ✅アラーム 1 ⏰(TIMER_IRQ_1) ... 8ms周期
      - ✅LEDのPWM（フェード）
    - ✅アラーム 2 ⏰(TIMER_IRQ_2) ... 20ms周期
    - ✅アラーム 3 ⏰(TIMER_IRQ_3) ... 1000ms周期
  - ✅ボタンIRQ (@GPIO24)
    - ✅ `ボタン単押し判定` ... ボタン一回押しを検知
    - ✅ `ボタン複数押し判定` ... 短時間に複数回ボタン押しを検知
    - ✅ `ボタン長押し判定` ... `ボタン長押し`= 1000ms = 1sec
    - ✅ `ボタン超長押し判定` ... `ボタン長押し` = 3000ms = 3sec

<!-- ### PIO

- 📍PIO0
  - ✅SM0
    - GPIOを独立してトグル
  - 🚩SM1
  - 🚩SM2
  - 🚩SM3
- 📍PIO1
  - 🚩SM0
  - 🚩SM1
  - 🚩SM2
  - 🚩SM3
- 📍PIO2(※RP2350)
  - 🚩SM0
  - 🚩SM1
  - 🚩SM2
  - 🚩SM3 -->

<!-- ### Pimoroni Pico VGA Demo Base

- 📍Pimoroni Pico VGA Demo Base
  - 📍Audio📢
    - 📍DAC📢
    - 📍PWM📢
  - 📍VGA📺
  - 📍SD/TF📚 -->