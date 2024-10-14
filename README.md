# RP2040開発(C++)
RP2040 Firmeware C++ Develop by Chimi
RP2040のF/WのC++での個人開発リポジトリ🥳

# 実装済み

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