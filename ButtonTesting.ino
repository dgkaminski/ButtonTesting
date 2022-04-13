#include <Servo.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
Servo spinArm;
int angleArm = 0;
int angleWheel = 0;
Servo spinWheel;
#define ButtonForward 8
#define ButtonBackward 7
#define LED 6
#define SERVOMIN  75 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  435 // This is the 'maximum' pulse length count (out of 4096) //BOTH ABOVE FOR ARM
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates
#define USMIN  2200 // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define USMAX  2400 // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
int lastButtonStateForward;    // the previous state of button
int currentButtonStateForward; // the current state of button
int lastButtonStateBackward;    // the previous state of button
int currentButtonStateBackward; // the current state of button
int lastDirection; //The last direction that the arm was in, if it's at 1 was at right of book

void setup()   {
  pinMode(6, OUTPUT);
  pinMode(8, INPUT);
  pwm.begin();
  Serial.begin(9600);
  //spinArm.attach(0, 480, 2400);
  //spinWheel.attach(1, 480, 2400);
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates
  lastDirection = 0; //Set by default to be on right side of book
}

void loop() {

  lastButtonStateForward    = currentButtonStateForward;      // save the last state
  lastButtonStateBackward    = currentButtonStateBackward;      // save the last state
  currentButtonStateForward = digitalRead(ButtonForward); // read new state
  currentButtonStateBackward = digitalRead(ButtonBackward); // read new state
  if (lastButtonStateForward == HIGH && currentButtonStateForward == LOW) { //Seems to do this after the button has been released
    digitalWrite(LED, HIGH);
    Serial.println("The forward button is pressed");
    if (lastDirection == 0) {
      for (int pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++) {
        pwm.setPWM(1, 0, pulselen); //1 SHOULD BE THE PIN FOR THE ARM
      }
      lastDirection = 1;
    }
    delay(1000);
    for (int time = 1 ; time > 0; time--) {
      for (uint16_t microsec = USMAX; microsec > USMIN; microsec--) {
        pwm.writeMicroseconds(7, microsec);
        delay(25);
      }
      pwm.writeMicroseconds(7, 0);
    }
  }
  else if (lastButtonStateBackward == HIGH && currentButtonStateBackward == LOW) {
    digitalWrite(LED, HIGH);
    Serial.println("The backward button is pressed");
    if (lastDirection == 1) {
      for (int pulselen = SERVOMAX; pulselen > SERVOMIN; pulselen--) {
        pwm.setPWM(1, 0, pulselen); //1 SHOULD BE THE PIN FOR THE ARM
      }
      lastDirection = 0;
    }
    delay(1000);
    for (int time = 1 ; time > 0; time--) {
      for (uint16_t microsec = 1000; microsec > 500; microsec--) {
        pwm.writeMicroseconds(7, microsec);
        delay(25);
      }
      delay(1);
      pwm.writeMicroseconds(7, 0);
    }
  }
  else {
    digitalWrite(6, LOW);
  }
  delay (10);
}
