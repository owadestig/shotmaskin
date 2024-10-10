#include "fct.h"

// Serve the HTML content
void handleRoot(ESP8266WebServer &server)
{
  server.send(200, "text/html", htmlContent);
}

void handleToggle(ESP8266WebServer &server)
{
  if (server.hasArg("flowTime"))
  {
    flowTime = server.arg("flowTime").toInt();
  }
  serve_shot(flowTime, maxOnDuration);
  server.send(200, "text/plain", "LED toggled with flowTime = " + String(flowTime) + " ms");
}