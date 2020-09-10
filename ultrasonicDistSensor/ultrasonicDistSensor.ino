#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const int trigPin = 7;
const int echoPin = 8;
const int buzzer = 9;
int light_1 = 13;
/****************************************
 * This Initialises The pins 12,11,5,4,3 and 2 for data transmission to the LCD diaplay.
 * pin 7 and 8 are used to trigger and read the time difference from the ultrasonic distance module.
 * pin 9 is used to control the buzzer.
 * pin 13 in used to controll the onboard led
 ****************************************/
void setup() 
{
  Serial.begin(9600);         //Set the baud rate of the serial port
  lcd.begin(16, 2);           //this is used to onen a 16bit channel to the lcd display.
  pinMode(buzzer, OUTPUT);
}
struct dist
{
  long duration, inches;
  double miles;
  public:
  long cm;
  void sensor();
  long microsecondstocentimeters(long);
  long microsecondstoinches(long);
  void serialprint();
  void lcdprint();
  void error();
};
/*******************************
 * This Structure defination decleres all the required variables and functions
 ***********************************/
void dist::sensor()
{
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  inches = dist::microsecondstoinches(duration);
  cm = dist::microsecondstocentimeters(duration);
  miles=cm/100;
  miles=miles*0.000621;
    }
/***********************************************
 * function void dist::sensor() reads the time difference in the trig and echo signal and calls
 * dist::microsecondstoinches    and
 * dist::microsecondstocentimeters
 * to calculate distance.
 **********************************************/
long dist::microsecondstoinches(long microseconds)
{
  return microseconds / 74 / 2;
}

/*
 *  there are
  // 73.746 microseconds per inch (i.e. sound travels at 340 m/s = 340*100/(2.54) in/s   
 * 
 */
long dist::microsecondstocentimeters(long microseconds)
{
  return microseconds /29 / 2;
}
/**************************************
 * The speed of sound is 340 m/s or 29 microseconds per centimeter.
 * The ping travels out and back, so to find the distance of the
 * object we take half of the distance travelled.
 ***************************************/
void dist::serialprint()
{
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  
  Serial.println();
}
/***************************************
 * This function sends the calculated distance to the serial communication
 ********************************************/
void dist::lcdprint()
{
 lcd.clear();
  int inc[4],cem[4];
  int temp;
  int i;
  for(i=0;i<=3;i++)
  {
    inc[i]=48;
    cem[i]=48;
  }
  temp=inches;
  inc[3]+=temp%10;
  temp=temp/10;
  inc[2]+=temp%10;
  temp=temp/10;
  inc[1]+=temp%10;  
  temp=temp/10;
  inc[0]+=temp;
  temp=cm;
  cem[3]+=temp%10;
  temp=temp/10;
  cem[2]+=temp%10;
  temp=temp/10;
  cem[1]+=temp%10;  
  temp=temp/10;
  cem[0]+=temp;
  lcd.write("    ");
  lcd.write(inc[0]);
  lcd.write(inc[1]);
  lcd.write(inc[2]);
  lcd.write(inc[3]);
  lcd.write("  Inches ");
  lcd.write("     ");
  lcd.write(cem[0]);
  lcd.write(cem[1]);
  lcd.write(cem[2]);
  lcd.write(cem[3]);
  lcd.write(" CentiMeters  "); 
}
/************************************
 * The lcd display is sent with the ascii code of each caracter to be displayed.
 ************************************/
void dist::error()
{
  lcd.write("Obstruction  Detcted");
  tone(buzzer, 200000);
  delay(500);
  noTone(buzzer);
  delay(500);
  digitalWrite(light_1,HIGH);
  delay(50);  
  digitalWrite(light_1,LOW);
  delay(50);
  Serial.println("Obstruction too close");
}
/*****************************
 * This send out the warning signal when the calculated distance in lenn than 10 cm.
 ****************************/
void loop()
{
  dist obj;
  obj.sensor();
  obj.serialprint();
  obj.lcdprint();
  if(obj.cm<20)
    obj.error();
  delay(100);
}

