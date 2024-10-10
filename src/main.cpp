#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "shot.h"
#include "gui/gui.h"

ESP8266WebServer server(80);

const char *ssid = "Shot'O'Clock";
const char *password = "gurk";
int pinLED = 5;
int pinInput = 14;
unsigned long maxOnDuration = 10000;
int flowTime = 2000;

// Serve the HTML content
void handleRoot()
{
  server.send(200, "text/html", htmlContent);
}

void handleToggle()
{
  if (server.hasArg("flowTime"))
  {
    flowTime = server.arg("flowTime").toInt();
  }
  serve_shot(flowTime, maxOnDuration);
  server.send(200, "text/plain", "LED toggled with flowTime = " + String(flowTime) + " ms");
}

void setup()
{
  Serial.begin(115200);
  delay(10);

  // No need for LittleFS if we're serving HTML directly from sketch
  // if (!LittleFS.begin()) {
  //   Serial.println("Failed to mount file system");
  //   return;
  // }
  Serial.println("File system not used");

  pinMode(pinLED, OUTPUT);
  pinMode(pinInput, INPUT_PULLUP);

  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  server.on("/", handleRoot);
  server.on("/toggle", handleToggle);
  server.begin();
  Serial.println("HTTP server started");
  reset_machine(maxOnDuration);
}

void loop()
{
  server.handleClient();
}
