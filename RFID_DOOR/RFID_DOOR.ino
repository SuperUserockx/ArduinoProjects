#include <EEPROM.h>     // We are going to read and write PICC's UIDs from/to EEPROM
#include <SPI.h>        // RC522 Module uses SPI protocol
#include <MFRC522.h>	// Library for Mifare RC522 Devices
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address

#define COMMON_ANODE

#ifdef COMMON_ANODE
#define LED_ON LOW
#define LED_OFF HIGH
#else
#define LED_ON HIGH
#define LED_OFF LOW
#endif

#define redLed 8		// Set Led Pins
#define greenLed 7
#define blueLed 6

#define relay 4			// Set Relay Pin
#define wipeB 3			// Button pin for WipeMode

boolean match = false;          // initialize card match to false
boolean programMode = false;	// initialize programming mode to false
boolean replaceMaster = false;

int successRead;		// Variable integer to keep if we have Successful Read from Reader
const int buzzer = 5;
int intruder=0;
int restart=0;
byte storedCard[4];		// Stores an ID read from EEPROM
byte readCard[4];		// Stores scanned ID read from RFID Module
byte masterCard[4];		// Stores master card's ID read from EEPROM

/*
 * FOR LCD
   SDA - PIN A4
   SCL - PIN A5
   
 * FOR RC522->
	MOSI: Pin 11 / ICSP-4
	MISO: Pin 12 / ICSP-1
	SCK : Pin 13 / ICSP-3
	SS : Pin 10 (Configurable)
	RST : Pin 9 (Configurable)
*/

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);	// Create MFRC522 instance.

