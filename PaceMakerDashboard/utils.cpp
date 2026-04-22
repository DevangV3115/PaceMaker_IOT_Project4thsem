// ═══════════════════════════════════════════════════════════════════
//  MediPulse Pro — Utility Functions (implementation)
// ═══════════════════════════════════════════════════════════════════

#include "utils.h"

const char* levelStr(AlertLevel l) {
  switch (l) {
    case LVL_NOISE:    return "NOISE ALERT";
    case LVL_HEART:    return "HEART ALERT";
    case LVL_CRITICAL: return "CRITICAL";
    default:           return "NORMAL";
  }
}

void pushLog(AlertLevel lvl, int hv, int sv) {
  G.eventLog[G.logHead] = { millis(), lvl, hv, sv };
  G.logHead = (G.logHead + 1) % LOG_SIZE;
  if (G.logCount < LOG_SIZE) G.logCount++;
  G.alertsFired++;
}
