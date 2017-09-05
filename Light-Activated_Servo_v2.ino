/* 
Light-Activated Servo Motor

Written by:
Michael Wozniak

Created: 08/04/2017
Last Updated: 08/20/2017

The goal of this project is to activate a servo motor when light is applied to a light sensor.
A light sensor is utilized to read in ambient light.  When light entering the sensor reads above
600 as defined by the sensor, the code activates the servo motor then ceases.
*/ 

#include <Servo.h>

int const modeSelection = 2;  // Set equal to '1' for time-delay testing function.
                              // Set equal to '2' for light-activated control
                              int const lightThreshold = 600; // Initialize the activation threshold of the light sensor
int const timeDelay_test = 10000; // Time delat in milliseconds servo will activate afeter power is applied to board
int const timeDelay_light = 5000;  // Time delay in milliseconds servo will activate after drone lights turned on
int const openAngle = 160;   // Angle to move servo to in order to open door
int const closeAngle = 20;   // Angle to move servo to in order to "reset"

int sensorPin = A0;  // Initialize the input pin for light sensor
int sensorValue = 0; // Initialize the starting value of the light sensor reading
int servoPin = 8;    // Initialize the output pin on the Arduino which will send 
                     // signal to servo to activate servo
Servo Servo;         // Initializes the variable Servo as a servo motor object

void setup() 
  { 
    pinMode(2, OUTPUT); //pin connected to the relay 
    Serial.begin(9600); //sets serial port for communication 
    Servo.attach(servoPin);
    Servo.write(closeAngle);
    Servo.detach();
  } 
  
  void loop() 
  {
      if(modeSelection == 1)
      {
        // Testing & Proof of Concept Code
        // Servo will activate after a set number of milliseconds after power is applied to the board

        delay(timeDelay_test); // Delay the amount of time specified by timeDelay_test
        servoActivation();
      }


      if(modeSelection == 2)
      {
        // Production Code
        // Servo will activate 1 second after drone LED is activated

        sensorValue = analogRead(sensorPin); // Reads in value of the "light" entering the sensor
                                             // and stores it in sensorValue variable
   
        Serial.print("Analog reading = ");  // Print "Analog Reading = "" to the display screen
        Serial.println(sensorValue);        // Print the light sensor value to the screen
        
        if(sensorValue > lightThreshold)  // If light is applied to the sensor above the value defined above in "lightThreshold" variable, then continue the code below 
        {
          delay(timeDelay_light);         // Wait number of milliseconds in parentheses before continuing
          servoActivation();
        }
      }
  }





void servoActivation()
  {
    Servo.attach(servoPin); // Initialize communication to servo motor
             
    Servo.write(openAngle);       // Move servo position to 160 degrees
    delay(1000);            // Wait number of milliseconds in parentheses before continuing
  
    Servo.write(closeAngle);        // Move servo position to 20 degrees
    delay(500);             // Wait number of milliseconds in parentheses before continuing
        
    Servo.detach();         // Disconnect servo motor

    for (;;);               // Infinite loop used to effectively stop the progam from commanding
                                // the servo to move continuously

  }
