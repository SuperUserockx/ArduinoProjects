# Home Automation with Alexa and NodeMCU
WeMos smart devices emulation using FAUXMOESP Library

Code based on the great open source lib & example code at : http://tinkerman.cat/emulate-wemo-device-esp8266/ which is based off of the Python example code by : https://github.com/makermusings/fauxmo

Also, thanks to Sid for Sid's E Classroom : https://www.youtube.com/c/SidsEClassroom

fauxmoESP is a library for ESP8266-based devices that emulates a Belkin WeMo device 
and thus allows you to control them using this protocol, in particular from 
Alexa-powered devices like the Amazon Echo or the Dot.
 
4 Simple WeMo devices

  ==> Light1    ==> Relay 1 ==> NodeMCU D5
  
  ==> Light2    ==> Relay 3 ==> NodeMCU D7
  
  ==> Outlet1   ==> Relay 2 ==> NodeMCU D6 
  
  ==> Outlet2   ==> Relay 4 ==> NodeMCU D8
 
To discovery devices for the first time, use voice commnad: 
"Computer (or Alexa), discovery devices"
 
To activate a device or a gropu of devices, you should use voice commands, like: 

  "Computer (or Alexa), turn on Light1" or "..., turn off Light1"
  
  "Computer (or Alexa), turn on Living Room" or "..., turn off Living Room"
  
  "Computer (or Alexa), turn on All Devices" or "..., turn off All Devices"
