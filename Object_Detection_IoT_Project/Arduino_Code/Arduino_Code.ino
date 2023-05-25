// Includes the Servo library
#include <Servo.h>
#include<LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
// Defines Tirg and Echo pins of the Ultrasonic Sensor
const int trigPin = 10;
const int echoPin = 11;
// Variables for the duration and the distance
long duration;
int distance;
Servo myServo; // Creates a servo object for controlling the servo motor
void setup() {
  lcd.begin(2, 16);
  lcd.backlight();
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600);
  myServo.attach(12); // Defines on which pin is the servo motor attached
}
void loop() {
  // rotates the servo motor from 15 to 165 degrees
  for (int i = 15; i <= 165; i++) {
    myServo.write(i);
    delay(30);
    distance = calculateDistance();// Calls a function for calculating the distance measured by the Ultrasonic sensor for each degree

    Serial.print(i); 
    Serial.print(","); 
    Serial.print(distance);
    Serial.print("."); 
    
    if (distance < 40)
    {

      lcd.clear();
      lcd.setCursor(2, 0);
      lcd.print("Hello, Surya ");
      lcd.setCursor(1, 1);
      lcd.print("Distance: ");
      lcd.print(distance);
      lcd.print("cm");
      // Draws bargraph on the second line of the LCD

      lcd.setCursor(0, 1);
      delay(5);
    }
    else
    {
      lcd.clear();
      lcd.setCursor(2, 0);
      lcd.print("Hello, Surya ");
      lcd.setCursor(2, 1);
      lcd.print("Out of Range");
      delay(5);

    }
  }

  for (int i = 165; i > 15; i--) {
    myServo.write(i);
    delay(30);
    distance = calculateDistance();
    Serial.print(i);
    Serial.print(",");
    Serial.print(distance);
    Serial.print(".");

    if (distance < 40)
    {
      lcd.clear();
      lcd.setCursor(2, 0);
      lcd.print("Hello, Surya ");
      lcd.setCursor(1, 1);
      lcd.print("Distance: ");
      lcd.print(distance);
      lcd.print("cm");
      // Draws bargraph on the second line of the LCD

      lcd.setCursor(0, 1);
      delay(5);
    }
    else
    {
      lcd.clear();
      lcd.setCursor(2, 0);
      lcd.print("Hello, Surya ");
      lcd.setCursor(2, 1);
      lcd.print("Out of Range");
      delay(5);

    }
  }
}
// Function for calculating the distance measured by the Ultrasonic sensor
int calculateDistance() {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
  distance = duration * 0.034 / 2;
  return distance;
}
