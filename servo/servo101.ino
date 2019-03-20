#include <Servo.h>

Servo storageServo; // create servo object to control a servo
Servo garbageServo; // create servo object to control a servo
// twelve servo objects can be created on most boards

int motorPin = 3;

int storageServoPin = 7;
int storageServoPos = 0; // variable to store the servo storageServoPosition
int storageStartAngle = 10;
int storageHaltAngle = 90;

int garbageServoPin = 5;
int garbageServoPos = 0; // variable to store the servo storageServoPosition
int garbageHaltAngle = 90;

void setup()
{
  storageServo.attach(storageServoPin); // attaches the servo on pin 9 to the servo object
  // garbageServo.attach(garbageServoPin); // attaches the servo on pin 9 to the servo object
  // pinMode(motorPin, OUTPUT);
  Serial.begin(115200);
}

void loop()
{

  for (storageServoPos = storageStartAngle; storageServoPos < storageHaltAngle; storageServoPos++)
  { // goes from 0 degrees to 45 degrees
    // in steps of 1 degree
    storageServo.write(storageServoPos); // tell servo to go to storageServoPosition in variable 'storageServoPos'
    delay(15);                           // waits 15ms for the servo to reach the storageServoPosition
  }

  // digitalWrite(motorPin, HIGH);

  delay(1500);
  for (storageServoPos = storageHaltAngle; storageServoPos >= storageStartAngle; storageServoPos--)
  {                                      // goes from 45 degrees to 0 degrees
    storageServo.write(storageServoPos); // tell servo to go to storageServoPosition in variable 'storageServoPos'
    delay(15);                           // waits 15ms for the servo to reach the storageServoPosition
  }

  /* delay(1000 * 60 - 1500);
  digitalWrite(motorPin, LOW);

  delay(1000 * 60 * 5);
  for (garbageServoPos = 0; garbageServoPos <= garbageHaltAngle; garbageServoPos += 1)
  { // goes from 0 degrees to 90 degrees
    // in steps of 1 degree
    garbageServo.write(garbageServoPos); // tell servo to go to garbageServoPosition in variable 'garbageServoPos'
    delay(15);                           // waits 15ms for the servo to reach the garbageServoPosition
  }

  delay(2000);
  for (garbageServoPos = garbageHaltAngle; garbageServoPos >= 0; garbageServoPos -= 1)
  {                                      // goes from 90 degrees to 0 degrees
    garbageServo.write(garbageServoPos); // tell servo to go to garbageServoPosition in variable 'garbageServoPos'
    delay(15);                           // waits 15ms for the servo to reach the garbageServoPosition
  } */

  // exit(0);
  delay(5000);
}
