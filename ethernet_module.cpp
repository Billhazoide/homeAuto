#include <ArdOSC.h>
#include <Ethernet.h>
#include <SPI.h>

//Set IP for the main automation server
const byte myIp[]  = { 192, 168, 0, 10 };   

// Set Mac address to ethernet shield
const byte myMac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};

//Set rx port to OSC
const int serverPort  = 8000;

//Set tx port for OSC
const int destPort = 9000;

//Set arduino digital port
const int DigitalPinCount = 14;

// Initial state of the port, 1 = Off
int flag2 = 1;
int flag3 = 1;
int flag4 = 1;
int flag5 = 1;
int flag6 = 1;
int flag7 = 1;
int flag8 = 1;
int flag9 = 1;

//Start OSC server (tread with rx OSC msg)
OSCServer server;    

//Start OSC client (tread with tx OSC msg)
OSCClient client;    

void setup() {
  
  //Start ethernet module interface
  Ethernet.begin(myMac, myIp);  

  //Start OSC server setting rx port
  server.begin(serverPort);   

  //Set callback function to oscaddress (routes)
  // Those are for turn on/off relay channel 
  server.addCallback("/ard/relePin2", &func2); 
  server.addCallback("/ard/relePin3", &func3); 
  server.addCallback("/ard/relePin4", &func4); 
  server.addCallback("/ard/relePin5", &func5); 
  server.addCallback("/ard/relePin6", &func6); 
  server.addCallback("/ard/relePin7", &func7); 
  server.addCallback("/ard/relePin8", &func8); 
  server.addCallback("/ard/relePin9", &func9); 
  server.addCallback("/ard/digPin10", &func10);

  // Call function
  setupPins();
}

void func10(OSCMessage *_mes){
  // Request from OSC
  int value = (int)_mes -> getArgFloat(0);

  // Create new osc message
  OSCMessage txMes;

  // Set destination ip address & destination OSC port
  txMes.setAddress(_mes->getIpAddress(), destPort);
  
  // Set OSC command
  txMes.beginMessage("/ard/digPin10");
  
  // Change value in 9 digi port
  analogWrite(9,value);
  
  // Set port state in OSC message 
  txMes.addArgFloat(value);
  
  // Set port status in OSC message
  txMes.addArgInt32(value);

  // Send OSC message to client 
  client.send(&txMes);
}
  
void loop(){
  // Check for any new OSC msg
  if(server.availableCheck()>0) {
//     Serial.println("alive, mf! "); 
  }
  
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
    digitalWrite(2, LOW);
  } else {
    flag2 = 1;
    digitalWrite(2, HIGH);
  }
  
  // Set port status in OSC message
  txMes.addArgInt32(flag2);

  // Send OSC message to client 
  client.send(&txMes);
}


// Tread OSC message
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
  txMes.addArgFloat(flag3);
  
  if (flag3 == 1) {
    flag3 = 0;
    digitalWrite(3, LOW);
  } else {
    flag3 = 1;
    digitalWrite(3, HIGH);
  }
  
  // Set port status in OSC message
  txMes.addArgInt32(flag3);

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
  txMes.addArgFloat(flag5);
  
  if (flag5 == 1) {
    flag5 = 0;
    digitalWrite(5, LOW);
  } else {
    flag5 = 1;
    digitalWrite(5, HIGH);
  }
  
  // Set port status in OSC message
  txMes.addArgInt32(flag5);

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
  txMes.addArgFloat(flag6);
  
  if (flag6 == 1) {
    flag6 = 0;
    digitalWrite(6, LOW);
  } else {
    flag6 = 1;
    digitalWrite(6, HIGH);
  }
  
  // Set port status in OSC message
  txMes.addArgInt32(flag6);

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