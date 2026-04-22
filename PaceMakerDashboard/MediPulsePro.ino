// ╔══════════════════════════════════════════════════════════════════╗
// ║           MediPulse Pro — Smart Health Monitor v2.0              ║
// ║  ESP32 + FreeRTOS + Multi-File Modular Architecture              ║
// ║                                                                  ║
// ║  This is the ENTRY POINT. Open this file in Arduino IDE.         ║
// ║  All other .h/.cpp files in this folder are auto-compiled.       ║
// ╚══════════════════════════════════════════════════════════════════╝

// ── Framework includes ───────────────────────
#include <WiFi.h>
#include <Wire.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/semphr.h>

// ── Project modules ──────────────────────────
#include "config.h"
#include "types.h"
#include "display.h"
#include "sensor_task.h"
#include "web_server.h"

// ═══════════════════════════════════════════════════════════════════
//  GLOBAL SHARED STATE — single definition
//  Other modules access via `extern` in types.h
// ═══════════════════════════════════════════════════════════════════

SharedState        G;
SemaphoreHandle_t  xMutex;

// ═══════════════════════════════════════════════════════════════════
//  SETUP
// ═══════════════════════════════════════════════════════════════════

void setup() {
  Serial.begin(115200);
  Serial.println("\n╔══════════════════════════╗");
  Serial.println("║  MediPulse Pro  v2.0     ║");
  Serial.println("╚══════════════════════════╝");

  // ── Hardware init ──────────────────────────
  pinMode(PIN_BUZZER, OUTPUT);
  pinMode(PIN_SOUND, INPUT);
  digitalWrite(PIN_BUZZER, LOW);

  // ── Mutex ──────────────────────────────────
  xMutex = xSemaphoreCreateMutex();
  configASSERT(xMutex);
  G.bootTime = millis();

  // ── OLED ───────────────────────────────────
  displayInit();
  displayConnecting();

  // ── WiFi ───────────────────────────────────
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.print("WiFi connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(300);
    Serial.print(".");
  }
  String ip = WiFi.localIP().toString();
  Serial.println("\n✓ Connected! IP: " + ip);

  displayReady(ip);

  // ── Web server ─────────────────────────────
  server.begin();

  // ── FreeRTOS tasks ─────────────────────────
  xTaskCreatePinnedToCore(
    sensorTask, "Sensor",
    SENSOR_STACK, NULL, SENSOR_PRIORITY, NULL, SENSOR_CORE
  );
  xTaskCreatePinnedToCore(
    webTask, "Web",
    WEB_STACK, NULL, WEB_PRIORITY, NULL, WEB_CORE
  );

  Serial.println("✓ FreeRTOS tasks launched");
  Serial.println("✓ Open: http://" + ip);
}

// ═══════════════════════════════════════════════════════════════════
//  LOOP — idle (FreeRTOS tasks own everything)
// ═══════════════════════════════════════════════════════════════════

void loop() {
  vTaskDelay(portMAX_DELAY);
}
