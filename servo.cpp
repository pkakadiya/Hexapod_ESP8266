#include <Arduino.h>
#include "header.h"

// ================================================================
// ===                          Servo                           ===
// ================================================================
#ifdef SERVO

Adafruit_PWMServoDriver servoDriver_0 = Adafruit_PWMServoDriver();
Adafruit_PWMServoDriver servoDriver_1 = Adafruit_PWMServoDriver(0x41);

Leg_Struct Leg[6];

//const int limitSwitchPin[6] = {0, 2, 14, 12, 13, 15};

void Servo_init()
{
    servoDriver_0.begin();
    servoDriver_0.setOscillatorFrequency(27000000);
    servoDriver_0.setPWMFreq(SERVO_FREQ); // Analog servos run at ~60 Hz updates

    servoDriver_1.begin();
    servoDriver_1.setOscillatorFrequency(27000000);
    servoDriver_1.setPWMFreq(SERVO_FREQ); // Analog servos run at ~60 Hz updates

#pragma region configureServos

// for correct Servo Placenment check the Leg Configuration and Servo Leg Configuration Images
#pragma region Leg_0
    Leg[0].Servo[0].ch = 2;
    Leg[0].Servo[1].ch = 1;
    Leg[0].Servo[2].ch = 0;

    Leg[0].Servo[2].minAngle = 20;
    Leg[0].Servo[2].maxAngle = 160;

    Leg[0].Servo[0].angleOffset = 0;
    Leg[0].Servo[1].angleOffset = 0;
    Leg[0].Servo[2].angleOffset = -40;

    Leg[0].mirrored = false;
    Leg[0].mountAngle = -40;

    //Leg[0].LIMIT_SWITCH_STATE = digitalRead(limitSwitchPin[0]);
    

#pragma endregion

#pragma region Leg_1
    Leg[1].Servo[0].ch = 6;
    Leg[1].Servo[1].ch = 5;
    Leg[1].Servo[2].ch = 4;

    Leg[1].Servo[2].minAngle = 20;
    Leg[1].Servo[2].maxAngle = 160;

    Leg[1].Servo[0].angleOffset = 0;
    Leg[1].Servo[1].angleOffset = 3;
    Leg[1].Servo[2].angleOffset = -40;

    Leg[1].mirrored = false;
    Leg[1].mountAngle = -90;
    
    //Leg[1].LIMIT_SWITCH_STATE = digitalRead(limitSwitchPin[1]);
    
#pragma endregion

#pragma region Leg_2
    Leg[2].Servo[0].ch = 13;
    Leg[2].Servo[1].ch = 14;
    Leg[2].Servo[2].ch = 15;

    Leg[2].Servo[2].minAngle = 20;
    Leg[2].Servo[2].maxAngle = 160;

    Leg[2].Servo[0].angleOffset = 0;
    Leg[2].Servo[1].angleOffset = 0;
    Leg[2].Servo[2].angleOffset = -40;

    Leg[2].mirrored = false;
    Leg[2].mountAngle = -140;
    
    //Leg[2].LIMIT_SWITCH_STATE = digitalRead(limitSwitchPin[2]);
    
#pragma endregion

#pragma region Leg_3
    Leg[3].Servo[0].ch = 18;
    Leg[3].Servo[1].ch = 17;
    Leg[3].Servo[2].ch = 16;

    Leg[3].Servo[2].minAngle = 20;
    Leg[3].Servo[2].maxAngle = 160;

    Leg[3].Servo[0].angleOffset = 0;
    Leg[3].Servo[1].angleOffset = 0-7;
    Leg[3].Servo[2].angleOffset = 10;

    Leg[3].mirrored = true;
    Leg[3].mountAngle = 140;
    
    //Leg[3].LIMIT_SWITCH_STATE = digitalRead(limitSwitchPin[3]);
    
#pragma endregion

#pragma region Leg_4
    Leg[4].Servo[0].ch = 25;
    Leg[4].Servo[1].ch = 26;
    Leg[4].Servo[2].ch = 27;

    Leg[4].Servo[2].minAngle = 20;
    Leg[4].Servo[2].maxAngle = 160;

    Leg[4].mirrored = true;
    Leg[4].mountAngle = 90;
    

    Leg[4].Servo[0].angleOffset = 0;
    Leg[4].Servo[1].angleOffset = 5;
    Leg[4].Servo[2].angleOffset = 40;

    //Leg[4].LIMIT_SWITCH_STATE = digitalRead(limitSwitchPin[4]);
    
#pragma endregion

#pragma region Leg_5
    Leg[5].Servo[0].ch = 29;
    Leg[5].Servo[1].ch = 30;
    Leg[5].Servo[2].ch = 31;

    Leg[5].Servo[2].minAngle = 20;
    Leg[5].Servo[2].maxAngle = 160;

    Leg[5].Servo[0].angleOffset = 0;
    Leg[5].Servo[1].angleOffset = 3;
    Leg[5].Servo[2].angleOffset = 40;

    Leg[5].mirrored = true;
    Leg[5].mountAngle = 40;

    //Leg[5].LIMIT_SWITCH_STATE = digitalRead(limitSwitchPin[5]);
    

#pragma endregion
    for (int i = 0; i < int(sizeof(Leg) / sizeof(Leg[0])); i++)
    {
        Leg[i].Servo[1].minAngle = 0;
        Leg[i].Servo[1].maxAngle = 180;
    }

#pragma endregion
}


