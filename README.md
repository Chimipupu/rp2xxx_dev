# RP2040開発(C++)

RP2040 Firmeware C++ Develop by Chimi\
RP2040のF/WのC++での個人開発リポジトリ🥳

# 実装した機能

- CPU x2コア
  - Core0 ... ドライバコア
    - Neopixcelのアプリ
  - Core1 ... アプリコア
    - OLEDのアプリ
    - モニタプログラム(UART)
    - 数学アプリ
      - 円周率π、自然数の底e、黄金比、フィボナッチ数列、高速逆平方根

# 実装予定
- FreeRTOS ... CPU x2コア分を搭載
- アプリ追加 ... I2C、SPI、PIO、スリープ機能

# RP2040とは？
<div align="center">
<img width="200" src="https://assets.raspberrypi.com/static/chips-a126ba53c50bb160d65210696edf8ad9.png">
</div>

Raspberry Piのデュアルコア（ARM Cortex-M0+ x2コア)のマイコン🥳

[公式URL]
- https://www.raspberrypi.com/products/rp2040/

[データシート]
- https://datasheets.raspberrypi.com/rp2040/rp2040-datasheet.pdf

## スペック
- プロセス ... 40nm
- クロック ... 133MHz
- CPU ... x2コア ARM Cortex-M0+
- SRAM ... 264KB
- FPU ... 単精度
- UART ... x2ch
- SPI ... x2ch
- I2C ... x2ch
- ADC ... 12bit SAR x4ch
- GPIO ... 30本
- PWM ... 16本
- PIO ... x8基