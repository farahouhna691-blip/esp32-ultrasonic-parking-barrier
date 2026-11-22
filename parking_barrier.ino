#include <ESP32Servo.h>

// Pin definitions (adjust to match your exact ESP32 wiring)
const int TRIG_PIN = 5;
const int ECHO_PIN = 18;
const int SERVO_PIN = 19;
const int LED_PIN = 26;

// Threshold & timing parameters
const float DISTANCE_THRESHOLD_CM = 30.0;
const int CLOSED_ANGLE = 0;
const int OPEN_ANGLE = 90;
const unsigned long OPEN_DURATION_MS = 5000;
const unsigned long MEASURE_INTERVAL_MS = 100;

Servo barrierServo;

bool isBarrierOpen = false;
unsigned long barrierOpenTimestamp = 0;
unsigned long lastMeasureTimestamp = 0;

float readDistanceCm() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long durationUs = pulseIn(ECHO_PIN, HIGH, 30000); // 30 ms timeout (~5 m max)
  if (durationUs == 0) {
    return -1.0; // No echo received
  }
  return (durationUs * 0.0343f) / 2.0f;
}

void openBarrier() {
  if (!isBarrierOpen) {
    barrierServo.write(OPEN_ANGLE);
    digitalWrite(LED_PIN, HIGH);
    isBarrierOpen = true;
    Serial.println("Barrier OPENED");
  }
  barrierOpenTimestamp = millis();
}

void closeBarrier() {
  barrierServo.write(CLOSED_ANGLE);
  digitalWrite(LED_PIN, LOW);
  isBarrierOpen = false;
  Serial.println("Barrier CLOSED");
}

void setup() {
  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  barrierServo.attach(SERVO_PIN);
  barrierServo.write(CLOSED_ANGLE);

  Serial.println("Automated Parking Barrier System initialized.");
}

void loop() {
  unsigned long now = millis();

  if (now - lastMeasureTimestamp >= MEASURE_INTERVAL_MS) {
    lastMeasureTimestamp = now;
    float distance = readDistanceCm();

    if (distance > 0) {
      Serial.print("Distance: ");
      Serial.print(distance, 1);
      Serial.println(" cm");

      if (distance <= DISTANCE_THRESHOLD_CM) {
        openBarrier();
      }
    }
  }

  if (isBarrierOpen && (now - barrierOpenTimestamp >= OPEN_DURATION_MS)) {
    closeBarrier();
  }
}
