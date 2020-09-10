//include libraries
#include <SoftwareSerial.h>
#include <AFMotor.h>

AF_DCMotor motor1(1, MOTOR12_64KHZ); // create motor #2, 64KHz pwm
AF_DCMotor motor2(2, MOTOR12_64KHZ);

SoftwareSerial esp8266(2, 13); //RX pin = 3, TX pin = 2

//definition of variables
#define DEBUG true //show messages between ESP8266 and Arduino in serial port
int state = 5; //define initial state of the robot (5 = stand-by)
//define motor pins

//*****
//SETUP
//*****
void setup()
{
  //set pin modes
  motor1.setSpeed(90);
  motor2.setSpeed(105);
  //start communication
  Serial.begin(9600);
  esp8266.begin(9600);
  
  sendData("AT+RST\r\n", 2000, DEBUG); //reset module
  sendData("AT+CWMODE=1\r\n", 1000, DEBUG); //set station mode
  sendData("AT+CWJAP=\"super2\",\"hahahahaha\"\r\n", 2000, DEBUG); //connect wi-fi network (replace XXXXX by your Wi-Fi router SSID and YYYYY by its password
  delay(5000); //wait for connection

  sendData("m\r\n", 1000, DEBUG); //show IP address
  sendData("AT+CIPMUX=1\r\n", 1000, DEBUG); //allow multiple connections
  sendData("AT+CIPSERVER=1,80\r\n", 1000, DEBUG); // start web server on port 80
}

//*********
//MAIN LOOP
//*********
void loop()
{
  
  if (esp8266.available())  //verify incoming data
  {
    if (esp8266.find("+IPD,")) //if there is a message
    {
      String msg;
      esp8266.find("?"); //look for the message
      msg = esp8266.readStringUntil(' '); //read whole message
      String command = msg.substring(0, 3); //first 3 characters = command
      Serial.println(command);
           
      //move forward
      if(command == "cm1") {
          state = 1;
      }

      //move backward
      if(command == "cm2") {
          state = 2;
      }

      //turn right
      if(command == "cm3") {
          state = 3;
       }
       
       //turn left
       if(command == "cm4") {
          state = 4;
       }
       //stop       
       if(command == "cm5") {
          state = 5;
       }

    }
  }
  
  //STATE 1: move forward
  if (state == 1) {
    motor1.run(FORWARD);
  motor2.run(FORWARD);
  }
  //STATE 2: move backward
  if (state == 2) {
    motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  
     }
  //STATE 3: move right
  if (state == 3) {
   motor1.run(FORWARD);
  motor2.run(RELEASE);
  
   }
  //STATE 4: move left
  if (state == 4) {
    
  motor1.run(RELEASE);
    motor2.run(FORWARD);
  }
    //STATE 5: stop
  if (state == 5) {
    motor1.run(RELEASE);
  motor2.run(RELEASE);
  
     }
  
  
  
}

//*******************
//Auxiliary functions
//*******************
String sendData(String command, const int timeout, boolean debug)
{
  String response = "";
  esp8266.print(command);
  long int time = millis();
  while ( (time + timeout) > millis())
  {
    while (esp8266.available())
    {
      char c = esp8266.read();
      response += c;
    }
  }
  Serial.print(response);
  if (debug)
  {
    Serial.print(response);
  }
  return response;
}