///////////////////////////////////////// Setup ///////////////////////////////////
void setup() {
  pinMode(buzzer, OUTPUT);
  //Arduino Pin Configuration
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(blueLed, OUTPUT);
  pinMode(wipeB, INPUT_PULLUP);		// Enable pin's pull up resistor
  pinMode(relay, OUTPUT);
  //Be careful how relay circuit behave on while resetting or power-cycling your Arduino
  digitalWrite(relay, HIGH);		// Make sure door is locked
  digitalWrite(redLed, LED_OFF);	// Make sure led is off
  digitalWrite(greenLed, LED_OFF);	// Make sure led is off
  digitalWrite(blueLed, LED_OFF);	// Make sure led is off
  lcd.begin(20,4);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(" Arduino RFID Based    Locking System");
  tone(buzzer, 1000);
  delay(50);
  noTone(buzzer);
  delay(50);
  tone(buzzer, 1000);
  delay(50);
  noTone(buzzer);
  delay(50);
  tone(buzzer, 1000);
  delay(50);
  noTone(buzzer);
  delay(50);
  tone(buzzer, 1000);
  delay(50);
  noTone(buzzer);
  delay(50);
  tone(buzzer, 1000);
  delay(50);
  noTone(buzzer);
  delay(50);
  tone(buzzer, 1000);
  delay(50);
  noTone(buzzer);
  delay(50);
  lcd.clear();
  lcd.setCursor(0,0);
  //Protocol Configuration
  Serial.begin(9600);	 // Initialize serial communications with PC
  SPI.begin();           // MFRC522 Hardware uses SPI protocol
  mfrc522.PCD_Init();    // Initialize MFRC522 Hardware

  //If you set Antenna Gain to Max it will increase reading distance
  mfrc522.PCD_SetAntennaGain(mfrc522.RxGain_max);

  Serial.println(F("Access Control v3.4"));   // For debugging purposes
  ShowReaderDetails();	// Show details of PCD - MFRC522 Card Reader details

  //Wipe Code if Button Pressed while setup run (powered on) it wipes EEPROM
  if (digitalRead(wipeB) == LOW) {	// when button pressed pin should get low, button connected to ground
    digitalWrite(redLed, LED_ON);	// Red Led stays on to inform user we are going to wipe
    Serial.println(F("Wipe Button Pressed"));
    lcd.print("   !!!WARNING!!!    Wipe Button Pressed");
    delay(1000);
    lcd.clear();
  lcd.setCursor(0,0);
    Serial.println(F("You have 15 seconds to Cancel"));
    Serial.println(F("This will be remove all records and cannot be undone"));
                           // Give user enough time to cancel operation
    lcd.print(" You have 15 seconds      to Cancel");
    if (digitalRead(wipeB) != LOW)
      goto abc;
    delay(1000);
    lcd.clear();
  lcd.setCursor(0,0);
    lcd.print(" You have 14 seconds      to Cancel");
    if (digitalRead(wipeB) != LOW)
      goto abc;
    delay(1000);
    lcd.clear();
  lcd.setCursor(0,0);
    lcd.print(" You have 13 seconds      to Cancel");
    if (digitalRead(wipeB) != LOW)
      goto abc;
    delay(1000);
    lcd.clear();
  lcd.setCursor(0,0);
    lcd.print(" You have 12 seconds      to Cancel");
    if (digitalRead(wipeB) != LOW)
      goto abc;
    delay(1000);
    lcd.clear();
  lcd.setCursor(0,0);
    lcd.print(" You have 11 seconds      to Cancel");
    if (digitalRead(wipeB) != LOW)
      goto abc;
    delay(1000);
    lcd.clear();
  lcd.setCursor(0,0);
    lcd.print(" You have 10 seconds      to Cancel");
    if (digitalRead(wipeB) != LOW)
      goto abc;
    delay(1000);
    lcd.clear();
  lcd.setCursor(0,0);
    lcd.print(" You have 9 seconds       to Cancel");
    if (digitalRead(wipeB) != LOW)
      goto abc;
    delay(1000);
    lcd.clear();
  lcd.setCursor(0,0);
    lcd.print(" You have 8 seconds       to Cancel");
    if (digitalRead(wipeB) != LOW)
      goto abc;
    delay(1000);
    lcd.clear();
  lcd.setCursor(0,0);
    lcd.print(" You have 7 seconds       to Cancel");
    if (digitalRead(wipeB) != LOW)
      goto abc;
    delay(1000);
    lcd.clear();
  lcd.setCursor(0,0);
    lcd.print(" You have 6 seconds       to Cancel");
    if (digitalRead(wipeB) != LOW)
      goto abc;
    delay(1000);
    lcd.clear();
  lcd.setCursor(0,0);
    lcd.print(" You have 5 seconds       to Cancel");
    if (digitalRead(wipeB) != LOW)
      goto abc;
    delay(1000);
    lcd.clear();
  lcd.setCursor(0,0);
    lcd.print(" You have 4 seconds       to Cancel");
    if (digitalRead(wipeB) != LOW)
      goto abc;
    delay(1000);
    lcd.clear();
  lcd.setCursor(0,0);
    lcd.print(" You have 3 seconds       to Cancel");
    if (digitalRead(wipeB) != LOW)
      goto abc;
    delay(1000); 
    lcd.clear();
  lcd.setCursor(0,0);
    lcd.print(" You have 2 seconds       to Cancel");
    if (digitalRead(wipeB) != LOW)
      goto abc;
    delay(1000);
    lcd.clear();
  lcd.setCursor(0,0);
    lcd.print(" You have 1 second        to Cancel");
    if (digitalRead(wipeB) != LOW)
      goto abc;
    delay(1000);
    lcd.clear();
  lcd.setCursor(0,0);   
    if (digitalRead(wipeB) == LOW) {    // If button still be pressed, wipe EEPROM
      Serial.println(F("Starting Wiping EEPROM"));
      lcd.print("  Starting to Wipe         EEPROM");
      for (int x = 0; x < EEPROM.length(); x = x + 1) {    //Loop end of EEPROM address
        if (EEPROM.read(x) == 0) {              //If EEPROM address 0
          // do nothing, already clear, go to the next address in order to save time and reduce writes to EEPROM
       
        }
        else {
          EEPROM.write(x, 0); 			// if not write 0 to clear, it takes 3.3mS
          
        }
      }
      Serial.println(F("EEPROM Successfully Wiped"));
            digitalWrite(redLed, LED_OFF); 	// visualize successful wipe
      delay(200);
      digitalWrite(redLed, LED_ON);
      delay(200);
      digitalWrite(redLed, LED_OFF);
      delay(200);
      digitalWrite(redLed, LED_ON);
      delay(200);
      digitalWrite(redLed, LED_OFF);
      delay(1000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("    EEPROM Clear");
    delay(2000);
    }
    else {
      abc:Serial.println(F("Wiping Cancelled"));
      digitalWrite(redLed, LED_OFF);
      lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("EEPROM wipe Aborted");
    delay(1500);
    lcd.clear();
    lcd.setCursor(0,0);
    }
  }
 
  if (EEPROM.read(1) != 143) {
    Serial.println(F("No Master Card Defined"));
     lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("   No Master Card         Defined");
    tone(buzzer, 1000);
  delay(50);
  noTone(buzzer);
  delay(50);
  tone(buzzer, 1000);
  delay(50);
  noTone(buzzer);
  delay(50);tone(buzzer, 1000);
  delay(50);
  noTone(buzzer);
  delay(50);
  tone(buzzer, 1000);
  delay(50);
  noTone(buzzer);
  delay(50);
    delay(1500);
    Serial.println(F("Scan A PICC to Define as Master Card"));
     lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("   Scan A Card to     Define as Master");
    do {
      successRead = getID();            // sets successRead to 1 when we get read from reader otherwise 0
      digitalWrite(blueLed, LED_ON);    // Visualize Master Card need to be defined
      delay(200);
      digitalWrite(blueLed, LED_OFF);
      delay(200);
    }
    while (!successRead);                  // Program will not go further while you not get a successful read
    for ( int j = 0; j < 4; j++ ) {        // Loop 4 times
      EEPROM.write( 2 + j, readCard[j] );  // Write scanned PICC's UID to EEPROM, start from address 3
    }
    EEPROM.write(1, 143);                  // Write to EEPROM we defined Master Card.
    Serial.println(F("Master Card Defined"));
     lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Master Card Defined");
    delay(1000);
  }
  Serial.println(F("-------------------"));
  Serial.println(F("Master Card's UID"));
  lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(" Master Card's UID        ");
    for ( int i = 0; i < 4; i++ ) {          // Read Master Card's UID from EEPROM
    masterCard[i] = EEPROM.read(2 + i);    // Write it to masterCard
    Serial.print(masterCard[i], HEX);
    lcd.print(masterCard[i],HEX);
  }
  delay(1500);
  Serial.println("");
  Serial.println(F("-------------------"));
  Serial.println(F("Ready"));
  Serial.println(F("Waiting for Card to be Scanned"));
  lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Waiting for Card to      be Scanned");
  cycleLeds();    // Everything ready lets give user some feedback by cycling leds
}


///////////////////////////////////////// Main Loop ///////////////////////////////////
void loop () {
  if(restart==1)
   {digitalWrite(redLed, LED_ON);
        digitalWrite(greenLed, LED_OFF);
        digitalWrite(blueLed, LED_OFF);
        goto res;
   }
  
  do {
    successRead = getID(); 	// sets successRead to 1 when we get read from reader otherwise 0
    if (digitalRead(wipeB) == LOW) {
      if(restart==1)
    goto res;
      digitalWrite(redLed, LED_ON);  // Make sure led is off
      digitalWrite(greenLed, LED_OFF);  // Make sure led is off
      digitalWrite(blueLed, LED_OFF); // Make sure led is off
      Serial.println(F("Wipe Button Pressed"));
      lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("   !!!WARNING!!!    Wipe Button Pressed");
    delay(1000);
      lcd.clear();
    lcd.setCursor(0,0);
      lcd.print(F("Master Card will be Erased in 10 seconds"));
       if (digitalRead(wipeB) != LOW)
       {
        lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("  Master Card Wipe        Aborted");
    delay(1500);
        goto xyz;  
       }
      delay(1000);
      lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(F("Master Card will be Erased in 9 seconds"));
       if (digitalRead(wipeB) != LOW)
       {
        lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(F("  Master Card Wipe        Aborted"));
    delay(1500);
        goto xyz;  
       }
      delay(1000);
      lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(F("Master Card will be Erased in 8 seconds"));
       if (digitalRead(wipeB) != LOW)
       {
        lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(F("  Master Card Wipe        Aborted"));
    delay(1500);
        goto xyz;  
       }
      delay(1000);
      lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(F("Master Card will be Erased in 7 seconds"));
       if (digitalRead(wipeB) != LOW)
       {
        lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(F("  Master Card Wipe        Aborted"));
    delay(1500);
        goto xyz;  
       }
      delay(1000);
      lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(F("Master Card will be Erased in 6 seconds"));
       if (digitalRead(wipeB) != LOW)
       {
        lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(F("  Master Card Wipe        Aborted"));
    delay(1500);
        goto xyz;  
       }
      delay(1000);
      lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(F("Master Card will be Erased in 5 seconds"));
       if (digitalRead(wipeB) != LOW)
       {
        lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(F("  Master Card Wipe        Aborted"));
    delay(1500);
        goto xyz;  
       }
      delay(1000);
      lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(F("Master Card will be Erased in 4 seconds"));
       if (digitalRead(wipeB) != LOW)
       {
        lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(F("  Master Card Wipe        Aborted"));
    delay(1500);
        goto xyz;  
       }
      delay(1000);
      lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(F("Master Card will be Erased in 3 seconds"));
       if (digitalRead(wipeB) != LOW)
       {
        lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(F("  Master Card Wipe        Aborted"));
    delay(1500);
        goto xyz;  
       }
      delay(1000);
      lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(F("Master Card will be Erased in 2 seconds"));
       if (digitalRead(wipeB) != LOW)
       {
        lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(F("  Master Card Wipe        Aborted"));
    delay(1500);
        goto xyz;  
       }
      delay(1000);
      lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(F("Master Card will be Erased in 1 second"));
       if (digitalRead(wipeB) != LOW)
       {
        lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(F("  Master Card Wipe        Aborted"));
    delay(1500);
        goto xyz;  
       }
      delay(1000);
      lcd.clear();
    lcd.setCursor(0,0);
    
      if (digitalRead(wipeB) == LOW) {
        EEPROM.write(1, 0);                  // Reset Magic Number.
        Serial.println(F("Master Card Wiped"));
        lcd.print("Master Card Wiped");
        delay(1000);
        res:lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(" Please Reboot The         System");
        digitalWrite(redLed, LED_ON);
        digitalWrite(greenLed, LED_OFF);
        digitalWrite(blueLed, LED_OFF);
        restart=1;
        qqq:while (digitalRead(wipeB) == LOW)
        {goto qqq;}
        
      }
    }
    if (programMode) {
      cycleLeds();              // Program Mode cycles through RGB waiting to read a new card
    }
    else {
      normalModeOn(); 		// Normal mode, blue Power LED is on, all others are off
    }
  }
  
  while (!successRead); 	//the program will not go further while you not get a successful read
  if (programMode) {
    if ( isMaster(readCard) ) { //If master card scanned again exit program mode
      Serial.println(F("Master Card Scanned"));
      Serial.println(F("Exiting Program Mode"));
      Serial.println(F("-----------------------------"));
      lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Exiting Programming         Mode");
    delay(1500);
      programMode = false;
      goto xyz;
      return;
    }
    else {
      if ( findID(readCard) ) { // If scanned card is known delete it
        Serial.println(F("Card ID Found, Removing..."));
        deleteID(readCard);
        Serial.println("-----------------------------");
        Serial.println(F("Scan a PICC to ADD or REMOVE to EEPROM"));
      }
      else {                    // If scanned card is not known add it
        Serial.println(F("New Card Scanned, Adding..."));
        writeID(readCard);
        Serial.println(F("-----------------------------"));
        Serial.println(F("Scan a PICC to ADD or REMOVE to EEPROM"));
      }
    }
  }
  else {
    if ( isMaster(readCard)) {  	// If scanned card's ID matches Master Card's ID enter program mode
      programMode = true;
      Serial.println(F("Master Card Detected - Entered Program Mode"));
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Master Card Detected");
    delay(1000);
      int count = EEPROM.read(0); 	// Read the first Byte of EEPROM that
      Serial.print(F("Number of record(s) on EEPROM "));    	// stores the number of ID's in EEPROM
      Serial.print(count);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Number of Record(s) on EEPROM -> ");
    lcd.print(count);
    delay(1000);
      Serial.println("");
      Serial.println(F("Scan a PICC to ADD or REMOVE to EEPROM"));
      Serial.println(F("Scan Master Card again to Exit Program Mode"));
      lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Entering Programming        Mode");
    delay(1000);
      Serial.println(F("-----------------------------"));
    }
    else {
      if ( findID(readCard) ) {	// If not, see if the card is in the EEPROM
        Serial.println(F("Valid Card Detected"));
        
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("   Access Granted");
        granted(3000);        	// Open the door lock for 300 ms
        //delay(1000);
        intruder=0;
      }
      else {			// If not, show that the ID was not valid
        Serial.println(F("Invalid Card"));
        
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("   Access Denied");
        denied();
        intruder++;
        delay(1000);
      }
    }
  }
  xyz:if(intruder>3)
  { 
    tone(buzzer, 1000);
    lcd.clear();
    lcd.setCursor(0,0);
    Serial.print("INTRUDER ALERT");
    lcd.print("   !!!WARNING!!!       Intruder Alert");
    digitalWrite(redLed, LED_ON);
    delay(250);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("   !!!WARNING!!!");
    digitalWrite(redLed, LED_OFF);
    delay(250);
    noTone(buzzer);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("   !!!WARNING!!!       Intruder Alert");
    digitalWrite(redLed, LED_ON);
    delay(250);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("   !!!WARNING!!!");
    digitalWrite(redLed, LED_OFF);
    delay(250);
    tone(buzzer, 1000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("   !!!WARNING!!!       Intruder Alert");
    digitalWrite(redLed, LED_ON);
    delay(250);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("   !!!WARNING!!!");
    digitalWrite(redLed, LED_OFF);
    delay(250);
    noTone(buzzer);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("   !!!WARNING!!!       Intruder Alert");
    digitalWrite(redLed, LED_ON);
    delay(250);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("   !!!WARNING!!!");
    digitalWrite(redLed, LED_OFF);
    delay(250);
    tone(buzzer, 1000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("   !!!WARNING!!!       Intruder Alert");
    digitalWrite(redLed, LED_ON);
    delay(250);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("   !!!WARNING!!!");
    digitalWrite(redLed, LED_OFF);
    delay(250);
    noTone(buzzer);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("   !!!WARNING!!!       Intruder Alert");
    digitalWrite(redLed, LED_ON);
    delay(250);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("   !!!WARNING!!!");
    digitalWrite(redLed, LED_OFF);
    delay(250);
    tone(buzzer, 1000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("   !!!WARNING!!!       Intruder Alert");
    digitalWrite(redLed, LED_ON);
    delay(250);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("   !!!WARNING!!!");
    digitalWrite(redLed, LED_OFF);
    delay(250);
    noTone(buzzer);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("   !!!WARNING!!!       Intruder Alert");
    digitalWrite(redLed, LED_ON);
    delay(250);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("   !!!WARNING!!!");
    digitalWrite(redLed, LED_OFF);
    delay(250);
    tone(buzzer, 1000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("   !!!WARNING!!!       Intruder Alert");
    digitalWrite(redLed, LED_ON);
    delay(250);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("   !!!WARNING!!!");
    digitalWrite(redLed, LED_OFF);
    delay(250);
    noTone(buzzer);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("   !!!WARNING!!!       Intruder Alert");
    digitalWrite(redLed, LED_ON);
    delay(250);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("   !!!WARNING!!!");
    digitalWrite(redLed, LED_OFF);
    delay(250);
    tone(buzzer, 1000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("   !!!WARNING!!!       Intruder Alert");
    digitalWrite(redLed, LED_ON);
    delay(250);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("   !!!WARNING!!!");
    digitalWrite(redLed, LED_OFF);
    delay(250);
    noTone(buzzer);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("   !!!WARNING!!!       Intruder Alert");
    digitalWrite(redLed, LED_ON);
    delay(250);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("   !!!WARNING!!!");
    digitalWrite(redLed, LED_OFF);
    delay(250);
    intruder=0;    
  }
  Serial.println(F("Waiting for Card to be Scanned"));
  lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Waiting for Card to      be Scanned");
    
    
}

/////////////////////////////////////////  Access Granted    ///////////////////////////////////
void granted (int setDelay) {
  digitalWrite(blueLed, LED_OFF); 	// Turn off blue LED
  digitalWrite(redLed, LED_OFF); 	// Turn off red LED
  digitalWrite(greenLed, LED_ON); 	// Turn on green LED
  digitalWrite(relay, LOW); 		// Unlock door!
  delay(setDelay); 					// Hold door lock open for given seconds
  digitalWrite(relay, HIGH); 		// Relock door
  delay(1000); 						// Hold green LED on for a second
}

///////////////////////////////////////// Access Denied  ///////////////////////////////////
void denied() {
  digitalWrite(greenLed, LED_OFF); 	// Make sure green LED is off
  digitalWrite(blueLed, LED_OFF); 	// Make sure blue LED is off
  digitalWrite(redLed, LED_ON); 	// Turn on red LED
  delay(1000);
}


///////////////////////////////////////// Get PICC's UID ///////////////////////////////////
int getID() {
  // Getting ready for Reading PICCs
  if ( ! mfrc522.PICC_IsNewCardPresent()) { //If a new PICC placed to RFID reader continue
    return 0;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) {   //Since a PICC placed get Serial and continue
    return 0;
  }
  // There are Mifare PICCs which have 4 byte or 7 byte UID care if you use 7 byte PICC
  // I think we should assume every PICC as they have 4 byte UID
  // Until we support 7 byte PICCs
  Serial.println(F("Scanned Card's UID is :"));
  
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Scanned Card's UID      is - ");
  for (int i = 0; i < 4; i++) {  //
    readCard[i] = mfrc522.uid.uidByte[i];
    Serial.print(readCard[i], HEX);
    lcd.print(readCard[i],HEX);
  }
  digitalWrite(blueLed, LED_OFF);
  delay(50);
  digitalWrite(blueLed, LED_ON);
  delay(50);  
  digitalWrite(blueLed, LED_OFF);
  delay(50);
  digitalWrite(blueLed, LED_ON);
  delay(50);
  digitalWrite(blueLed, LED_OFF);
  delay(50);
  digitalWrite(blueLed, LED_ON);
  delay(50);
  digitalWrite(blueLed, LED_OFF);
  delay(50);
  digitalWrite(blueLed, LED_ON);
  delay(50);
  digitalWrite(blueLed, LED_OFF);
  delay(50);
  digitalWrite(blueLed, LED_ON);
  delay(50);
  digitalWrite(blueLed, LED_OFF);
  delay(50);
  digitalWrite(blueLed, LED_ON);
  delay(50);
  digitalWrite(blueLed, LED_OFF);
  delay(50);
  digitalWrite(blueLed, LED_ON);
  delay(50);
  digitalWrite(blueLed, LED_OFF);
  delay(50);
  digitalWrite(blueLed, LED_ON);
  delay(50);
  digitalWrite(blueLed, LED_OFF);
  delay(50);
  digitalWrite(blueLed, LED_ON);
  delay(50);
  digitalWrite(blueLed, LED_OFF);
  delay(50);
  digitalWrite(blueLed, LED_ON);
  delay(50);
  Serial.println("");
  mfrc522.PICC_HaltA(); // Stop reading
  return 1;
}

void ShowReaderDetails() {
  // Get the MFRC522 software version
  byte v = mfrc522.PCD_ReadRegister(mfrc522.VersionReg);
//  Serial.print(F("MFRC522 Software Version: 0x"));
 // Serial.print(v, HEX);
  /*if (v == 0x91)
  //  Serial.print(F(" = v1.0"));
  else if (v == 0x92)
    Serial.print(F(" = v2.0"));
  else
    Serial.print(F(" (unknown),probably a chinese clone?"));
  Serial.println("");
  // When 0x00 or 0xFF is returned, communication probably failed*/
  if ((v == 0x00) || (v == 0xFF)) {
    Serial.println(F("WARNING: Communication failure, is the MFRC522 properly connected?"));
    Serial.println(F("SYSTEM HALTED: Check connections."));
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("   !!!WARNING!!!     RFID Sensor Error");
    while (true); // do not go further
  }
}

///////////////////////////////////////// Cycle Leds (Program Mode) ///////////////////////////////////
void cycleLeds() {
  digitalWrite(redLed, LED_OFF); 	// Make sure red LED is off
  digitalWrite(greenLed, LED_ON); 	// Make sure green LED is on
  digitalWrite(blueLed, LED_OFF); 	// Make sure blue LED is off
  delay(200);
  digitalWrite(redLed, LED_OFF); 	// Make sure red LED is off
  digitalWrite(greenLed, LED_OFF); 	// Make sure green LED is off
  digitalWrite(blueLed, LED_ON); 	// Make sure blue LED is on
  delay(200);
  digitalWrite(redLed, LED_ON); 	// Make sure red LED is on
  digitalWrite(greenLed, LED_OFF); 	// Make sure green LED is off
  digitalWrite(blueLed, LED_OFF); 	// Make sure blue LED is off
  delay(200);
}

//////////////////////////////////////// Normal Mode Led  ///////////////////////////////////
void normalModeOn () {
  digitalWrite(blueLed, LED_ON); 	// Blue LED ON and ready to read card
  digitalWrite(redLed, LED_OFF); 	// Make sure Red LED is off
  digitalWrite(greenLed, LED_OFF); 	// Make sure Green LED is off
  digitalWrite(relay, HIGH); 		// Make sure Door is Locked
}

//////////////////////////////////////// Read an ID from EEPROM //////////////////////////////
void readID( int number ) {
  int start = (number * 4 ) + 2; 		// Figure out starting position
  for ( int i = 0; i < 4; i++ ) { 		// Loop 4 times to get the 4 Bytes
    storedCard[i] = EEPROM.read(start + i); 	// Assign values read from EEPROM to array
  }
}

///////////////////////////////////////// Add ID to EEPROM   ///////////////////////////////////
void writeID( byte a[] ) {
  if ( !findID( a ) ) { 		// Before we write to the EEPROM, check to see if we have seen this card before!
    int num = EEPROM.read(0); 		// Get the numer of used spaces, position 0 stores the number of ID cards
    int start = ( num * 4 ) + 6; 	// Figure out where the next slot starts
    num++; 								// Increment the counter by one
    EEPROM.write( 0, num ); 		// Write the new count to the counter
    for ( int j = 0; j < 4; j++ ) { 	// Loop 4 times
      EEPROM.write( start + j, a[j] ); 	// Write the array values to EEPROM in the right position
    }
    successWrite();
    Serial.println(F("Succesfully added ID record to EEPROM"));
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("     Card Added");
    delay(1000);
    
  }
  else {
    failedWrite();
    Serial.println(F("Failed! There is something wrong with ID or bad EEPROM"));
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("   !!!WARNING!!!     EEPROM/CARD ERROR");
  }
}

///////////////////////////////////////// Remove ID from EEPROM   ///////////////////////////////////
void deleteID( byte a[] ) {
  if ( !findID( a ) ) { 		// Before we delete from the EEPROM, check to see if we have this card!
    failedWrite(); 			// If not
    Serial.println(F("Failed! There is something wrong with ID or bad EEPROM"));
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("   !!!WARNING!!!     EEPROM/CARD ERROR");
  }
  else {
    int num = EEPROM.read(0); 	// Get the numer of used spaces, position 0 stores the number of ID cards
    int slot; 			// Figure out the slot number of the card
    int start;			// = ( num * 4 ) + 6; // Figure out where the next slot starts
    int looping; 		// The number of times the loop repeats
    int j;
    int count = EEPROM.read(0); // Read the first Byte of EEPROM that stores number of cards
    slot = findIDSLOT( a ); 	// Figure out the slot number of the card to delete
    start = (slot * 4) + 2;
    looping = ((num - slot) * 4);
    num--; 			// Decrement the counter by one
    EEPROM.write( 0, num ); 	// Write the new count to the counter
    for ( j = 0; j < looping; j++ ) { 				// Loop the card shift times
      EEPROM.write( start + j, EEPROM.read(start + 4 + j)); 	// Shift the array values to 4 places earlier in the EEPROM
    }
    for ( int k = 0; k < 4; k++ ) { 				// Shifting loop
      EEPROM.write( start + j + k, 0);
    }
    successDelete();
    Serial.println(F("Succesfully removed ID record from EEPROM"));
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("    Card Deleted");
    digitalWrite(redLed, LED_ON);
    digitalWrite(blueLed, LED_OFF);
    digitalWrite(greenLed, LED_OFF);
    delay(1000);
  }
}

///////////////////////////////////////// Check Bytes   ///////////////////////////////////
boolean checkTwo ( byte a[], byte b[] ) {
  if ( a[0] != NULL ) 			// Make sure there is something in the array first
    match = true; 			// Assume they match at first
  for ( int k = 0; k < 4; k++ ) { 	// Loop 4 times
    if ( a[k] != b[k] ) 		// IF a != b then set match = false, one fails, all fail
      match = false;
  }
  if ( match ) { 			// Check to see if if match is still true
    return true; 			// Return true
  }
  else  {
    return false; 			// Return false
  }
}

///////////////////////////////////////// Find Slot   ///////////////////////////////////
int findIDSLOT( byte find[] ) {
  int count = EEPROM.read(0); 			// Read the first Byte of EEPROM that
  for ( int i = 1; i <= count; i++ ) { 		// Loop once for each EEPROM entry
    readID(i); 								// Read an ID from EEPROM, it is stored in storedCard[4]
    if ( checkTwo( find, storedCard ) ) { 	// Check to see if the storedCard read from EEPROM
      // is the same as the find[] ID card passed
      return i; 				// The slot number of the card
      break; 					// Stop looking we found it
    }
  }
}

///////////////////////////////////////// Find ID From EEPROM   ///////////////////////////////////
boolean findID( byte find[] ) {
  int count = EEPROM.read(0);			// Read the first Byte of EEPROM that
  for ( int i = 1; i <= count; i++ ) {  	// Loop once for each EEPROM entry
    readID(i); 					// Read an ID from EEPROM, it is stored in storedCard[4]
    if ( checkTwo( find, storedCard ) ) {  	// Check to see if the storedCard read from EEPROM
      return true;
      break; 	// Stop looking we found it
    }
    else {  	// If not, return false
    }
  }
  return false;
}

///////////////////////////////////////// Write Success to EEPROM   ///////////////////////////////////
// Flashes the green LED 3 times to indicate a successful write to EEPROM
void successWrite() {
  digitalWrite(blueLed, LED_OFF); 	// Make sure blue LED is off
  digitalWrite(redLed, LED_OFF); 	// Make sure red LED is off
  digitalWrite(greenLed, LED_OFF); 	// Make sure green LED is on
  delay(200);
  digitalWrite(greenLed, LED_ON); 	// Make sure green LED is on
  delay(200);
  digitalWrite(greenLed, LED_OFF); 	// Make sure green LED is off
  delay(200);
  digitalWrite(greenLed, LED_ON); 	// Make sure green LED is on
  delay(200);
  digitalWrite(greenLed, LED_OFF); 	// Make sure green LED is off
  delay(200);
  digitalWrite(greenLed, LED_ON); 	// Make sure green LED is on
  delay(200);
}

///////////////////////////////////////// Write Failed to EEPROM   ///////////////////////////////////
// Flashes the red LED 3 times to indicate a failed write to EEPROM
void failedWrite() {
  digitalWrite(blueLed, LED_OFF); 	// Make sure blue LED is off
  digitalWrite(redLed, LED_OFF); 	// Make sure red LED is off
  digitalWrite(greenLed, LED_OFF); 	// Make sure green LED is off
  delay(200);
  digitalWrite(redLed, LED_ON); 	// Make sure red LED is on
  delay(200);
  digitalWrite(redLed, LED_OFF); 	// Make sure red LED is off
  delay(200);
  digitalWrite(redLed, LED_ON); 	// Make sure red LED is on
  delay(200);
  digitalWrite(redLed, LED_OFF); 	// Make sure red LED is off
  delay(200);
  digitalWrite(redLed, LED_ON); 	// Make sure red LED is on
  delay(200);
}

///////////////////////////////////////// Success Remove UID From EEPROM  ///////////////////////////////////
// Flashes the blue LED 3 times to indicate a success delete to EEPROM
void successDelete() {
  digitalWrite(blueLed, LED_OFF); 	// Make sure blue LED is off
  digitalWrite(redLed, LED_OFF); 	// Make sure red LED is off
  digitalWrite(greenLed, LED_OFF); 	// Make sure green LED is off
  delay(200);
  digitalWrite(blueLed, LED_ON); 	// Make sure blue LED is on
  delay(200);
  digitalWrite(blueLed, LED_OFF); 	// Make sure blue LED is off
  delay(200);
  digitalWrite(blueLed, LED_ON); 	// Make sure blue LED is on
  delay(200);
  digitalWrite(blueLed, LED_OFF); 	// Make sure blue LED is off
  delay(200);
  digitalWrite(blueLed, LED_ON); 	// Make sure blue LED is on
  delay(200);
}

////////////////////// Check readCard IF is masterCard   ///////////////////////////////////
// Check to see if the ID passed is the master programing card
boolean isMaster( byte test[] ) {
  if ( checkTwo( test, masterCard ) )
    return true;
  else
    return false;
}

