#include <XBOXUSB.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>
int left_trig,right_trig,stick_p,stick_n,vel;
int left_f=2;
int left_r=4;
int right_f=6;
int right_r=7;
int l_speed=3;
int r_speed=5;
USB Usb;
XBOXUSB Xbox(&Usb);

void setup() {
  pinMode(left_f, OUTPUT);
  pinMode(left_r, OUTPUT);
  pinMode(right_f, OUTPUT);
  pinMode(right_r, OUTPUT);
  pinMode(l_speed, OUTPUT);
  pinMode(r_speed, OUTPUT);
  Serial.begin(115200);
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print(F("\r\nXBOX USB Library Started"));
}
void motion(int l_trig,int r_trig,int stick_pl,int stick_ne)
{
  if(l_trig>0 && r_trig==0 && stick_ne<0)
  {
    vel=stick_ne*-1;
    if (vel>160)
      vel=160;
    vel=255-vel;
    digitalWrite(left_f, HIGH);
  digitalWrite(left_r, LOW);  
  digitalWrite(right_r, HIGH);
  digitalWrite(right_f, LOW); 
  analogWrite(l_speed, vel);
    analogWrite(r_speed, l_trig);
  }
  if(l_trig>0 && r_trig==0 && stick_pl<0)
  {
    vel=stick_pl;
    if (vel>160)
      vel=160;
    vel=255-vel;
    digitalWrite(left_f, HIGH);
  digitalWrite(left_r, LOW);  
  digitalWrite(right_r, HIGH);
  digitalWrite(right_f, LOW); 
  analogWrite(l_speed, vel);
    analogWrite(r_speed, l_trig);
  }
  if(l_trig==0 && r_trig==0 && stick_pl>0)
  {vel=stick_pl;
    digitalWrite(left_f, LOW);
  digitalWrite(left_r, HIGH);  
  digitalWrite(right_r, LOW);
  digitalWrite(right_f, HIGH); 
  analogWrite(l_speed, vel);
    analogWrite(r_speed, vel);
  }
  if(l_trig==0 && r_trig==0 && stick_ne<0)
  {
    vel=stick_ne*-1;
    digitalWrite(left_f, HIGH);
  digitalWrite(left_r, LOW);  
  digitalWrite(right_r, HIGH);
  digitalWrite(right_f, LOW); 
  analogWrite(l_speed, vel);
    analogWrite(r_speed, vel);
  }
if(l_trig>0 && r_trig==0 && stick_ne==0 && stick_pl==0)
  {
    vel=l_trig;
    digitalWrite(left_f, HIGH);
  digitalWrite(left_r, LOW);  
  digitalWrite(right_r, LOW);
  digitalWrite(right_f, HIGH); 
  analogWrite(l_speed, vel);
    analogWrite(r_speed, vel);
  }
  if(l_trig==0 && r_trig>0 && stick_ne==0 && stick_pl==0)
  {
    vel=r_trig;
    digitalWrite(left_f, LOW);
  digitalWrite(left_r, HIGH);  
  digitalWrite(right_r, HIGH);
  digitalWrite(right_f, LOW); 
  analogWrite(l_speed, vel);
    analogWrite(r_speed, vel);
  }

if(l_trig==0 && r_trig==0 && stick_ne==0 && stick_pl==0)
  {
    vel=0;
    digitalWrite(left_f, LOW);
  digitalWrite(left_r, LOW);  
  digitalWrite(right_r, LOW);
  digitalWrite(right_f, LOW); 
  analogWrite(l_speed, vel);
    analogWrite(r_speed, vel);
  }



  
}
void loop() {
  left_trig=0;
  right_trig=0;
  stick_p=0;
  stick_n=0;
  Usb.Task();
  if (Xbox.Xbox360Connected) {
    if (Xbox.getButtonPress(L2) || Xbox.getButtonPress(R2)) {
    // Serial.print("L2: ");
      left_trig=Xbox.getButtonPress(L2);
      //Serial.print(Xbox.getButtonPress(L2));
      //Serial.print("\tR2: ");
      //Serial.println(Xbox.getButtonPress(R2));
      right_trig=Xbox.getButtonPress(R2);
      Xbox.setRumbleOn(Xbox.getButtonPress(L2), Xbox.getButtonPress(R2));
    } else
      Xbox.setRumbleOn(0, 0);

    if (Xbox.getAnalogHat(RightHatX) > 7500 || Xbox.getAnalogHat(RightHatX) < -7500) {
           if (Xbox.getAnalogHat(RightHatX) > 7500) {
        //Serial.print(F("RightHatX: "));
        //Serial.print((Xbox.getAnalogHat(RightHatX)/100)-72);
        //Serial.print("\t");
        stick_p=((Xbox.getAnalogHat(RightHatX)/100)-72);
      }
      if(Xbox.getAnalogHat(RightHatX) < -7500){
        //Serial.print(F("RightHatX: "));
        //Serial.print((Xbox.getAnalogHat(RightHatX)/100)+72);
        //Serial.print("\t");
        stick_n=((Xbox.getAnalogHat(RightHatX)/100)+72);
      }
     
      //Serial.println();
    }

  }
  Serial.print("left_trig : " );
  Serial.print(left_trig);
    Serial.print("right_trig : " );
  Serial.print(right_trig);
    Serial.print("stick_p : " );
  Serial.print(stick_p);
    Serial.print("stick_n : " );
  Serial.print(stick_n);
  Serial.println();
  motion(left_trig,right_trig,stick_p,stick_n);
}
