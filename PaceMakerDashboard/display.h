// ═══════════════════════════════════════════════════════════════════
//  MediPulse Pro — OLED Display Module
// ═══════════════════════════════════════════════════════════════════

#ifndef MEDIPULSE_DISPLAY_H
#define MEDIPULSE_DISPLAY_H

#include <Adafruit_SSD1306.h>
#include "types.h"

// Global OLED object — defined in display.cpp
extern Adafruit_SSD1306 oled;

// Initialize OLED hardware
void displayInit();

// Show "Connecting WiFi..." screen
void displayConnecting();

// Show "Ready!" with IP address
void displayReady(const String& ip);

// Real-time sensor data update (called from sensorTask)
void displayUpdate(int hv, int sv, AlertLevel lvl);

#endif // MEDIPULSE_DISPLAY_H
