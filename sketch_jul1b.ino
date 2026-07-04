#include <M5Unified.h>
#include <Wire.h>
#include <M5_UNIT_8SERVO.h>

// --- サーボON/OFF切り替え用変数 ---
bool running = false;

// --- 制御するサーボのチャンネル ---
static constexpr uint8_t SERVO_CH0 = 0;

// --- Servo Kit 360° のパルス幅 (µs) ---
static constexpr uint16_t PULSE_MIN = 500;      // 時計回り 最大速
static constexpr uint16_t PULSE_STOP = 1500;    // 停止
static constexpr uint16_t PULSE_MAX = 2500;     // 反時計回り 最大速
static constexpr uint16_t PULSE_DEADBAND = 25;  // 停止付近の揺れ防止 (±µs)

M5_UNIT_8SERVO unit_8servo;

void setup() {
  M5.begin();
  M5.Display.setTextSize(2);
  M5.Display.fillScreen(TFT_BLACK);
  M5.Display.println("Init 8Servos...");

  // Port A の I2C を G2(SDA) / G1(SCL) で初期化
  while (!unit_8servo.begin(&Wire, 2, 1, M5_UNIT_8SERVO_DEFAULT_ADDR)) {
    M5.Display.fillScreen(TFT_RED);
    M5.Display.setCursor(10, 10);
    M5.Display.println("8Servos not found");
    Serial.println("8Servos not found");
    delay(500);
  }

  unit_8servo.setAllPinMode(SERVO_CTL_MODE);

  // 起動時は停止
  unit_8servo.setServoPulse(SERVO_CH0, PULSE_STOP);
  M5.Display.fillScreen(TFT_BLACK);
  M5.Display.setCursor(20, 40);
  M5.Display.println("Servo STOP");
}

void loop() {
  M5.update();
  auto t = M5.Touch.getDetail();

  if (t.wasPressed()) {  // M5のタッチパネルにタッチしたら
    running = !running;  // サーボモータのON/OFFを切り替える


    if (running) {                                      // サーボモータがONのとき
      unit_8servo.setServoPulse(SERVO_CH0, PULSE_MIN);  // 正転
      M5.Display.fillScreen(BLACK);
      M5.Display.setCursor(20, 40);
      M5.Display.println("Servo ON");
    } else {                                             // サーボモータがOFFのとき
      unit_8servo.setServoPulse(SERVO_CH0, PULSE_STOP);  // 停止
      M5.Display.fillScreen(BLACK);
      M5.Display.setCursor(20, 40);
      M5.Display.println("Servo STOP");
    }
  }
  delay(20);
}