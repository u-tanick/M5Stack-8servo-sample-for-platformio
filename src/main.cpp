#include <M5Unified.h>
// #include <M5Stack.h>
//#include <M5GFX.h>
#include "M5_UNIT_8SERVO/M5_UNIT_8SERVO.h"

M5GFX display;
M5Canvas canvas(&display);
M5_UNIT_8SERVO unit_8servo;

uint8_t sda = 32;
uint8_t scl = 33;

/**
 * [POAT A]
 * M5Stack_Core_ESP32 (M5STACK_BASIC)
 * M5STACK_FIRE
 *   sda 21
 *   scl 22
 * M5STACK_Core2 v1.0, v1.1
 *   sda 32
 *   scl 33
 * 
 * [POAT C]
 * M5STACK_CoreS3
 *   sda 17
 *   scl 18
*/
void setup() {

    auto cfg = M5.config(); // 設定用の構造体を代入。
    // 設定したい項目を設定する。下記の2行はデフォルト設定を使う場合は省略してください。
    cfg.serial_baudrate = 115200;
    cfg.output_power = true;
    M5.begin(cfg); // 設定した値でデバイスを開始する。
//    M5.begin(); // 設定した値でデバイスを開始する。
    display.begin();
    canvas.setColorDepth(1);  // mono color
    canvas.setFont(&fonts::efontCN_14);
    canvas.createSprite(display.width(), display.height());
    canvas.setPaletteColor(1, GREEN);

//    while (!unit_8servo.begin(&Wire, 21, 22, M5_UNIT_8SERVO_DEFAULT_ADDR)) {
    while (!unit_8servo.begin(&Wire, sda, scl, M5_UNIT_8SERVO_DEFAULT_ADDR)) {
        Serial.println("extio Connect Error");
        M5.Lcd.print("extio Connect Error");
        delay(1000);
    }
/*
    Serial.println("UNIT_8SERVO Connected");
    M5.Lcd.print("UNIT_8SERVO Connected");
*/

    unit_8servo.setAllPinMode(SERVO_CTL_MODE);
    // unit_8servo.setAllPinMode(DIGITAL_INPUT_MODE);
    // unit_8servo.setAllPinMode(DIGITAL_OUTPUT_MODE);
    // unit_8servo.setAllPinMode(ADC_INPUT_MODE);
    // unit_8servo.setAllPinMode(RGB_LED_MODE);
}

char info[50];

void loop() {
    canvas.fillSprite(0);

    canvas.setTextSize(2);
    canvas.drawString("SERVO CTL MODE", 10, 10);
    canvas.drawString("FW VERSION: " + String(unit_8servo.getVersion()), 10, 40);
    for (uint8_t deg = 0; deg <= 180; deg += 45) {
        for (uint8_t i = 0; i < 8; i++) {
            unit_8servo.setServoAngle(i, deg);
            Serial.printf("CH:%d DEG: %d", i, deg);
            canvas.drawRect(0, i * 20 + 75, 200, 15, 1);
            canvas.fillRect(0, i * 20 + 75, map(deg, 0, 180, 0, 200), 15, 1);
            canvas.setCursor(220, i * 28 + 10);
            canvas.setTextSize(1);
            canvas.printf("CH:%d DEG: %d", i, deg);
        }
        canvas.pushSprite(0, 0);
        vTaskDelay(500);
    }

    canvas.setTextSize(2);
    canvas.drawString("SERVO CTL MODE", 10, 10);
    canvas.drawString("FW VERSION: " + String(unit_8servo.getVersion()), 10, 40);
    for (int pulse = 500; pulse <= 2500; pulse += 100) {
        for (uint8_t i = 0; i < 8; i++) {
            unit_8servo.setServoPulse(i, pulse);
            Serial.printf("CH:%d P: %d", i, pulse);
            canvas.drawRect(0, i * 20 + 75, 200, 15, 1);
            canvas.fillRect(0, i * 20 + 75, map(pulse, 500, 2500, 0, 200), 15, 1);
            canvas.setCursor(220, i * 28 + 10);
            canvas.setTextSize(1);
            canvas.printf("CH:%d P: %d", i, pulse);
        }
        canvas.pushSprite(0, 0);
    }

    delay(100);
    canvas.pushSprite(0, 0);
}
