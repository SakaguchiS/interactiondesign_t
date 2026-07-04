#include <M5Unified.h>
#include <Wire.h>
#include <VL53L0X.h>

VL53L0X tof;

void setup() {
  auto cfg = M5.config();
  M5.begin(cfg);
  Wire.begin();
  Serial.begin(115200); // シリアル通信を115200のボーレートで開始

  M5.Display.setRotation(1);
  M5.Display.fillScreen(BLACK);
  M5.Display.setTextSize(3);
  M5.Display.setTextColor(WHITE);

  tof.setTimeout(500);

  if (!tof.init()) {
    M5.Display.fillScreen(RED);
    M5.Display.setCursor(20, 20);
    M5.Display.println("ToF Error");
    while (1);
  }

  tof.startContinuous();
}

void loop() {
  // --- 距離を取得 ---
  uint16_t distance = tof.readRangeContinuousMillimeters();

  M5.Display.fillScreen(BLACK);
  M5.Display.setCursor(20, 100);
  M5.Display.println(distance); // 距離をM5の画面に表示

  Serial.println(distance); // 距離をUSBシリアル通信でProcessingへ送信

  delay(100);
}