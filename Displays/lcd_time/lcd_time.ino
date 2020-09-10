#include <ds3231.h>
#include <Wire.h>
#include <LiquidCrystal.h>

// lcd Configuration
LiquidCrystal lcd (8, 9, 4, 5, 6, 7);

// Setting up the DS3231 library
ds3231 clock;
bool Century = false;
bool h12;
bool PM;
byte ADay, AHour, AMinute, ASecond, ABits;
bool ADy, A12h, Apm;

byte year, month, date, DoW, hour, minute, second;

void setup () {
  // Start the I2C interface 
  Wire.begin ();
     
  // Start the serial
  Serial.begin (115200);

        // Start the lcd
        lcd.begin (16, 2); 

}
void ReadDS3231 () // Function of the DS3231
{
  int second, minute, hour, date, month, year, temperature, day; 
  char name;

  second = clock.getSecond (); // Save the seconds
  minute = clock.getMinute (); // Save the minutes
  hour = clock.getHour (h12, PM); // Save the hours
  date = clock.getDate (); // Save the day of the month
  month = clock.getMonth (Century); // Save the month
  year = clock.getYear (); // Save the year
  day = clock.getDoW (); // Save the day of the week (it saves the value from above)

  Temperature = clock.getTemperature (); // Store temperature

  // Change the weekday variable, which is an int value for the day in char)
  Switch (day) {
    Case 1: name = 'S';
    Break;
    Case 2: name = 'T';
    Break;
    Case 3: name = 'Q';
    Break;
    Case 4: name = 'Q';
    Break;
    Case 5: name = 'S';
    Break;
    Case 6: name = 'S';
    Break;
    Case 7: name = 'D';
    Break;
    Default:
    Break;
  }

  // Play the variables in Serial
  Serial.print ("20");
  Serial.print (year, DEC);
  Serial.print ('-');
  Serial.print (month, DEC);
  Serial.print ('-');
  Serial.print (date, DEC);
  Serial.print (' ');
  Serial.print (hour, DEC);
  Serial.print (':');
  Serial.print (minute, DEC);
  Serial.print (':');
  Serial.print (second, DEC);
  Serial.print ('\ n');
  Serial.print ("Temperature =");
  Serial.print (temperature); 
  Serial.print ('\ n');
  Serial.print ("Day =");
  Serial.print (name); 
  Serial.print ('\ n');

  // First lcd Line
  lcd.setCursor (0,0); // Position the position on the lcd (column, line)
  lcd.print (hour, DEC); // prints the message on the lcd (remembering that each character uses a lcd space)
  lcd.setCursor (2.0);
  lcd.print (":");
  lcd.setCursor (3.0);
  lcd.print (minute, DEC);
  lcd.setCursor (5.0);
  lcd.print (":");
  lcd.setCursor (6,0);
  lcd.print (second, DEC); 
  lcd.setCursor (9,0);
  lcd.print (name); 

  // Second lcd line
  lcd.setCursor (0,1);
  lcd.print (date, DEC); 
  lcd.setCursor (2,1);
  lcd.print ("-"); 
  lcd.setCursor (3.1);
  lcd.print (month, DEC); 
  lcd.setCursor (5.1);
  lcd.print ("-"); 
  lcd.setCursor (6,1);
  lcd.print (year, DEC); 

  lcd.setCursor (9,1);
  lcd.print ("Temp:");
  lcd.setCursor (14,1);
  lcd.print (temperature, DEC); 

}
void loop () {
  ReadDS3231 (); // Calls the clock function
  Delay (1000);

}
