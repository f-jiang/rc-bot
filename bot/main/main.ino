#define M_L_F 5 // IN1 Blue
#define M_L_R 4 // IN2 Green
#define M_R_F 6 // IN3 Yellow
#define M_R_R 7 // IN4 Orange
#define SERVO_OUT 9 // Servo Motor Output

#define echoPin 2 // Echo Pin
#define trigPin 3 // Trigger Pin
#define LEDPin 13 // Onboard LED

#include <Servo.h>

enum DriveState { REV, OFF, FWD };

Servo myservo;  // create servo object to control a servo
int pos = 0;    // variable to store the servo position

int maximumRange = 200; // Maximum range needed
int minimumRange = 0; // Minimum range needed
long distance; // Duration used to calculate distance

void setup() {
    Serial.begin (9600);

    // initialize ultrasonic sensor + servo mount
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(LEDPin, OUTPUT); // Use LED indicator (if required)
    myservo.attach(9);  // attaches the servo on pin 9 to the servo object
    myservo.write(90);

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

long get_dist() {
    long duration;
    /* The following trigPin/echoPin cycle is used to determine the
    distance of the nearest object by bouncing soundwaves off of it. */ 
    digitalWrite(trigPin, LOW); 
    delayMicroseconds(2); 

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10); 

    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);

    //Calculate the distance (in cm) based on the speed of sound.
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

void servo_write(int angle) {
    myservo.write(angle + 90);
}

void loop() {
    distance = get_dist();

    if (distance >= maximumRange || distance <= minimumRange) {
        /* Send a negative number to computer and Turn LED ON 
        to indicate "out of range" */
        Serial.println("-1");
        digitalWrite(LEDPin, HIGH); 
    } else {
        /* Send the distance to the computer using Serial protocol, and
        turn LED OFF to indicate successful reading. */
        Serial.println(distance);
        digitalWrite(LEDPin, LOW); 
    }

    delay(50);

    servo_write(0);
}


