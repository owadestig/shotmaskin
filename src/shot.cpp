#include "Utils.h"

const int pinLED = 5;
const int pinInput = 14;

void toggle_flow(int maxOnDuration, int waitState)
{
    // Turn on the LED
    digitalWrite(pinLED, HIGH);
    unsigned long startTime = millis();
    bool ButtonSignal = false;

    while (millis() - startTime < maxOnDuration)
    {
        // Read the button state directly without debouncing
        int buttonState = digitalRead(pinInput);

        // Check if the button state matches the wait state
        if (buttonState == waitState)
        {
            ButtonSignal = true;
            break;
        }

        delay(10); // Small delay to prevent high CPU usage
    }
    // Turn off the LED
    digitalWrite(pinLED, LOW);
}
void serve_shot(int watering_time, int maxOnDuration)
{
    toggle_flow(maxOnDuration, LOW);
    delay(watering_time);
    toggle_flow(maxOnDuration, HIGH);
}

void resetLED(int maxOnDuration)
{
    serve_shot(1, maxOnDuration);
}