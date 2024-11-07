# RP2040評価F/W by ちみ
RP2040評価F/W 個人開発リポジトリ🥳

- 📍CPU ... [RP2040🔗](https://www.raspberrypi.com/products/rp2040/)
  - 📍CPU0 ... [ARM Cortex-M0+🔗](https://www.arm.com/ja/products/silicon-ip-cpu/cortex-m/cortex-m0-plus)
  - 📍CPU1 ... [ARM Cortex-M0+🔗](https://www.arm.com/ja/products/silicon-ip-cpu/cortex-m/cortex-m0-plus)

- 📍OS ... [FreeRTOS🔗](https://www.freertos.org/)
  - 📍CPU0 ... ✅FreeRTOS (搭載済み)
  - 📍CPU1 ... ✅FreeRTOS (搭載済み)

## 開発環境
- [開発環境の詳細🔗](/doc/rp2040_dev_env.md)

- 📍IDE
  - 📍[Arduino IDE v2.33🔗](https://github.com/arduino/arduino-ide/releases/tag/2.3.3)
    - [Raspberry Pi Pico/RP2040 by Earle F. Philhower, III🔗](https://github.com/earlephilhower/arduino-pico)

- 📍基板
  - RP2040
    - [VCC-GND YD-RP2040🔗](https://www.aliexpress.us/item/1005004004120604.html?gatewayAdapt=4itemAdapt)

## ✅実装機能
- 📍CPU (ARM Cortex-M0+)(clk_sys = 133MHz)
  - 📍Core0 ... ドライバCPU
    - 📍OS ... FreeRTOS
      - ✅ボタンタスク
        - ボタン処理
          - ボタン単押し ... TODO
          - ボタン複数押し判定 ... TODO
          - ボタン長押し判定 ... TODO
          - ボタン超長押し判定 ... TODO
      - ✅LEDタスク
        - LEDのアプリ処理
      - ✅Neopixcelタスク
        - Neopixcelのアプリ処理
  - 📍Core1 ... アプリCPU
    - 📍OS ... FreeRTOS
      - ✅モニタプログラムタスク
        - ✅レジスタ
          - M0PLUS CPUIDレジスタ、SIOレジスタのRead
        - ✅計算
          - マンデルブロ集合、円周率π、自然数の底e、黄金比、フィボナッチ数列、高速逆平方根

- 📍割込み(IRQ)
    - ✅ボタンIRQ (@GPIO24)
      - ✅`ボタン単押し判定` ... ボタン一回押しを検知
      - ✅`ボタン複数押し判定` ... 短時間に複数回ボタン押しを検知
      - ✅`ボタン長押し判定` ... ボタン長押しを検知（1000ms = 1s）
      - ✅`ボタン超長押し判定` ... ボタン長押しを検知（3000ms = 2s）
  - ✅タイマーIRQ⏰(clk_ref = 12MHz)
    - ✅アラーム 0 ⏰(TIMER_IRQ_0) ... TODO
    - ✅アラーム 1 ⏰(TIMER_IRQ_1) ... TODO
    - ✅アラーム 2 ⏰(TIMER_IRQ_2) ... TODO
    - ✅アラーム 3 ⏰(TIMER_IRQ_3) ... TODO

### TBD
- ARM Cortex-M0+
  - ADC & DMA ... ADCをDMAでとりたい
  - アプリ追加 ... I2C、SPI、PIO、スリープ機能

- PIO
  - GPIO ... PIOにGPIO任せる
  - VGA ... モニターに描画したい
  - SDIO ... SDカード