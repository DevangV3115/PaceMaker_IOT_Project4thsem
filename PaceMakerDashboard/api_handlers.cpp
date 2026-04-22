// ═══════════════════════════════════════════════════════════════════
//  MediPulse Pro — API Handlers (implementation)
// ═══════════════════════════════════════════════════════════════════

#include "api_handlers.h"
#include "types.h"
#include "utils.h"
#include "dashboard.h"

// ── Common HTTP headers ─────────────────────────────────────────
void sendHeaders(WiFiClient& c, const char* ct) {
  c.println("HTTP/1.1 200 OK");
  c.print("Content-Type: "); c.println(ct);
  c.println("Access-Control-Allow-Origin: *");
  c.println("Cache-Control: no-cache, no-store, must-revalidate");
  c.println("Connection: close");
  c.println();
}

// ── GET /data → current sensor snapshot ─────────────────────────
void apiData(WiFiClient& c) {
  int hv, sv; AlertLevel al; char st[20];
  xSemaphoreTake(xMutex, portMAX_DELAY);
    hv = G.heartVal;
    sv = G.soundVal;
    al = G.alertLevel;
    memcpy(st, G.statusStr, 20);
  xSemaphoreGive(xMutex);

  char buf[160];
  snprintf(buf, sizeof(buf),
    "{\"heart\":%d,\"sound\":%d,\"alert\":%s,\"alertType\":%d,\"status\":\"%s\"}",
    hv, sv, al ? "true" : "false", (int)al, st);

  sendHeaders(c, "application/json");
  c.println(buf);
}

// ── GET /logs → alert event history (newest first) ──────────────
void apiLogs(WiFiClient& c) {
  sendHeaders(c, "application/json");

  xSemaphoreTake(xMutex, portMAX_DELAY);
    int count = G.logCount;
    int head  = G.logHead;
    LogEntry snap[LOG_SIZE];
    memcpy(snap, G.eventLog, sizeof(G.eventLog));
  xSemaphoreGive(xMutex);

  c.print("[");
  for (int i = 0; i < count; i++) {
    int idx = ((head - 1 - i) % LOG_SIZE + LOG_SIZE) % LOG_SIZE;
    LogEntry& e = snap[idx];
    uint32_t sec = e.ts / 1000;

    char buf[160];
    snprintf(buf, sizeof(buf),
      "%s{\"time\":\"%02lu:%02lu:%02lu\",\"level\":%d,\"type\":\"%s\",\"heart\":%d,\"sound\":%d}",
      i > 0 ? "," : "",
      (unsigned long)(sec / 3600),
      (unsigned long)((sec % 3600) / 60),
      (unsigned long)(sec % 60),
      (int)e.level, levelStr(e.level),
      e.heart, e.sound);
    c.print(buf);
  }
  c.println("]");
}

// ── GET /stats → system metrics ─────────────────────────────────
void apiStats(WiFiClient& c) {
  uint32_t reads, alerts, upMs;
  xSemaphoreTake(xMutex, portMAX_DELAY);
    reads  = G.readings;
    alerts = G.alertsFired;
    upMs   = millis() - G.bootTime;
  xSemaphoreGive(xMutex);

  uint32_t s = upMs / 1000;
  char buf[220];
  snprintf(buf, sizeof(buf),
    "{\"readings\":%lu,\"alerts\":%lu,"
    "\"uptime\":\"%02lu:%02lu:%02lu\",\"uptimeMs\":%lu,"
    "\"freeHeap\":%lu,\"minHeap\":%lu}",
    (unsigned long)reads,
    (unsigned long)alerts,
    (unsigned long)(s / 3600),
    (unsigned long)((s % 3600) / 60),
    (unsigned long)(s % 60),
    (unsigned long)upMs,
    (unsigned long)ESP.getFreeHeap(),
    (unsigned long)ESP.getMinFreeHeap());

  sendHeaders(c, "application/json");
  c.println(buf);
}

// ── Serve full dashboard HTML (from PROGMEM) ────────────────────
void sendDashboard(WiFiClient& c) {
  sendHeaders(c, "text/html; charset=utf-8");
  c.print(HTML_CHUNK_CSS);
  c.print(HTML_CHUNK_PAGES);
  c.print(HTML_CHUNK_DASH);
  c.print(HTML_CHUNK_JS);
}