void Servo_update(const Servo_Struct &servo, const int &onValue)
{
    int angle = constrain(servo.targetAngle, servo.minAngle, servo.maxAngle);
    // check which servo driver to use
    if (servo.ch < 16)
        servoDriver_0.setPWM(servo.ch, onValue, SERVO_BASELINE + (angle + servo.angleOffset) * 2);
    else if (servo.ch < 32)
        servoDriver_1.setPWM(servo.ch - 16, onValue, SERVO_BASELINE + (angle + servo.angleOffset) * 2);
}

void Servo_update(const int &servoCH, const int &angle, const int &onValue)
{
    // check which servo driver to use
    if (servoCH < 16)
        servoDriver_0.setPWM(servoCH, onValue, SERVO_BASELINE + angle * 2);
    else if (servoCH < 32)
        servoDriver_1.setPWM(servoCH - 16, onValue, SERVO_BASELINE + angle * 2);
}

// turns off the output for the servo
void Servo_deactivateAll()
{
    // loop through each leg
    for (size_t i = 0; i < 6; i++)
    {
        // loop through each servo in leg
        for (size_t o = 0; o < 3; o++)
        {
            Servo_update(Leg[i].Servo[o], 4096);
        }
    }
}

// used to test wether min values are correct
void Servo_moveAllToMinValue()
{
    // loop through each leg
    for (size_t i = 0; i < 6; i++)
    {
        // loop through each servo in leg
        for (size_t o = 0; o < 3; o++)
        {
            int oldTargetAngle = Leg[i].Servo[o].targetAngle;

            Leg[i].Servo[o].targetAngle = Leg[0].Servo[o].minAngle - abs(Leg[0].Servo[o].angleOffset);

            Servo_update(Leg[i].Servo[o]);

            Leg[i].Servo[o].targetAngle = oldTargetAngle;
        }
    }
}

// used to test wether max values are correct
void Servo_moveAllToMaxValue()
{
    // loop through each leg
    for (size_t i = 0; i < 6; i++)
    {
        // loop through each servo in leg
        for (size_t o = 0; o < 3; o++)
        {
            int oldTargetAngle = Leg[i].Servo[o].targetAngle;

            Leg[i].Servo[o].targetAngle = Leg[0].Servo[o].maxAngle + abs(Leg[0].Servo[o].angleOffset);

            Servo_update(Leg[i].Servo[o]);

            Leg[i].Servo[o].targetAngle = oldTargetAngle;
        }
    }
}

void Leg_update(const int &legID)
{
    calcLegServoAngles(Leg[legID]);

    Servo_update(Leg[legID].Servo[0]);
    Servo_update(Leg[legID].Servo[1]);
    Servo_update(Leg[legID].Servo[2]);
}

// update every output as needed to reflect any changes
void Output_update()
{
    Leg_update(0);
    Leg_update(1);
    Leg_update(2);
    Leg_update(3);
    Leg_update(4);
    Leg_update(5);
}

#endif

