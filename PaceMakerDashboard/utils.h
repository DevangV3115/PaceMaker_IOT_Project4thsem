// ═══════════════════════════════════════════════════════════════════
//  MediPulse Pro — Utility Functions
// ═══════════════════════════════════════════════════════════════════

#ifndef MEDIPULSE_UTILS_H
#define MEDIPULSE_UTILS_H

#include "types.h"

// Convert AlertLevel to human-readable string
const char* levelStr(AlertLevel l);

// Push an event into the circular log (call with mutex HELD)
void pushLog(AlertLevel lvl, int hv, int sv);

#endif // MEDIPULSE_UTILS_H
