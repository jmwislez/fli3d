# Fli3d Hardware

## Overview

## ESP32 minikit MH-ET Live

Originally, I intended to use a Wemos D1 mini (ESP8266) microprocessor board as the core system for Fli3d, given its small size.  I however bumped into performance limitations when trying to acquire data from all sensors in parallel, and the ESP8266 has only one hardware serial port.  A second serial port had to be implemented in software, which added to the performance problems.

Also very small but much more powerful is the ESP32 minikit MH-ET Live board.  It looks very much like the D1 mini. A subset of its pins is even designed to be directly mapped to the D1 mini pinout.

![Wemos D1 mini (ESP8266)](https://hackerstore.nl/PDF2/WeMosMini.png)
![ESP32 minikit MH-ET](https://chiptron.cz/images/news/MH-ET_LIVE_D1_mini_ESP32/MH-ET_LIVE_D1_mini_ESP32_4.png)

This board is connected to the other Fli3d subsystems as follows:
  - powered at 5V by the 134N3P battery charger
  - serial connection to ESP32CAM on pins IO1 (TX) and IO3 (RX) at 115200 baud
  - serial connection to NEO6MV2 GPS receiver on pins IO17 (TX) and IO16 (RX) at 57600 baud
  - I2C bus to MPU6050 accelerometer/gyroscope and BMP280 pressure sensor on pins IO21 (SDA) and IO22 (SCL)
  - separation detection wire on pin IO19 (GND is mated, open is unmated)
  - WL102-341 radio transmitter with OOK signal on pin IO26
Note that not any combination of pins works, as there seem to be hidden conflicts between functionality.  In this configuration, all subsystems seem to be working well and independently.
  
The software was developed in Arduino IDE, and can be found in the following repository: https://github.com/jmwislez/fli3d-esp32 

I defined a basic 3D model of the board in FreeCAD: https://github.com/jmwislez/fli3d/blob/master/Hardware/ESP32%20mini%20kit/ESP32minikit.FCStd

Some more details on this board's hardware: https://riot-os.org/api/group__boards__esp32__mh-et-live-minikit.html

## ESP32CAM
## GPS
## accelerometer
## barometer
## structure
