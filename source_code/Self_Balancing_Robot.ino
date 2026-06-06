#include <Wire.h>
#include <MPU6050.h>
#include <math.h>

MPU6050 mpu;

/* Motor Pins */
#define IN1 8
#define IN2 9
#define IN3 10
#define IN4 11
#define ENA 5
#define ENB 6

/* PID Variables */
float setPoint = 0.0;
float Kp = 25.0;
float Ki = 0.0;
float Kd = 0.8;

float error = 0;
float previousError = 0;
float integral = 0;
float angle = 0;

/* Function Prototypes */
void balanceMotor(int speed);

void setup()
{
    Serial.begin(9600);

    Wire.begin();
    mpu.initialize();

    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);

    pinMode(ENA, OUTPUT);
    pinMode(ENB, OUTPUT);

    Serial.println("Self Balancing Robot Started");
}

void loop()
{
    int16_t ax, ay, az;
    int motorSpeed;

    /* Read MPU6050 Data */
    mpu.getAcceleration(&ax, &ay, &az);

    /* Calculate Tilt Angle */
    angle = atan2((float)ay, (float)az) * 180.0 / PI;

    /* PID Controller */
    error = angle - setPoint;

    integral = integral + error;

    float derivative = error - previousError;

    motorSpeed = (int)(
        (Kp * error) +
        (Ki * integral) +
        (Kd * derivative));

    /* Limit PWM */
    if (motorSpeed > 255)
        motorSpeed = 255;

    if (motorSpeed < -255)
        motorSpeed = -255;

    balanceMotor(motorSpeed);

    previousError = error;

    delay(10);
}

void balanceMotor(int speed)
{
    if (speed > 0)
    {
        analogWrite(ENA, speed);
        analogWrite(ENB, speed);

        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);

        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
    }
    else
    {
        speed = abs(speed);

        analogWrite(ENA, speed);
        analogWrite(ENB, speed);

        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);

        digitalWrite(IN3, LOW);
        digitalWrite(IN4, HIGH);
    }
}
