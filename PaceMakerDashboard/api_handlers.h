// ═══════════════════════════════════════════════════════════════════
//  MediPulse Pro — API Handlers
//  HTTP endpoint handlers for /data, /logs, /stats, and dashboard
// ═══════════════════════════════════════════════════════════════════

#ifndef MEDIPULSE_API_HANDLERS_H
#define MEDIPULSE_API_HANDLERS_H

#include <WiFi.h>

// HTTP response helpers
void sendHeaders(WiFiClient& c, const char* contentType);

// REST-like API endpoints
void apiData(WiFiClient& c);       // GET /data  → sensor snapshot
void apiLogs(WiFiClient& c);       // GET /logs  → alert history
void apiStats(WiFiClient& c);      // GET /stats → system metrics

// Serve the full HTML dashboard
void sendDashboard(WiFiClient& c);

#endif // MEDIPULSE_API_HANDLERS_H
