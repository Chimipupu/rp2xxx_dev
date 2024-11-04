# RP2040評価プログラム by ちみ

RP2040 Firmeware C++ Develop by Chimi\
C++でのRP2040 F/W 個人開発リポジトリ🥳

## 開発環境構築
- [RP2040 開発環境構築(Windows)](doc\rp2040_dev_env.md)

## ✅実装機能
- CPU (ARM Cortex-M0+)
  - ✅Core0 ... ドライバCPU
    - ✅FreeRTOS
      - ✅LEDタスク
      - ✅Neopixcelのアプリ
  - ✅Core1 ... アプリCPU
    - ✅FreeRTOS
      - ✅モニタプログラムタスク
        - ✅レジスタ操作アプリ
          - M0PLUS CPUIDレジスタ、SIOレジスタの読み出し
        - ✅計算アプリ
          - マンデルブロ集合、円周率π、自然数の底e、黄金比、フィボナッチ数列、高速逆平方根

- 割込み(IRQ)
  - ✅タイマー(64bit)⏰
    - ✅アラーム 0 ⏰(TIMER_IRQ_0) ... TODO
    - ✅アラーム 1 ⏰(TIMER_IRQ_1) ... TODO
    - ✅アラーム 2 ⏰(TIMER_IRQ_2) ... TODO
    - ✅アラーム 3 ⏰(TIMER_IRQ_3) ... TODO

## TBD
- ARM Cortex-M0+
  - 割込み（IRQ） ... ボタン、タイマー、PIOからIRQがほしい
  - タイマー ... インターバルとワンショットタイマとIRQの生成
  - ADC & DMA ... ADCをDMAでとりたい
  - アプリ追加 ... I2C、SPI、PIO、スリープ機能

- PIO
  - GPIO ... PIOにGPIO任せる
  - VGA ... モニターに描画したい
  - SDIO ... SDカード

## 🔰RP2040とは？🔰
<div align="center">
<img width="200" src="https://assets.raspberrypi.com/static/chips-a126ba53c50bb160d65210696edf8ad9.png">
</div>

Raspberry Piの **ARM Cortex-M0+ x2コア** CPU搭載のマイコン🥳

[公式URL]
- https://www.raspberrypi.com/products/rp2040/

[データシート]
- https://datasheets.raspberrypi.com/rp2040/rp2040-datasheet.pdf

### スペック
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