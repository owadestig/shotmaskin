#include <Arduino.h>
extern const int pinLED;
extern const int pinInput;
int relayPin = 12; // D2

void toggle_flow(unsigned long maxOnDuration, int waitState)
{
    // Turn on the LED
    digitalWrite(pinLED, HIGH);
    Serial.println("flow toggled!");
    unsigned long startTime = millis();
    while (millis() - startTime < maxOnDuration)
    {

        // Check if the button state matches the wait state
        if (digitalRead(pinInput) == waitState)
        {
            break;
        }

        delay(10); // Small delay to prevent high CPU usage
    }
    // Turn off the LED
    digitalWrite(pinLED, LOW);
    Serial.println("flow UN-toggled!");
}
void serve_shot(int flowTime, unsigned long maxOnDuration)
{
    Serial.println("shot time!");
    digitalWrite(relayPin, HIGH);
    delay(2000);
    toggle_flow(maxOnDuration, LOW);
    delay(flowTime);
    toggle_flow(maxOnDuration, HIGH);
    delay(2000);
    digitalWrite(relayPin, LOW);
}

void reset_machine(unsigned long maxOnDuration)
{
    digitalWrite(pinLED, HIGH);
    delay(5000);
    digitalWrite(pinLED, LOW);
    if (digitalRead(pinInput) == HIGH)
    {
        toggle_flow(maxOnDuration, HIGH);
    }

    if (digitalRead(pinInput) == LOW)
    {
        toggle_flow(maxOnDuration, HIGH);
        if (digitalRead(pinInput) == HIGH)
        {
            toggle_flow(maxOnDuration, LOW);
        }
    }
    serve_shot(1, maxOnDuration);
}