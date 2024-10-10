#include <Arduino.h>
#include "shot.h"
#include "variables.h"

extern const int ledPin;
extern const int inputPin;


/// @brief serves shot
/// @param flowTime shot flow time in ms
/// @param maxOnDuration max motor spin time if no input. This means something in hardware is fucked
void serve_shot(int flowTime, unsigned long maxOnDuration)
{
    Serial.println("shot time!");
    digitalWrite(auxPin, HIGH); // turns on aux output two seconds before motor (nothing to do with motor)
    delay(2000);
    toggle_flow(maxOnDuration, LOW);
    delay(flowTime);
    toggle_flow(maxOnDuration, HIGH);
    delay(2000);
    digitalWrite(auxPin, LOW);
}
/// @brief turns on aux output
/// @param onOrOff choose if on or off
void toggle_aux(bool onOrOff) {
    digitalWrite(auxPin, onOrOff);
}

/// @brief toggles flow
/// @param maxOnDuration max motor spin time if no input. This means something in hardware is fucked
/// @param waitState desired state to stop at. LOW = open, HIGH = closed
void toggle_flow(unsigned long maxOnDuration, int waitState)
{
    // Turn on the LED
    digitalWrite(ledPin, HIGH);
    Serial.println("flow toggled!");
    unsigned long startTime = millis();
    while (millis() - startTime < maxOnDuration)
    {

        // Check if the button state matches the wait state
        if (digitalRead(inputPin) == waitState)
        {
            break;
        }

        delay(10); // Small delay to prevent high CPU usage

    }
    // Turn off the LED
    digitalWrite(ledPin, LOW);
    Serial.println("flow UN-toggled!");
}

/// @brief resets maching to closed state.
/// @param maxOnDuration max motor spin time if no input. This means something in hardware is fucked
void reset_machine(unsigned long maxOnDuration)
{
    digitalWrite(ledPin, HIGH);
    delay(5000);
    digitalWrite(ledPin, LOW);

    //Gör den hör funktionen ens något? Den kör ju på input high och snurrar motorn tills input blir high, vilket borde vara direkt.
    if (digitalRead(inputPin) == HIGH)
    {
        toggle_flow(maxOnDuration, HIGH);
    }

    if (digitalRead(inputPin) == LOW)
    {
        toggle_flow(maxOnDuration, HIGH);
    
    if (digitalRead(inputPin) == HIGH)
    {
        toggle_flow(maxOnDuration, LOW);
    }
    }
    serve_shot(1, maxOnDuration); // Verfur?
}