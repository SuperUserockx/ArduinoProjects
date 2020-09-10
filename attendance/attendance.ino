#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
int pinaq=0;
int gurpreet=0;
int rajat = 0;
int days=0;
int daybutton=8;
int monthbutton=9;
float attendance;

LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
int getFingerprintIDez();

// pin #2 is IN from sensor (GREEN wire)
// pin #3 is OUT from arduino  (WHITE wire)
SoftwareSerial mySerial(2, 3);
SoftwareSerial mySerial2(4, 5);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

// On Leonardo/Micro or others with hardware serial, use those! #0 is green wire, #1 is white
//Adafruit_Fingerprint finger = Adafruit_Fingerprint(&Serial1);

void setup()  
{
  digitalWrite(daybutton,HIGH);
  digitalWrite(monthbutton,HIGH);
  
  days++;
pinMode(daybutton, INPUT);
pinMode(monthbutton, INPUT);
  while (!Serial);  // For Yun/Leo/Micro/Zero/...
  mySerial2.begin(9600); 
  Serial.begin(9600);
  Serial.println("finger detect test");
  lcd.begin(20,4);
lcd.clear();
  // set the data rate for the sensor serial port
  finger.begin(57600);
  
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
    lcd.clear();
    lcd.setCursor(0,0);
  lcd.print("Fingureprint Sensor Detected");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    lcd.clear();
    lcd.setCursor(0,0);
  lcd.print("Fingureprint Sensor NOT Detected");
  
    while (1);
  }
  Serial.println("Waiting for valid finger...");
  lcd.clear();
    lcd.setCursor(0,0);
  lcd.print("   Waiting to scan");
  
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
      
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("No finger detected");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      return p;
    default:
      Serial.println("Unknown error");
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
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }
  
  // OK converted!
  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_OK) {
    Serial.println("Found a print match!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    Serial.println("Did not find a match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }   
  
  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence); 
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
  Serial.print("Welcome ");
  if(finger.fingerID==0)
  {
    Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
  lcd.clear();
    lcd.setCursor(0,0);
  lcd.print("Welcome Pinaq Sharma");
pinaq++;  }
  if(finger.fingerID==1)
  {
    Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
  lcd.clear();
    lcd.setCursor(0,0);
  lcd.print("Welcome Pinaq Sharma");
pinaq++;  }
  if(finger.fingerID==2)
  {
    Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
  lcd.clear();
    lcd.setCursor(0,0);
  lcd.print("Welcome Pinaq Sharma");
pinaq++;  }
  if(finger.fingerID==3)
  {
    Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
  lcd.clear();
    lcd.setCursor(0,0);
  lcd.print("Welcome Pinaq Sharma");
pinaq++; }
  if(finger.fingerID==4)
  {
    Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
  lcd.clear();
    lcd.setCursor(0,0);
  lcd.print("Welcome Pinaq Sharma");
pinaq++;  }
  
if(finger.fingerID==5)
  {
    Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
  lcd.clear();
    lcd.setCursor(0,0);
  lcd.print("Welcome Gurpreet");
  gurpreet++;}
if(finger.fingerID==6)
  {
    Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
  lcd.clear();
    lcd.setCursor(0,0);
  lcd.print("Welcome Gurpreet");
  gurpreet++;}
if(finger.fingerID==7)
  {
    Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
  lcd.clear();
    lcd.setCursor(0,0);
  lcd.print("Welcome Gurpreet");
  gurpreet++;  }
if(finger.fingerID==8)
  {
    Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
  lcd.clear();
    lcd.setCursor(0,0);
  lcd.print("Welcome Gurpreet");
gurpreet++;  }
if(finger.fingerID==9)
  {
    Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
  lcd.clear();
    lcd.setCursor(0,0);
  lcd.print("Welcome Gurpreet");

gurpreet++;  }
  
if(finger.fingerID==10)
  {
    Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
  lcd.clear();
    lcd.setCursor(0,0);
  lcd.print("Welcome Rajat");
  rajat++;}
  
if(finger.fingerID==11)
  {
    Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
  lcd.clear();
    lcd.setCursor(0,0);
  lcd.print("Welcome Rajat");
  
  rajat++;}
  
if(finger.fingerID==12)
  {
    Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
  lcd.clear();
    lcd.setCursor(0,0);
  lcd.print("Welcome Rajat");
  rajat++;}
  
if(finger.fingerID==13)
  {
    Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
  lcd.clear();
    lcd.setCursor(0,0);
  lcd.print("Welcome Rajat");
  
rajat++;}
  
if(finger.fingerID==14)
  {
    Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
  lcd.clear();
    lcd.setCursor(0,0);
  lcd.print("Welcome Rajat");
  rajat++;
  
  }
  delay(3000);

  lcd.clear();
    lcd.setCursor(0,0);
  lcd.print("  Waiting to scan");
  if (daybutton==LOW)
   { days++;
    delay(200);
   }
  if(monthbutton==LOW)
  {
    delay(200);
      attendance=(pinaq/days)*100;
      Serial.print(attendance);
     if(attendance<75)
     {
        mySerial2.println("AT+CMGF=1");    //To send SMS in Text Mode
  delay(1000);
  mySerial2.println("AT+CMGS=\"+918219436167\"\r"); //Change to destination phone number 
  delay(1000);
  //mySerial2.println("ID - ");
  mySerial2.println("ATTENDANCE IS SHORT");//the content of the message
  //mySerial2.println(finger.fingerID);//the content of the message
  Serial.println("pinaq");
  delay(200);
  mySerial2.println((char)26); //the stopping character Ctrl+Z

     } attendance=gurpreet/days;
     if(attendance<75)
     {
        mySerial2.println("AT+CMGF=1");    //To send SMS in Text Mode
  delay(1000);
  mySerial2.println("AT+CMGS=\"+919569159505\"\r"); //Change to destination phone number 
  delay(1000);
  //mySerial2.println("ID - ");
  mySerial2.println("gurpreet");//the content of the message
  //mySerial2.println(finger.fingerID);//the content of the message
  delay(200);
  mySerial2.println((char)26); //the stopping character Ctrl+Z

     }
     attendance=rajat/days;
     if(attendance<75)
     {
        mySerial2.println("AT+CMGF=1");    //To send SMS in Text Mode
  delay(1000);
  mySerial2.println("AT+CMGS=\"+919569159505\"\r"); //Change to destination phone number 
  delay(1000);
  //mySerial2.println("ID - ");
  mySerial2.println("ATTENDANCE IS SHORT");//the content of the message
  //mySerial2.println(finger.fingerID);//the content of the message
  mySerial2.println("rajat");
  delay(200);
  mySerial2.println((char)26); //the stopping character Ctrl+Z

     }
  }
  return finger.fingerID; 
  
}


