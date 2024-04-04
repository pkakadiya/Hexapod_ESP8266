#include <Arduino.h>
#include "header.h"

#ifdef Limit_Switch

limitSwitchPin[6] = {0, 2, 14, 12, 13, 15};


void InitializeSwitch()
{
    for (int i = 0; i < 6; i++)
    {
        pinMode(limitSwitchPin[i], INPUT);
    }
}
bool legTouchGround() {
    // Iterate through each leg
    for (int i = 0; i < 6; i++) {
        // Read the state of the limit switch
        bool switchState = digitalRead(limitSwitchPin[i]);

        // If any switch is not low, return false
        if (switchState != LOW) {
            return false;
        }
    }

    // If all switches are low, return true
    return true;
}




#endif