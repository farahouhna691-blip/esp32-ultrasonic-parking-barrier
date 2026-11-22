# Automated Parking Barrier System (ESP32 & Ultrasonic Sensor)

An embedded systems mini-project implementing an automated parking barrier using an ESP32 microcontroller, an HC-SR04 ultrasonic distance sensor, an SG90 servo motor, and an LED status indicator.

> **Note:** This repository provides a clean reference firmware implementation and documentation based on a hardware mini-project developed for the *Programmation Embarquée* course (SEIT engineering program).

## Overview
The system continuously measures distance using an ultrasonic sensor (`HC-SR04`). When an approaching object or vehicle is detected within a set threshold (`30 cm`), the ESP32 activates the LED indicator, rotates the servo motor (`0°` to `90°`) to raise the barrier, keeps it open for a configurable duration (`5 s`) using non-blocking `millis()` timing, and then closes the barrier (`90°` to `0°`).

## Hardware Components
- **Microcontroller:** ESP32 (ESP-WROOM-32 / DevKit)
- **Distance Sensor:** HC-SR04 Ultrasonic Sensor
- **Actuator:** SG90 Servo Motor
- **Indicator:** LED + current-limiting resistor
- **Prototyping:** Breadboard and jumper wires

## Key Engineering Highlights
- Non-blocking timing logic using `millis()` instead of blocking delays during barrier operation
- Iterative hardware validation moving from a PIR motion sensor to ultrasonic distance measurement for more reliable presence/distance detection
- Serial debugging output at `115200` baud for monitoring distance readings and state transitions

## File Structure
- `parking_barrier.ino` — ESP32 firmware for distance sensing, servo control, and LED signaling
- `README.md` — Project overview and hardware/software notes
