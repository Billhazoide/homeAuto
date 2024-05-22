# Home Automation.
## Libraries to use
[![IRremote](https://img.shields.io/badge/IRremote-3.5.0-red.svg)]()
[![ArdOsc](https://img.shields.io/badge/ArdOsc-2.2.0-lightblue)]()
[![Ethernet](https://img.shields.io/badge/Ethernet-1.1.2-lightgreen)]()

## :shipit: Before compile to the board, switch to ".ino" extension.
[![Arduino](https://img.shields.io/badge/Arduino-1.8.1-green.svg)]() [![NPM Version](https://img.shields.io/badge/TouchOSCEditor-1.8.9-blue)]() [![NODE VERSION](https://img.shields.io/badge/TouchOSC-1.9.1-lightblue)]() [![NODEMON VERSION](https://img.shields.io/badge/TouchBridge-1.7.3-orange)]()
### Description.
Simple script to automate the house with Arduino and a smartphone.
### Arquiteture.
The project is been made with C++, using  [Arduino](https://www.arduino.cc/) AT Mega 2650 board, ethernet shield W5100
and 8 channel relay module, TouchOSC apk for [Android](https://play.google.com/store/apps/details?id=net.hexler.lex), but is also available on [IoS](https://apps.apple.com/app/touchosc/id1569996730), TouchOSC Editor for
[Windows](https://hexler.net/touchosc#windows), [Mac](https://hexler.net/touchosc#mac) or [Linux](https://hexler.net/touchosc#linux), to create the template with the commands and [TouchOSC bridge](https://hexler.net/pub/touchosc/touchosc-bridge-1.7.3.150-win32.exe)

### Setup.
I use the [Arduino IDE 1.8.1](https://downloads.arduino.cc/arduino-1.8.1-windows.zip) to compile this code in arduino board, verification will display some warnings,
in my case did, but this will not prevent the code to work. You will need to design your own display with
the right commands in TouchOSC Editor to trigger the arduino ports, i highly recommend to use external power
supply to the relay module, otherwise can present malfunctioning such as high delay or even't work at all.

The button on the MIDI OSC should be configured as "/ard/relePin2", for example, the port configured in the OSC should be 9000.
