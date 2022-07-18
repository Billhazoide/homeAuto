#include <ArdOSC.h>
#include <Ethernet.h>
#include <SPI.h>

//Set IP for the main automation server
byte myIp[]  = { 192, 168, 0, 10 };   

// Set Mac address to ethernet shield
byte myMac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};

//Set rx port to OSC
int  serverPort  = 8000;

//Set tx port for OSC
int destPort = 9000;

//Set arduino digital port
int DigitalPinCount = 9;

// Initial state of the port, 1 = Off
int flag = 1;

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
  server.addCallback("/ard/relePin2", &func); 

  // Call function
  setupPins();
}
  
void loop(){
  // Check for any new OSC msg
  if(server.availableCheck()>0) {
    // Serial.println("alive, mf! "); 
  }
}

void setupPins(){
  //Set digital port X as output
  for(int i=0; i < DigitalPinCount; i++){
    pinMode(i, OUTPUT);
  }
}

// Tread OSC message
void func(OSCMessage * _mes) { 
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
  txMes.addArgFloat(flag);
  
  if (flag == 1) {
    flag = 0;
    digitalWrite(2, LOW);
  } else {
    flag = 1;
    digitalWrite(2, HIGH);
  }
  
  // Set port status in OSC message
  txMes.addArgInt32(flag);

  // Send OSC message to client 
  client.send(&txMes);
}