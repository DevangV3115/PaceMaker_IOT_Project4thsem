// ═══════════════════════════════════════════════════════════════════
//  MediPulse Pro — Sensor Task (implementation)
//  100 ms cycle: read → alert detect → buzzer → OLED
// ═══════════════════════════════════════════════════════════════════

#include "sensor_task.h"
#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "config.h"
#include "types.h"
#include "utils.h"
#include "display.h"

void sensorTask(void*) {
  // ── Per-task local state ───────────────────
  int      soundStreak    = 0;
  int      heartOutCount  = 0;
  uint32_t lastAlertAt[4] = {0};
  bool     buzState       = false;
  uint32_t buzToggle      = 0;

  for (;;) {
    uint32_t now = millis();

    // ── 1. Read sensors ──────────────────────
    int sv = digitalRead(PIN_SOUND);
    int hv = analogRead(PIN_HEART);

    // ── 2. Sound debounce ────────────────────
    soundStreak = (sv == HIGH) ? soundStreak + 1 : 0;
    bool soundTripped = (soundStreak >= SOUND_DEBOUNCE);

    // ── 3. Heart rolling counter ─────────────
    bool heartOut = (hv < HEART_LOW || hv > HEART_HIGH);
    if (heartOut) {
      if (heartOutCount < 50) heartOutCount++;
    } else {
      heartOutCount = max(0, heartOutCount - 2);
    }
    bool heartTripped = (heartOutCount >= 10);

    // ── 4. Determine alert level ─────────────
    AlertLevel lvl;
    if      (soundTripped && heartTripped) lvl = LVL_CRITICAL;
    else if (heartTripped)                 lvl = LVL_HEART;
    else if (soundTripped)                 lvl = LVL_NOISE;
    else                                   lvl = LVL_NORMAL;

    // ── 5. Cooldown-gated logging ────────────
    bool doLog = false;
    if (lvl != LVL_NORMAL && now - lastAlertAt[lvl] > ALERT_COOLDOWN) {
      lastAlertAt[lvl] = now;
      doLog = true;
    }

    // ── 6. Update shared state ───────────────
    xSemaphoreTake(xMutex, portMAX_DELAY);
      G.heartVal   = hv;
      G.soundVal   = sv;
      G.alertLevel = lvl;
      strncpy(G.statusStr, levelStr(lvl), 19);
      G.readings++;
      if (doLog) pushLog(lvl, hv, sv);
    xSemaphoreGive(xMutex);

    // ── 7. Non-blocking buzzer ───────────────
    uint32_t bInt = 0;
    switch (lvl) {
      case LVL_CRITICAL: bInt = BUZ_CRITICAL; break;
      case LVL_HEART:    bInt = BUZ_HEART;    break;
      case LVL_NOISE:    bInt = BUZ_NOISE;    break;
      default:
        digitalWrite(PIN_BUZZER, LOW);
        buzState = false;
        break;
    }
    if (lvl != LVL_NORMAL && now - buzToggle >= bInt) {
      buzState = !buzState;
      digitalWrite(PIN_BUZZER, buzState ? HIGH : LOW);
      buzToggle = now;
    }

    // ── 8. OLED update ───────────────────────
    displayUpdate(hv, sv, lvl);

    vTaskDelay(pdMS_TO_TICKS(100));
  }
}
