#include <ArdOSC.h>
#include <Ethernet.h>
#include <SPI.h>
#include <IRremote.hpp>

// Network Configuration
const byte MY_IP[] = {192, 168, 1, 177};
const byte MY_MAC[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
const int SERVER_PORT = 8000;
const int DEST_PORT = 9000;

// Pins
const int DIGITAL_PIN_COUNT = 11;

// IR Sender
IRsend irSender;

// Flags for digital pins
int flags[DIGITAL_PIN_COUNT] = {1};

// OSC Server and Client
OSCServer server;
OSCClient client;

// Function prototypes
void setupPins();
void handleRelayOSC(OSCMessage *_mes, int pin);
void handlePWMOSC(OSCMessage *_mes, int pin);
void handleTVControlOSC(OSCMessage *_mes, int command);

void setup() {
  Serial.begin(9600);

  // Initialize IR Sender
  irSender.begin(4, ENABLE_LED_FEEDBACK);

  // Start Ethernet
  Ethernet.begin(MY_MAC, MY_IP);

  // Start OSC Server
  server.begin(SERVER_PORT);

  // Set up pins
  setupPins();
}

void loop() {
  // Check for OSC messages
  if (server.availableCheck() > 0) {
    // Handle OSC messages
  }

  // Handle other tasks or sensors
}

void setupPins() {
  for (int i = 2; i < DIGITAL_PIN_COUNT; i++) {
    pinMode(i, OUTPUT);
  }
}

void handleRelayOSC(OSCMessage *_mes, int pin) {
  int value = (int)_mes->getArgFloat(0);
  digitalWrite(pin, value);
  flags[pin] = value;

  // Create response OSC message
  OSCMessage txMes;
  txMes.setAddress(_mes->getIpAddress(), DEST_PORT);
  txMes.beginMessage(("/ard/relePin" + String(pin)).c_str());
  txMes.addArgInt32(flags[pin]);
  client.send(&txMes);
}

void handlePWMOSC(OSCMessage *_mes, int pin) {
  int value = (int)_mes->getArgFloat(0);
  analogWrite(pin, value);

  // Create response OSC message
  OSCMessage txMes;
  txMes.setAddress(_mes->getIpAddress(), DEST_PORT);
  txMes.beginMessage(("/ard/pwmPin" + String(pin)).c_str());
  txMes.addArgInt32(value);
  client.send(&txMes);
}

void handleTVControlOSC(OSCMessage *_mes, int command) {
  // Send IR signal based on command
  switch (command) {
    case 11: irSender.sendRC6(0x0, 0x10058, 0, true); break;  // Arrow up
    case 12: irSender.sendRC6(0x0, 0x1005A, 0, true); break;  // Arrow left
    case 13: irSender.sendRC6(0x0, 0x10059, 0, true); break;  // Arrow down
    case 14: irSender.sendRC6(0x0, 0x1005B, 0, true); break;  // Arrow right
    case 15: irSender.sendRC6(0x0, 0x1005C, 0, true); break;  // OK button
    case 16: irSender.sendRC6(0x0, 0x10010, 0, true); break; // Volume up
    case 17: irSender.sendRC6(0x0, 0x10011, 0, true); break; // Volume down
    case 18: irSender.sendRC6(0x0, 0x1000D, 0, true); break; // Mute
    case 19: irSender.sendRC6(0x0, 0x10040, 0, true); break; // Options
    case 20: irSender.sendRC6(0x0, 0x10054, 0, true); break; // Home
    case 21: irSender.sendRC6(0x0, 0x1000C, 0, true); break; // On/Off
    default: break;
  }
}
