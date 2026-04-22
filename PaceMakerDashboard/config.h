// ═══════════════════════════════════════════════════════════════════
//  MediPulse Pro — Configuration
//  All constants, pins, thresholds, and credentials in one place.
// ═══════════════════════════════════════════════════════════════════

#ifndef MEDIPULSE_CONFIG_H
#define MEDIPULSE_CONFIG_H

// ── WiFi credentials ─────────────────────────
#define WIFI_SSID        "Deepak"
#define WIFI_PASS        "........"

// ── Hardware pins ────────────────────────────
#define PIN_SOUND        34      // FC-04 digital output
#define PIN_HEART        35      // Analog heart/pulse sensor
#define PIN_BUZZER       25      // Active buzzer

// ── Heart thresholds ─────────────────────────
#define HEART_LOW        250     // Below → out of range
#define HEART_HIGH       800     // Above → out of range

// ── Alert system ─────────────────────────────
#define SOUND_DEBOUNCE   3       // Consecutive HIGHs for noise alert
#define ALERT_COOLDOWN   5000    // ms between same alert type
#define LOG_SIZE         20      // Circular event log capacity

// ── Buzzer intervals (ms half-period) ────────
#define BUZ_NOISE        150
#define BUZ_HEART        500
#define BUZ_CRITICAL     60

// ── OLED ─────────────────────────────────────
#define OLED_W           128
#define OLED_H           64

// ── I2C pins ─────────────────────────────────
#define I2C_SDA          21
#define I2C_SCL          22

// ── FreeRTOS task config ─────────────────────
#define SENSOR_STACK     4096
#define SENSOR_PRIORITY  2
#define SENSOR_CORE      1

#define WEB_STACK        14336
#define WEB_PRIORITY     1
#define WEB_CORE         0

#endif // MEDIPULSE_CONFIG_H
