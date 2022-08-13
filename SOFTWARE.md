# Fli3d software

The software for Fli3d is developed in Arduino IDE.  It runs on two ESP32 boards (https://github.com/jmwislez/fli3d-esp32.git and https://github.com/jmwislez/fli3d-esp32cam.git), using a common library (https://github.com/jmwislez/fli3d-lib.git).

## Initialisation

The `setup()` part of the sketch initializes all services at power on:

<img src="https://github.com/jmwislez/fli3d/blob/master/Software/Fli3d%20initialisation.png">

A typical TM reporting of the initialisation is shown below:

<img src="https://github.com/jmwislez/fli3d/blob/master/Software/Fli3d%20ESP32-log.png">
<img src="https://github.com/jmwislez/fli3d/blob/master/Software/Fli3d%20ESP32cam-log.png">

## Loop

The `loop()` part of the sketch performs the measurements and maintanance tasks.  This is shown below for the ESP32 board:

<img src="https://github.com/jmwislez/fli3d/blob/master/Software/Fli3d%20ESP32%20loop.png">

## Telemetry transmission

Telemetry can be sent over different channels:
* CCSDS packets over WiFi/UDP to Yamcs ground station
* CCSDS packets to local file system (LittleFS flash on ESP32, and SD-card or LittleFS flash on ESP32cam) for post-flight recovery and in-flight buffering
* JSON packets on SD-card (on ESP32cam) for post-flight recovery 
* CCSDS or JSON packets over Serial to the other on-board ESP32 (or for in-development debug)
* JSON packets over WiFi/UDP to a debug interface
* a summary CCSDS packet over 433 MHz/OOK radio transmission

There is also a routing table, allowing to define for each individual packet type (APID) whether it is or is not routed on a particular channel.

<img src="https://github.com/jmwislez/fli3d/blob/master/Software/Fli3d%20TM%20routing.png">

