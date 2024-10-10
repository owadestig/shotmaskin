#ifndef FCT_H
#define FCT_H

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>


#include "gui/gui.h"
#include "variables.h"
#include "shot.h"

void handleRoot(ESP8266WebServer &server);
void handleToggle(ESP8266WebServer &server);

#endif