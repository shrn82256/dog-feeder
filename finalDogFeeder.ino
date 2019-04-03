#include <HX711.h>
#include <Servo.h>

Servo storageServo; // create servo object to control a servo
// twelve servo objects can be created on most boards


int storageServoPin = 9;
int storageServoPos = 0; // variable to store the servo storageServoPosition
int storageStartAngle = 0;
int storageHaltAngle = 90;

/*
 Setup your scale and start the sketch WITHOUT a weight on the scale
 Once readings are displayed place the weight on the scale
 Press +/- or a/z to adjust the calibration_factor until the output readings match the known weight
 Arduino pin 2 -> HX711 CLK
 Arduino pin 3 -> HX711 DOUT
 Arduino pin 5V -> HX711 VCC
 Arduino pin GND -> HX711 GND 
*/

// 1kg 654
// 2kg 1648
// 178g 146
// 181g 171
// 155g 147
// 1kg 178g 802
// 1kg 181g 178g 975
// 1kg 181g 178g 155g 1124
// 181g 178g 155g 468
// 1kg 178g 155g 951
// 178g 155g 295

int A=6;
int B=7;
int servoPin=9;


int flag = 0;


HX711 scale(3, 2);

float calibration_factor = -500; // this calibration factor is adjusted according to my load cell
float units;
float ounces;

void setup()
{
  storageServo.attach(storageServoPin); // attaches the servo on pin 9 to the servo object
  // garbageServo.attach(garbageServoPin); // attaches the servo on pin 9 to the servo object
  Serial.begin(9600);
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  Serial.println("HX711 calibration sketch");
  Serial.println("Remove all weight from scale");
  Serial.println("After readings begin, place known weight on scale");
  Serial.println("Press + or a to increase calibration factor");
  Serial.println("Press - or z to decrease calibration factor");

  scale.set_scale();
  scale.tare(); //Reset the scale to 0

  long zero_factor = scale.read_average(); //Get a baseline reading
  Serial.print("Zero factor: ");           //This can be used to remove the need to tare the scale. Useful in permanent scale projects.
  Serial.println(zero_factor);
}

void loop()
{
  scale.set_scale(calibration_factor); //Adjust to this calibration factor

  units = scale.get_units(5), 10;
  if (units < 0)
  {
    units = 0.00;
  }
  ounces = units * 0.035274;
  Serial.print("Reading: ");
  Serial.print(units);
  Serial.print(" grams");
  Serial.print(" calibration_factor: ");
  Serial.print(calibration_factor);
  Serial.println();

  if(flag == 1 && units < 100)
  {
    flag = 0;
  }

  
  if(!flag){
    if (units>100)
    {
      flag = 1; 
      digitalWrite(A, LOW);
      digitalWrite(B, HIGH);
      Serial.print("\nThe motor is running\n");
  
    for (storageServoPos = storageHaltAngle; storageServoPos >= storageStartAngle; storageServoPos--)
    {                                      // goes from 45 degrees to 0 degrees
      storageServo.write(storageServoPos); // tell servo to go to storageServoPosition in variable 'storageServoPos'
      delay(15);                           // waits 15ms for the servo to reach the storageServoPosition
    }
  
     delay(1000);
    
    for (storageServoPos = storageStartAngle; storageServoPos < storageHaltAngle; storageServoPos++)
    { // goes from 0 degrees to 45 degrees
      // in steps of 1 degree
      storageServo.write(storageServoPos); // tell servo to go to storageServoPosition in variable 'storageServoPos'
      delay(15);                           // waits 15ms for the servo to reach the storageServoPosition
    }
  
    delay(5000);
    digitalWrite(A, LOW);
    digitalWrite(B, LOW);
    
    }

  }

  // exit(0);
  if (Serial.available())
  {
    char temp = Serial.read();
    if (temp == '+' || temp == 'a')
      calibration_factor += 1;
    else if (temp == '-' || temp == 'z')
      calibration_factor -= 1;
  }

  delay(2000);

  // delay(1000);
}
