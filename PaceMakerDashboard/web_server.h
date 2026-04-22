// ═══════════════════════════════════════════════════════════════════
//  MediPulse Pro — Web Server Task
//  Runs on Core 0: accepts HTTP connections and routes requests.
// ═══════════════════════════════════════════════════════════════════

#ifndef MEDIPULSE_WEB_SERVER_H
#define MEDIPULSE_WEB_SERVER_H

#include <WiFi.h>

// Global server object — defined in web_server.cpp
extern WiFiServer server;

// FreeRTOS task entry point — pinned to WEB_CORE
void webTask(void* param);

#endif // MEDIPULSE_WEB_SERVER_H
