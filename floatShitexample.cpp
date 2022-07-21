// Laser Spirograph @ Pablo Gerbasi 2011 V 1.0
//////////////////////////////////////////////////////

// import oscP5 libraries and Arduino serial libraries
import oscP5.*;
import netP5.*;
import processing.serial.*;
import cc.arduino.*;
 
// Make a new Arduino object
Arduino arduino;
 
// Make a new oscP5 object
OscP5 oscP5;
 
// Setup the value for the Faders and Buttons
float fader1 = 0.0f;
float fader2 = 0.0f;
float toggle1 = 0.0f;
 
// Run the setup loop
void setup() {
 
 
  // start oscP5, listening for incoming messages at port 8000
  // if your outgoing port on TouchOSC is not 8000, edit it here
  oscP5 = new OscP5(this,8000);
 
  // establish a serial connection with the Arduino at 57600 baud
  // this will use the first listing in the serial list, change if necessary
  arduino = new Arduino(this,Serial.list()[0],57600);
 
 
}
 
  // when OSC packets are received
 void oscEvent(OscMessage theOscMessage) {
 
  // set the current address to the control name
  String addr = theOscMessage.addrPattern();
 
  // get the value of the control
  float  val  = theOscMessage.get(0).floatValue();
 
  // if statements to assign values of OSC controls
  
  if(addr.equals("/1/fader1"))  { fader1 = val; }
  else if(addr.equals("/2/fader2"))  { fader2 = val; }
  else if(addr.equals("/1/toggle1"))  { toggle1 = val; } 
 
}
 
  // the program loop
  
void draw() {
 
  // Random function to generate Random Laser Patterns
  while (toggle1 == 1) {
    arduino.analogWrite(11, (int) random(0,255));
    arduino.analogWrite(10, (int) random(0,255));
    delay(1000);  }
    
  // write the int value of Fader to pin 11 on Arduino
  arduino.analogWrite(11, (int) fader1);
  // write the int value of Fader button to pin 10 on Arduino
  arduino.analogWrite(10, (int) fader2);
 
  // print the status of Faders in serial debugger
  
  print(fader1);
  print("   ");
  print(fader2);
  println("   ");
 
}