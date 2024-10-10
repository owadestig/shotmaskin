#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#include "functions/shot.h"
#include "functions/fct.h"
#include "credentials.h"
#include "variables.h"

ESP8266WebServer server(80);

void setup()
{
  Serial.begin(115200);
  delay(10);

  pinMode(motorPin, OUTPUT);
  pinMode(auxPin, OUTPUT);
  pinMode(inputPin, INPUT_PULLUP);

  digitalWrite(motorPin, LOW);
  digitalWrite(auxPin, LOW);

  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  Serial.print("\n");

  server.on("/", []() { handleRoot(server); });
  server.on("/", []() { handleToggle(server); });
  server.begin();
  Serial.println("HTTP server started");
  reset_machine(maxOnDuration);
}

void loop()
{
  server.handleClient();
}
