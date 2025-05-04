# RP2040/2350 開発環境

- 📍統合開発環境 (IDE)
  - 📍[Arduino IDE v2.3.6🔗](https://github.com/arduino/arduino-ide/releases/tag/2.3.6)
  - 📚ボード
    - [arduino-pico v4.5.3🔗](https://github.com/earlephilhower/arduino-pico/releases/tag/4.5.3)
  - 📚外部ライブラリ
    - [LovyanGFX v1.2.7🔗](https://github.com/lovyan03/LovyanGFX/releases/tag/1.2.7)
    - [Adafruit_BME280_Library v2.3.0🔗](https://github.com/adafruit/Adafruit_BME280_Library/releases/tag/2.3.0)

- 📍基板

  - RP2040
    - 📍[Raspberry Pi Pico🔗](https://www.raspberrypi.com/products/raspberry-pi-pico/)
    - 📍[Raspberry Pi Pico W🔗](https://www.raspberrypi.com/documentation/microcontrollers/pico-series.html#raspberry-pi-pico-w)
    - 📍[VCC-GND YD-RP2040🔗](https://www.aliexpress.us/item/1005004004120604.html?gatewayAdapt=4itemAdapt)
    - 📍[XIAO RP2040🔗](https://wiki.seeedstudio.com/XIAO-RP2040/)

  - RP2350
    - 📍[Raspberry Pi Pico 2🔗](https://www.raspberrypi.com/products/raspberry-pi-pico-2/)
    - 📍[Pimoroni Pico Plus 2🔗](https://shop.pimoroni.com/products/pimoroni-pico-plus-2?variant=42092668289107/)

## 基板

### RP2040基板

![pico_pin_out](/doc/RP2040/基板/Pico/pico_pinout.png)

![pico_pin_out](/doc/RP2040/基板/YD-RP2040/YD-2040-PIN.png)

- 📍NeoPixel
  - Raspberry Pi Pico ... N/A
  - YD-RP2040... GPIO23
- 📍ボタン
  - Raspberry Pi Pico ... N/A
  - YD-RP2040... GPIO24
- 📍LED ... GPIO25
- 📍MCU(マイコン) ... RP2040
  - 📍CPU ... ARM Cortex-M0+ x2コア
  - 📍プロセス ... 40nm
  - 📍クロック ... 133MHz
  - 📍ROM ... 2MB、4MB、8MB、16MB
  - 📍SRAM ... 264KB
  - 📍FPU ... 単精度
  - 📍UART ... x2ch
  - 📍SPI ... x2ch
  - 📍I2C ... x2ch
  - 📍ADC ... 12bit SAR x4ch
  - 📍GPIO ... 30本
  - 📍PWM ... 16本
  - 📍タイマー(64bit) ... アラーム x4 (IRQ生成)
  - 📍RTC
  - 📍WDT
  - 📍PIO ... x8基

### RP2350基板

![pico2_pin_out](/doc/RP2350/基板/Pico2/pico_2_pinout.png)

![pimoroni_pico_plus_2_pin_out](/doc/RP2350/基板/Pimoroni_Pico_Plus_2/Pimoroni_Pico_Plus_2_Pinout.png)

- 📍LED ... GPIO25
- 📍ROM
  - Raspberry Pi Pico 2 ... 4MB
  - Pimoroni Pico Plus 2 ... 16MB
- 📍PSRAM
  - Raspberry Pi Pico 2 ... N/A
  - Pimoroni Pico Plus 2 ... 8MB
- 📍MCU(マイコン) ... RP2350
  - 📍CPU
    - `ARM Cortex-M33` x2コア
    - `RISC-V Hazard3(RV32I)` x2コア
  - 📍クロック ... 150MHz
  - 📍SRAM ... 520KB
  - 📍FPU ... 倍精度
  - 📍UART ... x2ch
  - 📍SPI ... x2ch
  - 📍I2C ... x2ch
  - 📍ADC ... 12bit SAR x4ch
  - 📍GPIO ... 48本
  - 📍PWM ... 24本
  - 📍タイマー(64bit) ... x2ch
  - 📍RTC
  - 📍WDT
  - 📍HSTX
  - 📍TRGN (真性乱数生成器)
  - 📍PIO ... x3基(SM x12)
  - 📍USB 1.1 controller and PHY

## Arduino IED
- `基本設定`から👇下記URLを追加
- `ボードマネージャ`から`Raspberry Pi Pico/RP2040/2350 by Earle F Philhower, III`をダウンロード or 更新

```shell
https://github.com/earlephilhower/arduino-pico/releases/download/global/package_rp2040_index.json
```

### ビルド構成

#### RP2040のビルド構成

![rp2040_build_info](/doc/rp2040_arduino_ide_build_info.png)

#### RP2350のビルド構成

![rp2350_build_info](/doc/rp2350_arduino_ide_build_info.png)

## VSCode
### `Raspberry Pi Pico`をインストール
- VSCodeの拡張機能で`Raspberry Pi Pico`をインストール

<div align="center">
<img width="600" src="https://storage.googleapis.com/zenn-user-upload/3fb53d261f08-20241015.png">
</div>

### プロジェクトを作成
- `Name` ... プロジェクト名を入力する
- `Board type` ... `pico`または`pico2`を選択する
- `location` ... プロジェクトの保存先を選択する
- `Select Pico SDK version` ... `Pico SDKの最新バージョン`を選択する
- `Features` ... 使用する機能を選択する
- `Stdio support` ... C/C++の`printf()`の出力先を`USB`か`UART`から決める
- `Code generation options` ... `Generate C++ code`でPico SDKのコードを生成する
- `Debbugger` ... `DebugProbe(CMSIS-DAP)[Default]`を選択する

<div align="center">
<img width="600" src="https://storage.googleapis.com/zenn-user-upload/93e5a68afb64-20241015.png">
</div>

### ビルド＆デバッグ

- `ビルド` ... `Compile Project`でコンパイルを実行
- F/Wを書き込む ... `Run Project`でPicoにF/Wを書き込む
- `デバッグ` ... `Debug Project`でデバッグ開始（※）

※Picoでデバッグをするには`デバッガ`が必要🥲
- 下記の`デバッガの準備`を参考にご準備ください

<div align="center">
<img width="600" src="https://storage.googleapis.com/zenn-user-upload/7b86d616bf51-20241015.png">
</div>


### デバッガの準備

Picoでデバッグするためには`デバッガ`がつくる💁‍♀️
- Picoをもう一つ用意 ... `debugprobe`のF/Wを書き込む

まず、デバッガ`debugprobe`の最新F/W(`debugprobe_on_pico.uf2`)をダウンロード
- https://github.com/raspberrypi/debugprobe/releases/latest

[F/Wの書き込む]
- Picoの **`BOOTSEL`ボタンを押しながら** USBをPCに接続する
- `debugprobe_on_pico.uf2`をPicoにドロップ＆ドラック

[他のPicoとの接続]
```
Pico(A) GND -> Pico(B) GND
Pico(A) GP2 -> Pico(B) SWCLK
Pico(A) GP3 -> Pico(B) SWDIO
Pico(A) GP4/UART1 TX -> Pico(B) GP1/UART0 RX
Pico(A) GP5/UART1 RX -> Pico(B) GP0/UART0 TX
```

<div align="center">
<img width="600" src="https://storage.googleapis.com/zenn-user-upload/4e1aedab768d-20241015.png">
</div>

## 開発環境構築(Linux)
PICO SDKはLinux環境が必須
- UbuntuやWindowsのWSL2で構築する方法を記載する

### pico_setup.sh
`pico_setup.sh`でPICO SDKの構築を自動化

[Github]
https://github.com/raspberrypi/pico-setup/tree/master

```shell
wget https://raw.githubusercontent.com/raspberrypi/pico-setup/master/pico_setup.sh
chmod +x ./pico_setup.sh
./pico_setup.sh
```

## 参考文献
### RP2040
- [RP2040のメーカーHP](https://www.raspberrypi.com/products/rp2040/)

- [RP2040のメーカー公式ドキュメントHP](https://www.raspberrypi.com/documentation/microcontrollers/silicon.html)

- [データシート(RP2040)](https://datasheets.raspberrypi.com/rp2040/rp2040-datasheet.pdf)

### RP2350
- [RP2350 メーカーHP](https://www.raspberrypi.com/products/rp2350/)

- [RP2350のメーカー公式ドキュメントHP](https://www.raspberrypi.com/documentation/microcontrollers/silicon.html)

- [データシート(RP2350)](https://datasheets.raspberrypi.com/rp2350/rp2350-datasheet.pdf)

### Pico SDK
- [Pico SDK 公式URL](https://www.raspberrypi.com/documentation/microcontrollers/c_sdk.html)

- [公式マニュアル（英語）※最新](https://datasheets.raspberrypi.com/pico/getting-started-with-pico.pdf?_gl=1*anhnfe*_ga*MTE3MTIyMDMzMS4xNzI4OTQ5MzU2*_ga_22FD70LWDS*MTcyODk2NTE2OC42LjAuMTcyODk2NTE3MS4wLjAuMA..)

- [公式マニュアル（日本語）※更新が2021年で止まっている](https://datasheets.raspberrypi.com/pico/getting-started-with-pico-JP.pdf)

- Zenn『Pico SDKの開発環境構築の最適解 📝』 by ちみ
  - https://zenn.dev/chimipupu/articles/039597a904849f