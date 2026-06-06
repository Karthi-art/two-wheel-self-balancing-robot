# Two-Wheel Self-Balancing Robot

## Overview
A self-balancing robot built using Arduino Uno, MPU6050 sensor, and L298N motor driver.

The robot continuously measures its tilt angle using the MPU6050 and uses a PID controller to maintain balance.

## Features
- Self balancing using PID control
- Real-time angle measurement
- DC motor control
- Arduino-based implementation

## Components
- Arduino Uno
- MPU6050
- L298N Motor Driver
- BO Motors (2)
- Wheels (2)
- Battery Pack
- Chassis

## Circuit Connections

### MPU6050
VCC -> 5V
GND -> GND
SDA -> A4
SCL -> A5

### L298N
IN1 -> D8
IN2 -> D9
IN3 -> D10
IN4 -> D11
ENA -> D5
ENB -> D6

## How It Works
1. MPU6050 measures tilt angle.
2. Arduino calculates error.
3. PID controller generates correction.
4. Motors rotate to balance the robot.

