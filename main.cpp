#include <Arduino.h>
#include <header.h>
//#include <LittleFS.h>

//File dataFile;

int loopTime;
Vector2 directionInput(0, 0);
float rotationInput; 
float groundClearance; 
float stepRadius;
float maxSpeed;
int mode;
State HexapodState = State::SITTING;




void setup()
{
#ifdef WEBSERVER // initialite webserver
  server_init();
#endif
 
#ifdef SERVO // initialite Servos
  Servo_init();
  
#endif

/*
#ifdef SERVO_CALIBRATION
  HexapodState = State::STANDING;
#endif

Serial.begin(115200);
if(LittleFS.begin()){
  Serial.println("Mount Successfully...");
}else{
  Serial.println("Failed to mount");
  return;
}
dataFile = LittleFS.open("/data.txt","w");
if (!dataFile)
{
  Serial.println("Failed to open file forwriting");
  return;
}
dataFile.println("X, Y, Z");
dataFile.close();
*/
}


void loop()
{
  
#ifdef WEBSERVER

  while (WiFi.status() == WL_CONNECTED)
  {
    #ifdef SERVO
    
    client();
    
    if (mode == 0) /*&& (HexapodState == State::STANDING || HexapodState == State::WALKING)*/
    {
      sitDown();
    }
    else if (mode == 1) /*&&  HexapodState == State::SITTING*/
    {
      standUp();
    }

    else if (mode == 2) /*&& (HexapodState == State::STANDING || HexapodState == State::WALKING)*/
    {
      rotationInput = 0;
      maxSpeed = 100;
      directionInput = Vector2::forward;
      directionInput = directionInput.inverse();
      groundClearance = 100;
      stepRadius = 30;
        
      for (int i = 0; i < 6; i++)
      {
        walkCycle();
        Leg_update(i); 
      }
      
      // for incress the speed incress the speed 
      /*note: give loopTime value in tripodgait.cpp directly
      under walkcycle and change current loop in to else if loop
      with same rest of the part */
      loopTime = 5000; //speed of walkcycle

    }
    else if (mode == 3) /*&& (HexapodState == State::STANDING || HexapodState == State::WALKING)*/
    {
      rotationInput = 0;
      maxSpeed = 100;
      directionInput = Vector2::back;
      directionInput = directionInput.inverse();
      groundClearance = 100;
      stepRadius = 30;
        
      for (int i = 0; i < 6; i++)
      {
        walkCycle();
        Leg_update(i); 
      }
      loopTime = 5000; //speed of walkcycle
    }
    else if (mode == 4) /*&& (HexapodState == State::STANDING || HexapodState == State::WALKING)*/
    {
      rotationInput = 0;
      maxSpeed = 100;
      directionInput = Vector2::right;
      directionInput = directionInput.inverse();
      groundClearance = 100;
      stepRadius = 30;
        
      for (int i = 0; i < 6; i++)
      {
        walkCycle();
        Leg_update(i); 
      }
      loopTime = 5000; //speed of walkcycle
    }

    else if (mode == 5) /*&& (HexapodState == State::STANDING || HexapodState == State::WALKING)*/
    {
      rotationInput = 0;
      maxSpeed = 100;
      directionInput = Vector2::left;
      directionInput = directionInput.inverse();
      groundClearance = 100;
      stepRadius = 30;
        
      for (int i = 0; i < 6; i++)
      {
        walkCycle();
        Leg_update(i); 
      }
      loopTime = 5000; //speed of walkcycle
    }
    else if (mode == 6)
    {
      rotationInput = 10; 
      maxSpeed = 100;
      directionInput = Vector2::zero;
      directionInput = directionInput.inverse();
      groundClearance = 100;
      stepRadius = 30;
        
      for (int i = 0; i < 6; i++)
      {
        walkCycle();
        Leg_update(i); 
      }
      loopTime = 5000; //speed of walkcycle
    }
    else if (mode == 7)
    {
      rotationInput = -10; 
      maxSpeed = 100;
      directionInput = Vector2::forward;
      directionInput = directionInput.inverse();
      groundClearance = 100;
      stepRadius = 30;
        
      for (int i = 0; i < 6; i++)
      {
        walkCycle();
        Leg_update(i); 
      }
      loopTime = 5000; //speed of walkcycle
    }
    #endif
  }
#endif
/*
dataFile = LittleFS.open("/data.txt", "a");

if(dataFile){
    dataFile.print(angle_0);
    dataFile.print(",");
    dataFile.print(angle_1);
    dataFile.print(",");
    dataFile.print(angle_2);

    dataFile.close();
}else{
  Serial.println("Failed to open file appending");
}
*/
}

