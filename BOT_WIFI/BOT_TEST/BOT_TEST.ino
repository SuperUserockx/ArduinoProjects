#include <SoftwareSerial.h>
#include <AFMotor.h>
const int i1=2;
const int i2=13;

AF_DCMotor motor1(1, MOTOR12_64KHZ); // create motor #2, 64KHz pwm
AF_DCMotor motor2(2, MOTOR12_64KHZ);
AF_DCMotor motor3(3, MOTOR12_64KHZ);
AF_DCMotor motor4(4, MOTOR12_64KHZ);

int c=0;
void setup()
{
  //set pin modes
  motor1.setSpeed(255);
  motor2.setSpeed(255);
  motor3.setSpeed(255);
  motor4.setSpeed(255);
  pinMode(i1,INPUT);
  pinMode(i2,INPUT);
  
  //start communication
 
  
}
int a=0;
  int b=0;
void loop()
{
 
  a=digitalRead(i1);
  b=digitalRead(i2);
  /*
//STATE 5: stop
  if (analogRead(A0)==0) {
    motor1.run(RELEASE);
    motor2.run(RELEASE);

  }*/
  //STATE 1: move forward
  if (a == LOW && b==LOW) {
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    motor3.run(FORWARD);
    motor4.run(FORWARD);
    
  }
  //STATE 2: move backward
  else if (a==HIGH&&b==HIGH) {
    motor1.run(RELEASE);
    motor2.run(RELEASE);
    motor3.run(RELEASE);
    motor4.run(RELEASE);
    delay(250);
    motor1.run(BACKWARD);
    motor2.run(BACKWARD);
    motor3.run(BACKWARD);
    motor4.run(BACKWARD);

  }
  //STATE 3: move right
 else if (a==HIGH&&b==LOW) {
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    motor3.run(RELEASE);
    motor4.run(RELEASE);

  }
  //STATE 4: move left
  else if (a==LOW&&b==HIGH) {

    motor1.run(RELEASE);
    motor2.run(RELEASE);
    motor3.run(FORWARD);
    motor4.run(FORWARD);
  }
  



}

