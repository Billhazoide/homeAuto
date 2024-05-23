#include <ArdOSC.h>
#include <Ethernet.h>
#include <SPI.h>
#include <IRremote.hpp>

// Ethernet configuration
const byte myIp[] = {192, 168, 1, 177};
const byte myMac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
const int serverPort = 8000;
const int destPort = 9000;

// IR setup
IRsend irsend;

// Pin configuration
const int DigitalPinCount = 11;
int flags[DigitalPinCount] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

// OSC server and client
OSCServer server;
OSCClient client;

void setup() {
  Serial.begin(9600);
  
  // Ethernet setup
  Ethernet.begin(myMac, myIp);
  server.begin(serverPort);

  // OSC callbacks
  setupOSC();
  
  // Initialize pins
  setupPins();
}

void loop() {
  // server.parse();
  server.availableCheck();
}

void setupOSC() {
  server.addCallback("/ard/relePin2", &togglePin);
  server.addCallback("/ard/relePin3", &togglePin);
  server.addCallback("/ard/pwmPin3", &setPwm);
  // server.addCallback("/ard/pwmPin4", &handleTVControlOSC);
  // Add more callbacks as needed
}

void setupPins() {
  for (int i = 1; i < DigitalPinCount; i++) {
    pinMode(i, OUTPUT);
  }
}

void togglePin(OSCMessage *_mes) {
  // int pin = _mes->getArgInt32(0);
  String address = _mes->getOSCAddress();
  int pin = address.substring(12).toInt();

  flags[pin] = !flags[pin];

  digitalWrite(pin, flags[pin]);

  sendOSCMessage("/ard/relePin" + String(pin), flags[pin], _mes );
}

void setPwm(OSCMessage *_mes) {

  String address = _mes->getOSCAddress();
  int pin = address.substring(11).toInt();

  // int pin = _mes->getArgInt32(0);
  int value = _mes->getArgInt32(1);
  analogWrite(pin, value);
  sendOSCMessage("/ard/pwmPin" + String(pin), value, _mes);
}

// void handleTVControlOSC(OSCMessage *_mes, int command) {
//   // Send IR signal based on command
//   // Those IR codes are to controll Phillips tv
//   switch (command) {
//     case 11: irSender.sendRC6(0x0, 0x10058, 0, true); break;  // Arrow up
//     case 12: irSender.sendRC6(0x0, 0x1005A, 0, true); break;  // Arrow left
//     case 13: irSender.sendRC6(0x0, 0x10059, 0, true); break;  // Arrow down
//     case 14: irSender.sendRC6(0x0, 0x1005B, 0, true); break;  // Arrow right
//     case 15: irSender.sendRC6(0x0, 0x1005C, 0, true); break;  // OK button
//     case 16: irSender.sendRC6(0x0, 0x10010, 0, true); break; // Volume up
//     case 17: irSender.sendRC6(0x0, 0x10011, 0, true); break; // Volume down
//     case 18: irSender.sendRC6(0x0, 0x1000D, 0, true); break; // Mute
//     case 19: irSender.sendRC6(0x0, 0x10040, 0, true); break; // Options
//     case 20: irSender.sendRC6(0x0, 0x10054, 0, true); break; // Home
//     case 21: irSender.sendRC6(0x0, 0x1000C, 0, true); break; // On/Off
//     default: break;
//   }

void sendOSCMessage(String address, int value, OSCMessage * _mes) {
  OSCMessage txMes;
  txMes.setAddress(_mes->getIpAddress(), destPort);
  txMes.beginMessage(address.c_str());
  txMes.addArgInt32(value);
  client.send(&txMes);
}
