#include <ArdOSC.h>
#include <Ethernet.h>
#include <SPI.h>
#include <IRremote.hpp>

//Set IP for the main automation server
const byte myIp[]  = { 192, 168, 0, 10 };   

// Set Mac address to ethernet shield
const byte myMac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};

//Set rx port to OSC
const int serverPort  = 8000;

//Set tx port for OSC
const int destPort = 9000;

//Set arduino digital port
const int DigitalPinCount = 10;

// Alarm, 0 === ON.
int active = 0;

//IR shit
IRsend irsend;

// Initial state of the port, 1 = Off
int flag2 = 0;
int flag3 = 0;
int flag4 = 0;
int flag5 = 0;
int flag6 = 0;
int flag7 = 0;
int flag8 = 0;
int flag9 = 0;

//Start OSC server (tread with rx OSC msg)
OSCServer server;    

//Start OSC client (tread with tx OSC msg)
OSCClient client;    

void setup() {
  Serial.begin(9600);

  // IR SHIT

  // Just to know which program is running on my Arduino
  // Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_IRREMOTE));
     
  // Specify send pin and enable feedback LED at default feedback LED pin
  IrSender.begin(3, ENABLE_LED_FEEDBACK);
  
  // Serial.println(F("Ready to send IR signals at pin 3"));

  // Start ethernet module interface
  Ethernet.begin(myMac, myIp);  

  // Start OSC server setting rx port
  server.begin(serverPort);   

  // Set callback function to oscaddress (routes)
  // Those are for turn on/off relay channel 
  server.addCallback("/ard/relePin2", &func2); 
  server.addCallback("/ard/relePin3", &func3); 
  server.addCallback("/ard/relePin4", &func4); 
  server.addCallback("/ard/relePin5", &func5); 
  server.addCallback("/ard/relePin6", &func6); 
  server.addCallback("/ard/relePin7", &func7); 
  server.addCallback("/ard/relePin8", &func8); 
  
  // PWM  
  server.addCallback("/ard/relePin9", &func9); 
  server.addCallback("/ard/digPin10", &func10);

  // IR tv signal relate
  // Arrow up  
  server.addCallback("/ard/tvPin1", &func11);
  // Arrow left
  server.addCallback("/ard/tvPin2", &func12);
  // Arrow down
  server.addCallback("/ard/tvPin3", &func13);
  // Arrow right
  server.addCallback("/ard/tvPin4", &func14);
  // OK button
  server.addCallback("/ard/tvPin5", &func15);
  // Volume up/Down
  server.addCallback("/ard/tvPin6", &func16);
  // Mute
  server.addCallback("/ard/tvPin7", &func17);
  // Options
  server.addCallback("/ard/tvPin8", &func18);
  // Home
  server.addCallback("/ard/tvPin9",&func19);
  // On/Off
  server.addCallback("/ard/tvPin10",&func20);

  // Call function to set pinMode
  // Set pins OUTPUT 2 to 10
  setupPins();
}
  
void loop(){
  // Check for any new OSC msg
  if(server.availableCheck()>0) {
  // Serial.println("alive, mf! "); 
  }
  
  // ALARM TEST SHITS
  // Read magnetic sensor on Analog port 0
  // int alarm = analogRead(A0);

  // // If active and sensor readings higher than 0
  // // Relay will be activated with a siren.
  // if(active > 0 && alarm > 0){
  //     Serial.println(Intruder!);
  //     // Activating digital port 2
  //     digitalWrite(2, LOW);     
  //   }
}

void setupPins(){
  //Set digital port X as output
  for(int i=1; i < DigitalPinCount; i++){
    pinMode(i, OUTPUT);
  }
}

