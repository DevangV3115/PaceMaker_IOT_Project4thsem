// ═══════════════════════════════════════════════════════════════════
//  MediPulse Pro — OLED Display Module (implementation)
// ═══════════════════════════════════════════════════════════════════

#include "display.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include "config.h"
#include "utils.h"

// ── OLED object definition ──────────────────
Adafruit_SSD1306 oled(OLED_W, OLED_H, &Wire, -1);

void displayInit() {
  Wire.begin(I2C_SDA, I2C_SCL);
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("[WARN] OLED init failed");
  }
  oled.setTextColor(WHITE);
  oled.clearDisplay();
  oled.setTextSize(1);
}

void displayConnecting() {
  oled.clearDisplay();
  oled.setTextSize(1);
  oled.setCursor(0, 0);  oled.println("MediPulse Pro");
  oled.setCursor(0, 12); oled.println("Connecting WiFi...");
  oled.display();
}

void displayReady(const String& ip) {
  oled.clearDisplay();
  oled.setCursor(0, 0);  oled.println("MediPulse Pro");
  oled.setCursor(0, 14); oled.println("Ready!");
  oled.setCursor(0, 28); oled.println(ip);
  oled.display();
}

void displayUpdate(int hv, int sv, AlertLevel lvl) {
  oled.clearDisplay();
  oled.setTextSize(1);

  // Row 0: heart
  oled.setCursor(0, 0);
  oled.print("HR: "); oled.println(hv);

  // Row 1: sound
  oled.setCursor(0, 12);
  oled.print("SND: "); oled.println(sv ? "DETECT" : "quiet");

  // Row 2: status
  oled.setTextSize(lvl >= LVL_CRITICAL ? 2 : 1);
  oled.setCursor(0, 28);
  oled.println(levelStr(lvl));

  // Row 3: readings count
  oled.setTextSize(1);
  oled.setCursor(0, 55);
  oled.print("Reads:");
  xSemaphoreTake(xMutex, portMAX_DELAY);
    oled.println(G.readings);
  xSemaphoreGive(xMutex);

  oled.display();
}
