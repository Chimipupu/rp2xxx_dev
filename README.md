# RP2040評価プログラム by ちみ
C++でのRP2040 F/W 個人開発リポジトリ🥳

- CPU ... RP2040
- OS ... FreeRTOS

## 開発環境構築
- [RP2040 開発環境構築(Windows)](doc/rp2040_dev_env.md)

## ✅実装機能
- CPU (ARM Cortex-M0+)(clk_sys = 133MHz)
  - ✅Core0 ... ドライバCPU
    - ✅FreeRTOS
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
  - ✅Core1 ... アプリCPU
    - ✅FreeRTOS
      - ✅モニタプログラムタスク
        - ✅レジスタ
          - M0PLUS CPUIDレジスタ、SIOレジスタのRead
        - ✅計算
          - マンデルブロ集合、円周率π、自然数の底e、黄金比、フィボナッチ数列、高速逆平方根

- 割込み(IRQ)
    - ✅ボタンIRQ
      - ✅`ボタン単押し判定` ... ボタン一回押しを検知
      - ✅`ボタン複数押し判定` ... 短時間に複数回ボタン押しを検知
      - ✅`ボタン長押し判定` ... ボタン長押しを検知（1000ms = 1s）
      - ✅`ボタン超長押し判定` ... ボタン長押しを検知（3000ms = 2s）
  - ✅タイマーIRQ⏰(clk_ref = 12MHz)
    - ✅アラーム 0 ⏰(TIMER_IRQ_0) ... TODO
    - ✅アラーム 1 ⏰(TIMER_IRQ_1) ... TODO
    - ✅アラーム 2 ⏰(TIMER_IRQ_2) ... TODO
    - ✅アラーム 3 ⏰(TIMER_IRQ_3) ... TODO

## TBD
- ARM Cortex-M0+
  - ADC & DMA ... ADCをDMAでとりたい
  - アプリ追加 ... I2C、SPI、PIO、スリープ機能

- PIO
  - GPIO ... PIOにGPIO任せる
  - VGA ... モニターに描画したい
  - SDIO ... SDカード

## 開発基板
## VCC GND YD-RP2040
CPUに ARM Cortex-M0+を2つ搭載のRP2040の開発基板🥳


![yd_rp2040_pin_out](doc/YD-RP2040\YD-2040-PIN.png)

### スペック (CPU)
[RP2040のメーカーHP](https://www.raspberrypi.com/products/rp2040/)
[RP2040のメーカー公式ドキュメントHP](https://www.raspberrypi.com/documentation/microcontrollers/silicon.html)
[データシート(RP2040)](https://datasheets.raspberrypi.com/rp2040/rp2040-datasheet.pdf)

- プロセス ... 40nm
- クロック ... 133MHz
- CPU ... ARM Cortex-M0+ x2コア
- ROM ... 2MB、4MB、8MB、16MB
- SRAM ... 264KB
- FPU ... 単精度
- UART ... x2ch
- SPI ... x2ch
- I2C ... x2ch
- ADC ... 12bit SAR x4ch
- GPIO ... 30本
- PWM ... 16本
- タイマー(64bit)
  - アラーム ... x4 (IRQ生成)
- RTC
- WDT
- PIO ... x8基