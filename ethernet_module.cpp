#include <ArdOSC.h>
#include <Ethernet.h>
#include <SPI.h>

//Set IP for the main automation server
byte myIp[]  = { 192, 168, 0, 210 };   

//Set rx port to OSC
int  serverPort  = 8000;

//Set tx port for OSC
int destPort = 9000;

//Set arduino digital port
int relePin2 =  2;
int relePin3 =  3;
int relePin4 =  4;
int relePin5 =  5;
int relePin6 =  6;
int relePin7 =  7;
int relePin8 =  8;   
int relePin9 =  9;

// Initial state of the port
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

  //Start ethernet module interface
  Ethernet.begin(myIp);  

  //Start OSC server setting rx port
  server.begin(serverPort);   

  //set callback function & oscaddress
  server.addCallback("/ard/relePin2", &func);  
  server.addCallback("/ard/relePin3", &func2); 
  server.addCallback("/ard/relePin4", &func3); 
  server.addCallback("/ard/relePin5", &func4); 
  server.addCallback("/ard/relePin6", &func5); 
  server.addCallback("/ard/relePin7", &func6); 
  server.addCallback("/ard/relePin8", &func7); 
  server.addCallback("/ard/relePin9", &func8); 

  //Set digital port X as output
  pinMode(relePin2, OUTPUT);   
  pinMode(relePin3, OUTPUT);
  pinMode(relePin4, OUTPUT);
  pinMode(relePin5, OUTPUT);
  pinMode(relePin6, OUTPUT);
  pinMode(relePin7, OUTPUT);
  pinMode(relePin8, OUTPUT);
  pinMode(relePin9, OUTPUT);

}
  
void loop(){
  
  //Check for new OSC msg
  if(server.availableCheck()>0){   
    Serial.println("alive, mf!"); 
  }
  
}

// Tread OSC message
void func(OSCMessage *_mes) { 
  // Store value the args from OSC ("/ard/relePin2")
  int value = (int)_mes->getArgFloat(0);

  // Switch digital port
  digitalWrite(relePin2, value);

  // Create new osc message
  OSCMessage txMes;

  // Set destination ip address & destination OSC port
  txMes.setAddress(_mes->getIpAddress(), destPort);
  
  // Set OSC command (route)
  txMes.beginMessage("/ard/relePin2");
  
  // Set port state in OSC message 
  txMes.addArgFloat(flag2);

  if (flag2 == 1) {
    flag2 = 0;
    digitalWrite(relePin2, LOW);
  } else {
    flag2 = 1;
    digitalWrite(relePin2, HIGH);
  }

  // Set port status in OSC message
  txMes.addArgInt32(flag2);

  // Send OSC message to client 
  client.send(&txMes);

}