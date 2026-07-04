#include <M5Unified.h>
#include <Wire.h>
#include <VL53L0X.h>

VL53L0X tof;

const uint16_t THRESHOLD = 500; // 500mm以内で反応

void setup() {
  auto cfg = M5.config();
  M5.begin(cfg);
  Wire.begin();

  M5.Display.setRotation(1);
  M5.Display.fillScreen(BLACK);
  M5.Display.setTextSize(2);
  M5.Display.setTextColor(WHITE);
  M5.Display.setCursor(20, 20);
  M5.Display.println("Initializing...");

  tof.setTimeout(500);

  if (!tof.init()) {
    M5.Display.fillScreen(RED);
    M5.Display.setCursor(20, 20);
    M5.Display.println("ToF Error");
    while (1);
  }

  tof.startContinuous();
  M5.Display.fillScreen(BLACK);
}

void loop() {
  // --- 距離を取得 ---
  uint16_t distance = tof.readRangeContinuousMillimeters();

  M5.Display.fillScreen(BLACK);

  if (distance < THRESHOLD) { // 距離が500mmより短いとき
    M5.Display.setTextSize(3);
    M5.Display.setCursor(20, 100);
    M5.Display.println("Welcome Home!"); // M5の画面に文字を表示
  }
  delay(100);
}