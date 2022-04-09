/*#define BTN1_PIN 2
#define BTN2_PIN 3*/
/*#include <Servo.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
Servo spinArm;
int angleArm = 0;
int angleWheel = 0;
Servo spinWheel;*/
#define ButtonForward 8
#define ButtonBackward 7
#define LED 6
int lastButtonStateForward;    // the previous state of button
int currentButtonStateForward; // the current state of button
int lastButtonStateBackward;    // the previous state of button
int currentButtonStateBackward; // the current state of button

void setup()   {                
 /* pinMode(BTN1_PIN, INPUT); 
  Serial.begin(9600);*/
  pinMode(6,OUTPUT);
  pinMode(8,INPUT);
 //digitalWrite(6,LOW);
 Serial.begin(9600);
 //pmw.begin();
 //spinWheel.attach(0,480,2400);
// spinArm.attach(1,480,2400);
}

void loop() {
  lastButtonStateForward    = currentButtonStateForward;      // save the last state
  lastButtonStateBackward    = currentButtonStateBackward;      // save the last state
  currentButtonStateForward = digitalRead(ButtonForward); // read new state
  currentButtonStateBackward = digitalRead(ButtonBackward); // read new state
  if (lastButtonStateForward == HIGH && currentButtonStateForward == LOW) { //Seems to do this after the button has been released
    digitalWrite(LED,HIGH);
    Serial.println("The forward button is pressed");
 /* for (angleArm = 0; angleArm <= 180; angleArm += 1) { //This loop moves the servo 180 degrees forwards/clockwise
      spinArm.write(angleArm);
      delay(5);
    }
    for (angleWheel = 0; angleWheel <= 180; angleWheel += 1) { //This loop moves the servo 180 degrees forwards/clockwise
      spinWheel.write(angleWheel);
      delay(5);
    }*/
  }
  else if(lastButtonStateBackward == HIGH && currentButtonStateBackward == LOW) {
    digitalWrite(LED,HIGH);
    Serial.println("The backward button is pressed");
  }
  else {
    digitalWrite(6,LOW); 
}
}
