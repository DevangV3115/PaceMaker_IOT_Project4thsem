// ═══════════════════════════════════════════════════════════════════
//  MediPulse Pro — Type Definitions
//  Enums, structs, and extern declarations for shared globals.
// ═══════════════════════════════════════════════════════════════════

#ifndef MEDIPULSE_TYPES_H
#define MEDIPULSE_TYPES_H

#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>
#include "config.h"

// ── Alert severity levels ────────────────────
enum AlertLevel : uint8_t {
  LVL_NORMAL   = 0,
  LVL_NOISE    = 1,
  LVL_HEART    = 2,
  LVL_CRITICAL = 3
};

// ── Single event log entry ───────────────────
struct LogEntry {
  uint32_t   ts;       // millis() timestamp
  AlertLevel level;
  int        heart;
  int        sound;
};

// ── Shared state (accessed via mutex) ────────
struct SharedState {
  int        heartVal    = 0;
  int        soundVal    = 0;
  AlertLevel alertLevel  = LVL_NORMAL;
  char       statusStr[20] = "NORMAL";
  uint32_t   readings    = 0;
  uint32_t   alertsFired = 0;
  uint32_t   bootTime    = 0;

  // Circular event log
  LogEntry   eventLog[LOG_SIZE];
  int        logHead     = 0;
  int        logCount    = 0;
};

// ── Extern declarations ──────────────────────
// Defined once in MediPulsePro.ino
extern SharedState        G;
extern SemaphoreHandle_t  xMutex;

#endif // MEDIPULSE_TYPES_H
