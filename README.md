# M5Stack用8chサーボドライバユニット動作確認用サンプル

[M5Stack用8chサーボドライバユニット](https://www.switch-science.com/collections/m5stack/products/9199)

最大8つのサーボモーターを接続することができるM5Stack用の拡張ユニットです。

本サンプルは、このユニットをplatformio経由でデプロイして動作確認するために作成したモノです。

本サンプルは、M5Stackの公式から公開されている
[M5Stack platformio project template](https://github.com/m5stack/M5Stack-platformio) をベースに、
[M5Unit-8Servo](https://github.com/m5stack/M5Unit-8Servo) のコード(src/M5_UNIT_8SERVO/以下のファイル)を取り込んで作成しています。

また、コアライブラリをM5Stack.hからM5Unified.hに修正しています。

## 動作確認済み

M5STACK_FIREのポートA および M5STACK_Core2 v1.1のポートA での動作確認済みです。

* [POAT A]
  * M5STACK_FIRE
    * sda 21
    * scl 22
  * M5STACK_Core2 v1.0, v1.1
    * sda 32
    * scl 33

## 注意事項

手ごろな電源が無いので未検証ですが、3つ以上のサーボモーターを動作させる場合、8chサーボドライバユニットに別途電源供給する必要があるようです。

Fireでは3つは何とか動いてましたが、Core2 v1.1だとコードは動いてもサーボが動かない、Core2が再起動を繰り返すなど、不安定な挙動になりました。