// Tread OSC message
void func2(OSCMessage * _mes) { 
  // Store value the args from OSC client
  int value = (int)_mes -> getArgFloat(0);

  // Switch digital port value
  digitalWrite(2, value);
  
  // Create new osc message
  OSCMessage txMes;

  // Set destination ip address & destination OSC port
  txMes.setAddress(_mes->getIpAddress(), destPort);
  
  // Set OSC command
  txMes.beginMessage("/ard/relePin2");
  
  // Set port state in OSC message 
  txMes.addArgFloat(flag2);
  
  if (flag2 == 1) {
    flag2 = 0;
    // active = 1;
    digitalWrite(2, LOW);
  } else {
    flag2 = 1;
    // active = 0;
    digitalWrite(2, HIGH);
  }
  
  // Set port status in OSC message
  txMes.addArgInt32(flag2);

  // Send OSC message to client 
  client.send(&txMes);
}


// Tread OSC message
// Ambient light (LED tape/Abajour)
void func3(OSCMessage * _mes) { 
  // Store value the args from OSC client
  int value = (int)_mes -> getArgFloat(0);

  // Switch digital port value
  digitalWrite(3, value);
  
  // Create new osc message
  OSCMessage txMes;

  // Set destination ip address & destination OSC port
  txMes.setAddress(_mes->getIpAddress(), destPort);
  
  // Set OSC command
  txMes.beginMessage("/ard/relePin3");
  
  // Set port state in OSC message 
  txMes.addArgFloat(value);

  analogWrite(3, value);

  // Set port status in OSC message
  txMes.addArgInt32(value);

  // Send OSC message to client 
  client.send(&txMes);
}


// Tread OSC message
void func4(OSCMessage * _mes) { 
  // Store value the args from OSC client
  int value = (int)_mes -> getArgFloat(0);

  // Switch digital port value
  digitalWrite(4, value);
  
  // Create new osc message
  OSCMessage txMes;

  // Set destination ip address & destination OSC port
  txMes.setAddress(_mes->getIpAddress(), destPort);
  
  // Set OSC command
  txMes.beginMessage("/ard/relePin4");
  
  // Set port state in OSC message 
  txMes.addArgFloat(flag4);
  
  if (flag4 == 1) {
    flag4 = 0;
    digitalWrite(4, LOW);
  } else {
    flag4 = 1;
    digitalWrite(4, HIGH);
  }
  
  // Set port status in OSC message
  txMes.addArgInt32(flag4);

  // Send OSC message to client 
  client.send(&txMes);
}


// Tread OSC message
void func5(OSCMessage * _mes) { 
  // Store value the args from OSC client
  int value = (int)_mes -> getArgFloat(0);

  // Switch digital port value
  digitalWrite(5, value);
  
  // Create new osc message
  OSCMessage txMes;

  // Set destination ip address & destination OSC port
  txMes.setAddress(_mes->getIpAddress(), destPort);
  
  // Set OSC command
  txMes.beginMessage("/ard/relePin5");
  
  // Set port state in OSC message 
  txMes.addArgFloat(value);
  
  analogWrite(5, value);

  // Set port status in OSC message
  txMes.addArgInt32(value);

  // Send OSC message to client 
  client.send(&txMes);
}


// Tread OSC message
void func6(OSCMessage * _mes) { 
  // Store value the args from OSC client
  int value = (int)_mes -> getArgFloat(0);

  // Switch digital port value
  digitalWrite(6, value);
  
  // Create new osc message
  OSCMessage txMes;

  // Set destination ip address & destination OSC port
  txMes.setAddress(_mes->getIpAddress(), destPort);
  
  // Set OSC command
  txMes.beginMessage("/ard/relePin6");
  
  // Set port state in OSC message 
  txMes.addArgFloat(value);
  
  if (flag6 == 1) {
    flag6 = 0;
    digitalWrite(6, LOW);
  } else {
    flag6 = 1;
    digitalWrite(6, HIGH);
  }
  
  // Set port status in OSC message
  txMes.addArgInt32(value);

  // Send OSC message to client 
  client.send(&txMes);
}

// Tread OSC message
void func7(OSCMessage * _mes) { 
  // Store value the args from OSC client
  int value = (int)_mes -> getArgFloat(0);

  // Switch digital port value
  digitalWrite(7, value);
  
  // Create new osc message
  OSCMessage txMes;

  // Set destination ip address & destination OSC port
  txMes.setAddress(_mes->getIpAddress(), destPort);
  
  // Set OSC command
  txMes.beginMessage("/ard/relePin7");
  
  // Set port state in OSC message 
  txMes.addArgFloat(flag7);
  
  if (flag7 == 1) {
    flag7 = 0;
    digitalWrite(7, LOW);
  } else {
    flag7 = 1;
    digitalWrite(7, HIGH);
  }
  
  // Set port status in OSC message
  txMes.addArgInt32(flag7);

  // Send OSC message to client 
  client.send(&txMes);
}

