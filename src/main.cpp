#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "shot.h"

ESP8266WebServer server(80);

const char *ssid = "Shot'O'Clock";
const char *password = "gurk";
int pinLED = 5;
int pinInput = 14;
unsigned long maxOnDuration = 10000;
int flowTime = 2000;

// HTML content embedded directly into the sketch
const char *htmlContent = R"rawliteral(
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>ESP8266 LED Control</title>
    <style>
        @keyframes colorChange {
            0% {
                background-color: #39ff14;
            }

            /* Neon Green */
            20% {
                background-color: #ff073a;
            }

            /* Neon Red */
            40% {
                background-color: #f7f000;
            }

            /* Neon Yellow */
            60% {
                background-color: #1f51ff;
            }

            /* Neon Blue */
            80% {
                background-color: #ff007f;
            }

            /* Neon Pink */
            100% {
                background-color: #39ff14;
            }

            /* Back to Neon Green */
        }

        @keyframes pulse {

            0%,
            100% {
                transform: scale(1);
            }

            50% {
                transform: scale(1.1);
            }
        }

        body {
            display: flex;
            justify-content: center;
            align-items: center;
            height: 100vh;
            margin: 0;
            font-family: Arial, sans-serif;
            animation: colorChange 6s linear infinite;
            /* Smooth color transition */
        }

        .container {
            text-align: center;
            padding: 20px;
            border-radius: 8px;
            background-color: #ffffff;
            box-shadow: 0 4px 8px rgba(0, 0, 0, 0.2);
            opacity: 0.8;
            /* Slightly opaque */
            animation: pulse 0.5s ease-in-out infinite;
            /* Beating effect at 120 BPM */
        }

        h1 {
            font-size: 24px;
            margin-bottom: 20px;
            color: #333;
        }

        button {
            padding: 10px 20px;
            font-size: 16px;
            color: #fff;
            background-color: #007BFF;
            border: none;
            border-radius: 5px;
            cursor: pointer;
            transition: background-color 0.3s ease;
        }

        button:hover {
            background-color: #0056b3;
        }
    </style>
</head>

<body>
    <div class="container">
        <h1>Shot Machine</h1>
        <input type="number" id="flowTime" placeholder="Enter flow time (ms)" min="0">
        <button onclick="serve_shot()">Serve Shot</button>
    </div>

    <script>
        let isToggling = false;  // Flag to prevent multiple requests

        function serve_shot() {
            if (isToggling) return;  // Prevent multiple requests
            isToggling = true;
            const flowTime = document.getElementById('flowTime').value;
            fetch(`/toggle?flowTime=${flowTime}`)
                .then(response => response.text())
                .then(text => {
                    console.log(text);
                    isToggling = false;  // Allow further requests
                })
                .catch(error => {
                    console.error('Error:', error);
                    isToggling = false;  // Allow further requests even if there's an error
                });
        }
    </script>
</body>

</html>
)rawliteral";

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
