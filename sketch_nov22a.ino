#include <BluetoothSerial.h>
BluetoothSerial BT; // Initialize Bluetooth

const int trigPin = 22; // Ultrasonic Sensor Trig Pin
const int echoPin = 21; // Ultrasonic Sensor Echo Pin
long duration;
int distance;
const int thresholdDistance = 200; // 100 cm = 1 meter


void setup() {
  Serial.begin(115200);
  BT.begin("RedmiNote9"); // Bluetooth Name
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.println("Bluetooth Device Ready to Pair");
}

void loop() {
  // Measure distance
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2; // Calculate distance in cm
  
  if (distance < thresholdDistance && distance > 0) {
    // Obstacle detected
    String message = "Obstacle detected at " + String(distance) + " cm!";
    BT.println(message); // Send Bluetooth message
    Serial.println(message);
    delay(5000); // Small delay to prevent spamming
  }
}
