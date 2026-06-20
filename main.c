#include <Servo.h>

// Define Pin Connections
const int trigPin = 9;
const int echoPin = 8;
const int servoPin = 6;

Servo gateServo; 

// Variables for distance calculation
long duration;
int distance;

void setup() {
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  gateServo.attach(servoPin);
  
  // Start with the gate closed
  gateServo.write(0); 
}

void loop() {
  // Clear the trigPin by setting it LOW
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Trigger the sensor by setting trigPin HIGH for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Read the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance in cm (Speed of sound is 340 m/s or 29 microseconds per cm)
  distance = duration * 0.034 / 2;
  
  // If a car is detected within 30 cm, open the gate
  if (distance < 30) {
    gateServo.write(90); // Rotate servo to 90 degrees to open the gate
    delay(3000);         // Wait 3 seconds for the car to pass
  }
  else {
    gateServo.write(0);  // Rotate servo to 0 degrees to close the gate
  }
  
  delay(100); // Small delay to prevent sensor reading spikes
}
