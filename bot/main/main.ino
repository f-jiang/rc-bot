#define M_L_F 5 // IN1
#define M_L_R 4 // IN2
#define M_R_F 6 // IN3
#define M_R_R 7 // IN4
#define SERVO 9

#define ULTRA_ECHO 2
#define ULTRA_TRIG 3
#define LED 13

#include <Servo.h>

enum DriveState { REV, OFF, FWD };

Servo ultraServo;

int maximumRange = 200;
int minimumRange = 0;
long distance;

void setup() {
    Serial.begin (9600);

    // initialize ultrasonic sensor + servo mount
    pinMode(ULTRA_TRIG, OUTPUT);
    pinMode(ULTRA_ECHO, INPUT);
    pinMode(LED, OUTPUT);
    ultraServo.attach(9);
    ultraServo.write(90);

    // Initialize Motor Pins
    pinMode(M_L_F, OUTPUT);
    pinMode(M_L_R, OUTPUT);
    pinMode(M_R_F, OUTPUT);
    pinMode(M_R_R, OUTPUT);

    digitalWrite(M_L_F, LOW);
    digitalWrite(M_L_R, LOW);
    digitalWrite(M_R_F, LOW);
    digitalWrite(M_R_R, LOW);

    delay(1000);
}

long getDist() {
    long duration;
    digitalWrite(ULTRA_TRIG, LOW); 
    delayMicroseconds(2); 

    digitalWrite(ULTRA_TRIG, HIGH);
    delayMicroseconds(10); 

    digitalWrite(ULTRA_TRIG, LOW);
    duration = pulseIn(ULTRA_ECHO, HIGH);

    // dist in cm
    return duration / 58.2;
}

void drive(DriveState left, DriveState right) {
    digitalWrite(M_L_F,LOW);
    digitalWrite(M_L_R,LOW);
    digitalWrite(M_R_F,LOW);
    digitalWrite(M_R_R,LOW);

    delay(15);

    if (left == FWD) {
        digitalWrite(M_L_F, HIGH);
    } else if (left == REV) {
        digitalWrite(M_L_R, HIGH);
    }

    if (right == FWD) {
        digitalWrite(M_R_F, HIGH);
    } else if (right == REV) {
        digitalWrite(M_R_R, HIGH);
    }
}

void servoWrite(int angle) {
    ultraServo.write(angle + 90);
}

void loop() {
    distance = getDist();

    if (distance >= maximumRange || distance <= minimumRange) {
        Serial.println("-1");
        digitalWrite(LED, HIGH); 
    } else {
        Serial.println(distance);
        digitalWrite(LED, LOW); 
    }

    delay(50);

    servoWrite(0);

    drive(FWD, FWD);
    delay(1000);
    drive(OFF, OFF);
    delay(1000);
    drive(REV, REV);
    delay(1000);
    drive(OFF, OFF);
    delay(2000);
}


