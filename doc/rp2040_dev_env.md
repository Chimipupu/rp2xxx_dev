# 開発環境構築 by ちみ
[Pico SDK 公式URL](https://www.raspberrypi.com/documentation/microcontrollers/c_sdk.html)
[公式マニュアル（英語）※最新](https://datasheets.raspberrypi.com/pico/getting-started-with-pico.pdf?_gl=1*anhnfe*_ga*MTE3MTIyMDMzMS4xNzI4OTQ5MzU2*_ga_22FD70LWDS*MTcyODk2NTE2OC42LjAuMTcyODk2NTE3MS4wLjAuMA..)
[公式マニュアル（日本語）※更新が2021年で止まっている](https://datasheets.raspberrypi.com/pico/getting-started-with-pico-JP.pdf)

## 開発環境構築(Windows)

## VSCode
### `Raspberry Pi Pico`をインストール
- VSCodeの拡張機能で`Raspberry Pi Pico`をインストール

<div align="center">
<img width="600" src="https://cdn.discordapp.com/attachments/1295531991789211719/1295543688759480441/image.png?ex=670f0895&is=670db715&hm=b2931d0cb730ffca71a144f64aac359a66d15b1d57f66cdbea507bc5407658fa&">
</div>

### プロジェクトを作成
- `Name` ... プロジェクト名を入力する
- `Board type` ... `pico`を選択する
- `location` ... プロジェクトの保存先を選択する
- `Select Pico SDK version` ... `Pico SDKの最新バージョン`を選択する
- `Features` ... 使用する機能を選択する
- `Stdio support` ... C/C++の`printf()`の出力先を`USB`か`UART`から決める
- `Code generation options` ... `Generate C++ code`でPico SDKのコードを生成する
- `Debbugger` ... `DebugProbe(CMSIS-DAP)[Default]`を選択する

<div align="center">
<img width="600" src="https://cdn.discordapp.com/attachments/1295531991789211719/1295554669493485649/image.png?ex=670f12cf&is=670dc14f&hm=97681773e397ca89060a20c9f48b7ff44e4b85c86826f5b15000f124ca8c5ef9&">
</div>

### ビルド＆デバッグ

- `ビルド` ... `Compile Project`でコンパイルを実行
- F/Wを書き込む ... `Run Project`でPicoにF/Wを書き込む
- `デバッグ` ... `Debug Project`でデバッグ開始（※）

※Picoでデバッグをするには`デバッガ`が必要です🥲
➡ 下記の`デバッガの準備`を参考にご準備ください

<div align="center">
<img width="600" src="https://cdn.discordapp.com/attachments/1295531991789211719/1295652162327810049/image.png?ex=670f6d9b&is=670e1c1b&hm=aa73cb36f5d61442a230e1c1e06c6b9065b390af2b25f9aba9c8a49904e85e50&">
</div>


### デバッガの準備

Picoでデバッグするためには`デバッガ`がつくります💁‍♀️
➡ Picoをもう一つ用意 ... `debugprobe`のF/Wを書き込む

まず、デバッガ`debugprobe`の最新F/W(`debugprobe_on_pico.uf2`)をダウンロード
➡ https://github.com/raspberrypi/debugprobe/releases/latest

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
<img width="600" src="https://cdn.discordapp.com/attachments/1295531991789211719/1295650923040739338/image.png?ex=670f6c74&is=670e1af4&hm=698b2f28c9b70c741e4017532d650bd640c36a54b7dae886a9e64074adced50f&">
</div>

## 開発環境構築(Linux)
PICO SDKはLinux環境が必須
➡ UbuntuやWindowsのWSL2で構築する方法を記載します

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
[ラズベリー・パイPico/Pico W攻略本](https://interface.cqpub.co.jp/magazine/2023pico/)