#ifndef SHOT_H
#define SHOT_H

void toggle_flow(unsigned long maxOnDuration, int waitState);
void serve_shot(int watering_time, unsigned long maxOnDuration);
void resetLED(unsigned long maxOnDuration);
void reset_machine(unsigned long maxOnDuration);
void toggleAux(bool onOrOff);

#endif