# Fli3d Hardware

## Overview

## ESP32 minikit MH-ET Live

Originally, I intended to use a Wemos D1 mini (ESP8266) microprocessor board as the core system for Fli3d, given its small size.  I however bumped into performance limitations when trying to acquire data from all sensors in parallel, and the ESP8266 has only one hardware serial port.  A second serial port had to be implemented in software, which added to the performance problems.

Also very small but much more powerful is the ESP32 minikit MH-ET Live board.  It looks very much like the D1 mini. A subset of its pins is even designed to be directly mapped to the D1 mini pinout.

![ESP32 minikit MH-ET Live](https://chiptron.cz/images/news/MH-ET_LIVE_D1_mini_ESP32/MH-ET_LIVE_D1_mini_ESP32_4.png)

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

The board costs less than 5 euros, and weighs only XXXX g.

## AI Thinker ESP32-CAM

This neat little board includes a 2 megapixel (1600x1200) OV2640 colour camera with lens, an ESP32 microcontroller, and an SD-card adapter.  It merely weighs 8.5g, and costs less than 5 euros.

![AI Thinker ESP32-CAM with OV2640](https://www.tinytronics.nl/shop/image/cache/data/product-2132/ESP32CAM_1-1000x1000.jpg)

It interfaces to the ESP32 minikit over the serial connection.  All acquired telemetry is exchanged in both directions, so that both units have the full telemetry to send over WiFi, for redundancy.  Telemetry and images are stored on the SD card.  The SD card can also contain a configuration file, which allows to override default WiFi settings.

The ESP32-CAM module allows the connection of an external WiFi antenna.  For this, it is however needed to unsolder and resolder a tiny SMD bridge connection on the board.  I attached a laptop WiFi antenna, but did not yet do the rerouting.  I intend to test whether the external antenna does yield a better WiFi range.

Note that the ESP32-CAM module is slightly more cumbersome to flash than other development boards.  It does not feature an USB connector, so the flashing needs to be done via an USB to serial converter.  It is also needed to ground GPIO0 during flashing, and unground the pin and press the reset button in order to run the firmware.  So that's a lot of small manipulations, especially if the serial interface needs to be rewired after flashing.  Also OTA update cannot be used, since the memory is needed for the images.  Still, one gets used to this.

The software was developed in Arduino IDE, and can be found in the following repository: https://github.com/jmwislez/fli3d-esp32cam 

A datasheet is available here: https://github.com/jmwislez/fli3d/blob/master/Hardware/ESP32-CAM%20microcontroller%20%2B%20camera/ESP32_CAM_V1.6.pdf

## NEO6MV2 GPS sensor
## MPU6050 accelerometer/gyroscope sensor
## BMP280 barometer sensor
## structure
