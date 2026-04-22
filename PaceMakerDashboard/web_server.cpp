// ═══════════════════════════════════════════════════════════════════
//  MediPulse Pro — Web Server Task (implementation)
// ═══════════════════════════════════════════════════════════════════

#include "web_server.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "api_handlers.h"

// ── Server object definition ────────────────
WiFiServer server(80);

void webTask(void*) {
  for (;;) {
    WiFiClient client = server.available();
    if (!client) {
      vTaskDelay(pdMS_TO_TICKS(5));
      continue;
    }

    // Wait up to 300 ms for data
    uint32_t t = millis();
    while (!client.available() && millis() - t < 300) {
      vTaskDelay(pdMS_TO_TICKS(1));
    }
    if (!client.available()) {
      client.stop();
      continue;
    }

    // Read request line
    String req = client.readStringUntil('\r');

    // Consume remaining HTTP headers
    while (client.connected()) {
      if (client.available()) {
        String line = client.readStringUntil('\n');
        if (line == "\r" || line.length() == 0) break;
      } else {
        vTaskDelay(pdMS_TO_TICKS(1));
        if (millis() - t > 800) break;  // timeout
      }
    }

    // ── Route request ────────────────────────
    if      (req.indexOf("GET /data")  != -1) apiData(client);
    else if (req.indexOf("GET /logs")  != -1) apiLogs(client);
    else if (req.indexOf("GET /stats") != -1) apiStats(client);
    else                                       sendDashboard(client);

    client.stop();
  }
}
