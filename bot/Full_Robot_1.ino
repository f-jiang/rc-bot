#define M_L_F 4 // IN1 Blue
#define M_L_R 5 // IN2 Green
#define M_R_F 6 // IN3 Yellow
#define M_R_R 7 // IN4 Orange
#define SERVO_OUT 9 // Servo Motor Output
#define TRIG_PIN 3 // 
#define ECHO_PIN 2 // Echo output pin
#define FWD 1
#define OFF 0
#define REV -1


#include <Servo.h>

Servo myservo;  // create servo object to control a servo
int pos = 0;    // variable to store the servo position

// Prototypes
void motor_left(int state);
void motor_right(int state);
void motor_fwd();
void motor_rev();
void motor_stop();


void setup() 
{
  Serial.begin(9600); // Serial Monitor Rate Initialization  
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object

  // Initialize Motor Pins
  pinMode(M_L_F, OUTPUT);
  pinMode(M_L_R, OUTPUT);
  pinMode(M_R_F, OUTPUT);
  pinMode(M_R_R, OUTPUT);

  digitalWrite(M_L_F, LOW);
  digitalWrite(M_L_R, LOW);
  digitalWrite(M_R_F, LOW);
  digitalWrite(M_R_R, LOW);

  // Initialize the Servo to 90 degrees (straight forward)
  myservo.write(90);

  delay(10000);
}

void loop() {
  servo_write(0);

  motor_fwd();
  delay(1000);
  motor_stop();
  delay(500);
  motor_rev();
  delay(1000);
  motor_stop(); 
  delay(3000);
}

void motor_left(int state)
{
  digitalWrite(M_L_F,LOW);
  digitalWrite(M_L_R,LOW);

  delay(15);
  
  if (state == FWD)
  {
    digitalWrite(M_L_F, HIGH);
  }
  else if (state == REV)
  {
    digitalWrite(M_L_R, HIGH);
  }
}

void motor_right(int state)
{
  digitalWrite(M_R_F,LOW);
  digitalWrite(M_R_R,LOW);

  delay(15);
  
  if (state == FWD)
  {
    digitalWrite(M_R_F, HIGH);
  }
  else if (state == REV)
  {
    digitalWrite(M_R_R, HIGH);
  }
}

void motor_fwd()
{
  motor_right(FWD);
  motor_left(FWD);  
}

void motor_rev()
{
  motor_right(REV);
  motor_left(REV);
}

void motor_stop()
{
 motor_right(OFF);
 motor_left(OFF);
}

void servo_write(int angle)
{
  myservo.write(angle + 90);
}