// Tread OSC message
void func8(OSCMessage * _mes) { 
  // Store value the args from OSC client
  int value = (int)_mes -> getArgFloat(0);

  // Switch digital port value
  digitalWrite(8, value);
  
  // Create new osc message
  OSCMessage txMes;

  // Set destination ip address & destination OSC port
  txMes.setAddress(_mes->getIpAddress(), destPort);
  
  // Set OSC command
  txMes.beginMessage("/ard/relePin8");
  
  // Set port state in OSC message 
  txMes.addArgFloat(flag8);
  
  if (flag8 == 1) {
    flag8 = 0;
    digitalWrite(8, LOW);
  } else {
    flag8 = 1;
    digitalWrite(8, HIGH);
  }
  
  // Set port status in OSC message
  txMes.addArgInt32(flag8);

  // Send OSC message to client 
  client.send(&txMes);
}

// Tread OSC message
void func9(OSCMessage * _mes) { 
  // Store value the args from OSC client
  int value = (int)_mes -> getArgFloat(0);

  // Switch digital port value
  digitalWrite(9, value);
  
  // Create new osc message
  OSCMessage txMes;

  // Set destination ip address & destination OSC port
  txMes.setAddress(_mes->getIpAddress(), destPort);
  
  // Set OSC command
  txMes.beginMessage("/ard/relePin9");
  
  // Set port state in OSC message 
  txMes.addArgFloat(flag9);
  
  if (flag9 == 1) {
    flag9 = 0;
    digitalWrite(9, LOW);
  } else {
    flag9 = 1;
    digitalWrite(9, HIGH);
  }
  
  // Set port status in OSC message
  txMes.addArgInt32(flag9);

  // Send OSC message to client 
  client.send(&txMes);
}

void func10(OSCMessage *_mes){
  // read osc request from android
  int value = (int)_mes -> getArgFloat(0);

  // Create new osc message
  OSCMessage txMes;

  // Set destination ip address & destination OSC port
  txMes.setAddress(_mes->getIpAddress(), destPort);
  
  // Set OSC command
  txMes.beginMessage("/ard/digPin10");

  analogWrite(10,value);
  
  // Set port state in OSC message 
  txMes.addArgFloat(value);
  
  // Set port status in OSC message
  txMes.addArgInt32(value);

  // Send OSC message to client 
  client.send(&txMes);
}

// Arrow up
void func11(){
  IrSender.sendRC6(0x0, 0x10058, 0, true);
}

// Arrow left
void func12(){
  IrSender.sendRC6(0x0, 0x1005A, 0, true);
}

// Arrow down
void func13(){
  IrSender.sendRC6(0x0, 0x10059, 0, true);
}

// Arrow right
void func14(){
  IrSender.sendRC6(0x0, 0x1005B, 0, true);
}

// OK
void func15(){
  IrSender.sendRC6(0x0, 0x1005C, 0, true);
}

// Increase/decrease tv volume
void func16(OSCMessage *_mes){
  int value = (int)_mes -> getArgFloat(0);
  
  int previousValue = 50; 
  
  if(value <= previousValue){
    // Volume down
    IrSender.sendRC6(0x0, 0x10011, 0, true);
  } else {
    // Volume up
    IrSender.sendRC6(0x0, 0x10010, 0, true);
  }
}

// Mute
void func17(){
  IrSender.sendRC6(0x0, 0x1000D, 0, true);
}

// Options
void func18(){
  IrSender.sendRC6(0x0, 0x10040, 0, true);
}

// Home
void func19(){
  IrSender.sendRC6(0x0, 0x10054, 0, true);
}

// On/Off
void func20(){
  IrSender.sendRC6(0x0, 0x1000C, 0, true);
}