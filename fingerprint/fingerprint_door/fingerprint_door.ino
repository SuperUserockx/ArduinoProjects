#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3);
int led=7;
int led2=8;
int getFingerprintIDez();
Servo servo_test;
int angle=30;
int xd=0;
// pin #2 is IN from sensor (yellow wire)
// pin #3 is OUT from arduino  (WHITE wire)
SoftwareSerial mySerial(2, 3);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

// On Leonardo/Micro or others with hardware serial, use those! #0 is green wire, #1 is white
//Adafruit_Fingerprint finger = Adafruit_Fingerprint(&Serial1);

void setup()  
{ pinMode(led, OUTPUT);
pinMode(led2, OUTPUT);
digitalWrite(led, LOW);
digitalWrite(led2, LOW);
  while (!Serial);  // For Yun/Leo/Micro/Zero/...
  lcd.begin(16,2);
  lcd.clear();
  lcd.setCursor(0,0);
  Serial.begin(9600);
  Serial.println("finger detect test");
  lcd.print("  Fingureprint");
  lcd.setCursor(0,1);
  lcd.print("     Sensor");
  // set the data rate for the sensor serial port
  finger.begin(57600);
  servo_test.attach(4);
  servo_test.write(angle);
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
    lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("      Found");
  lcd.setCursor(0,1);
  lcd.print("     Sensor");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("     Sensor");
  lcd.setCursor(0,1);
  lcd.print("    Not Found");
    while (1);
  }
  Serial.println("Waiting for valid finger...");
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("    Waiting");
  lcd.setCursor(0,1);
  lcd.print("    to Scan");
}

void loop()                     // run over and over again
{
  getFingerprintIDez();
  delay(50);            //don't ned to run this at full speed.
}

uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      xd=1;
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("No finger detected");
      xd=1;
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      xd=1;
      return p;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      xd=1;
      return p;
    default:
      Serial.println("Unknown error");
      xd=1;
      return p;
  }

  // OK success!

  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      xd=1;
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      xd=1;
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      xd=1;
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      xd=1;
      return p;
    default:
      Serial.println("Unknown error");
      xd=1;
      return p;
  }
  
  // OK converted!
  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_OK) {
    Serial.println("Found a print match!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    xd=1;
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    xd=1;
    Serial.println("Did not find a match");
    return p;
  } else {
    Serial.println("Unknown error");
    xd=1;
    return p;
  }   
  
  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence); 
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Found ID #");
  lcd.print(finger.fingerID);
  //delay(1000);
}

// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;
  
  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Found ID #");
  lcd.print(finger.fingerID);
  delay(100);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("OPENING GATE");
  digitalWrite(led, HIGH);
  for(angle = 30; angle <=125;angle +=1)
  {
      servo_test.write(angle);
      delay(20);
  }
  delay(500);
  digitalWrite(led, LOW);
  digitalWrite(led2, HIGH);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("CLOSING GATE");
  for(angle = 125;angle>=30;angle -=1)
  {
    servo_test.write(angle);
    delay(20);
  }
  digitalWrite(led2, LOW);
  if(xd==1)
  {
    lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Intruder");
  delay(1000);
  }
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("    Waiting");
  lcd.setCursor(0,1);
  lcd.print("    to Scan");
  
  return finger.fingerID; 
}
