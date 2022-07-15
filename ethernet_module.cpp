#include <ArdOSC.h>
#include <Ethernet.h>
#include <SPI.h>

//Set IP for the main automation server
byte myIp[]  = { 192, 168, 0, 210 };   

//Set rx port from OSC
int  serverPort  = 8000;

//Set tx port to OSC
int destPort = 9000;

//Set ard port
int relePin2 =  2;
int relePin3 =  3;
int relePin4 =  4;
int relePin5 =  5;
int relePin6 =  6;
int relePin7 =  7;
int relePin8 =  8;   
int relePin9 =  9;

// Initial state
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
  server.addCallback("/ard/relePin2", &func2);  
  server.addCallback("/ard/relePin3", &func3); 
  server.addCallback("/ard/relePin4", &func4); 
  server.addCallback("/ard/relePin5", &func5); 
  server.addCallback("/ard/relePin6", &func6); 
  server.addCallback("/ard/relePin7", &func7); 
  server.addCallback("/ard/relePin8", &func8); 
  server.addCallback("/ard/relePin9", &func9); 

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
  if(server.aviableCheck()>0){   
    Serial.println("alive, mf!"); 
  }
  
}