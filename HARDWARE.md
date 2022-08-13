# Fli3d Hardware

## Overview
<img src="https://github.com/jmwislez/fli3d/blob/master/Configuration/fli3d%20block%20diagram.png">
<img src="https://github.com/jmwislez/fli3d/blob/master/Hardware/Structure/fli3d%20closed%20v4.2.png" width="600px">
<img src="https://github.com/jmwislez/fli3d/blob/master/Hardware/Structure/fli3d%20full%20v4.2%20-%201.png" width="600px">
<img src="https://github.com/jmwislez/fli3d/blob/master/Hardware/Structure/fli3d%20full%20v4.2%20-%202.png" width="600px">

## ESP32 minikit MH-ET Live

Originally, I intended to use a Wemos D1 mini (ESP8266) microprocessor board as the core system for Fli3d, given its small size.  I however bumped into performance limitations when trying to acquire data from all sensors in parallel, and the ESP8266 has only one hardware serial port.  A second serial port had to be implemented in software, which added to the performance problems.

Also very small but much more powerful is the ESP32 minikit MH-ET Live board.  It looks very much like the D1 mini. A subset of its pins is even designed to be directly mapped to the D1 mini pinout.

<img src="https://chiptron.cz/images/news/MH-ET_LIVE_D1_mini_ESP32/MH-ET_LIVE_D1_mini_ESP32_4.png" width="800px">

This board is connected to the other Fli3d subsystems as follows:
  - powered at 5V by the 134N3P battery charger
  - serial connection to ESP32CAM on pins IO1 (TX) and IO3 (RX) at 115200 baud
  - serial connection to NEO6MV2 GPS receiver on pins IO17 (TX) and IO16 (RX) at 57600 baud
  - I2C bus to MPU6050 accelerometer/gyroscope and BMP280 pressure sensor on pins IO21 (SDA) and IO22 (SCL)
  - separation detection wire on pin IO19 (GND is mated, open is unmated)
  - WL102-341 radio transmitter with OOK signal on pin IO26
Note that not any combination of pins works, as there seem to be hidden conflicts between functionality.  In this configuration, all subsystems seem to be working well and independently.
  
The software was developed in Arduino IDE, and can be found in the following repository: https://github.com/jmwislez/fli3d-esp32 

I defined a basic 3D model of the board in FreeCAD: https://github.com/jmwislez/fli3d/blob/master/Hardware/Electronics/ESP32%20mini%20kit/ESP32minikit.FCStd

Some more details on this board's hardware: https://riot-os.org/api/group__boards__esp32__mh-et-live-minikit.html

The board costs less than 2 euros, and weighs only 8 g.

## AI Thinker ESP32-CAM

This neat little board includes a 2 megapixel (1600x1200) OV2640 colour camera with lens, an ESP32 microcontroller, and an SD-card adapter.  It merely weighs 8.5g, and costs less than 5 euros.

<img src="https://www.tinytronics.nl/shop/image/cache/data/product-2132/ESP32CAM_1-1000x1000.jpg" width="400px">

The camera is of course not very fast, and wifi transmission and storage further slow it down.  At low resolution, frame rates can be 25 Hz or higher.  At full resolution, this is rather 1 Hz.

The board interfaces to the ESP32 minikit over the serial connection.  All acquired telemetry is exchanged in both directions, so that both units have the full telemetry to send over WiFi, for redundancy.  Telemetry and images are stored on the SD card.  The SD card can also contain a configuration file, which allows to override default WiFi settings.

The ESP32-CAM module allows the connection of an external WiFi antenna.  For this, it is however needed to unsolder and resolder a tiny SMD bridge connection on the board.  I attached a laptop WiFi antenna, but did not yet do the rerouting.  I intend to test whether the external antenna does yield a better WiFi range.

Note that the ESP32-CAM module is slightly more cumbersome to flash than other development boards.  It does not feature an USB connector, so the flashing needs to be done via an USB to serial converter.  It is also needed to ground GPIO0 during flashing, and unground the pin and press the reset button in order to run the firmware.  So that's a lot of small manipulations, especially if the serial interface needs to be rewired after flashing.  Hence OTA update is strongly preferred, using "minimal SPIFFS" partitioning.

Most ESP32 connectivity is in use by the camera and SD card module, so do not expect to squeeze any more out of this module.  There is even a double use of pin GPIO 4, which makes the on-board flashlight blink when addressing the SD card.  This is annoying, but unavoidable by hardware design.  

The software was developed in Arduino IDE, and can be found in the following repository: https://github.com/jmwislez/fli3d-esp32cam 

A schematic of the board is available here: https://github.com/jmwislez/fli3d/blob/master/Hardware/Electronics/ESP32-CAM%20microcontroller%20%2B%20camera/ESP32_CAM_V1.6.pdf

## NEO6MV2 GPS sensor

It is astonishingly easy and cheap to integrate GPS functionality.  The NEO6MV2 board has all you need and can provide up to 16 readings per second, for slightly more than 6 grams (including antenna) and slightly more than 3 euros.

The GPS module is connected to ESP32 minikit over serial at 57600 baud.  Default speed is 9600 baud.  I tried 115200 baud too, but sometimes the serial line would not synchronize at that speed.

I defined a basic 3D model of the board in FreeCAD: https://github.com/jmwislez/fli3d/blob/master/Hardware/Electronics/NEO6MV2%20gps/neo6mv2.FCStd

The user manual is here: https://github.com/jmwislez/fli3d/blob/master/Hardware/NEO6MV2%20gps/U-blox-6-Receiver-Description-Including-Protocol-Specification.pdf

## MPU6050 accelerometer/gyroscope sensor

The MPU6050 provides a 6 DOF motion sensor over an I2C bus.  It provides passthrough functionality, which is used to connect the BMP280 sensor.  Initially I had hoped to use the sensor for internal navigation, i.e. determine position, speed, and orientation by integrating the acceleration/gyroscope readings.  The sensor is far from being sufficiently precise for this: it is even non trivial to get some usable data out of it.  There is a Digital Motion Processor on-board, but this functionality was hard to use, looked unstable to me, and did not help me to get what I needed.  Hence, I ended up doing my own naive calibration, which for now is still worthless.   

In a next version of Fli3d, it's probably worth looking at MPU9255, which also includes a 3D compass and can therefore more reliably provide orientation.  That board is slightly bigger, and would require a mechanical redesign of the Fli3d structure.

Mechanically, the board is mounted so that the sensor is on the rocket's central axis.  The X/Y/Z axes of the sensor correspond to Z/X/Y axes of the rocket.

The documentation of the board is extensive (https://github.com/jmwislez/fli3d/tree/master/Hardware/Electronics/MPU6050%206DOF%20motion%20sensor/), but lacks precision to harvest the full power of the chip.

## BMP280 barometer sensor

The BMP280 is a small, simple, but neat little board with a very sensitive barometer and thermometer, which can be used to determine altitude changes.  The resolution of altitude measurements is typically better than 1 meter!  

The board is connected over I2C, as an auxiliary board of the MPU6050.

The user manual of the chip is here: https://github.com/jmwislez/fli3d/blob/master/Hardware/Electronics/BMP280%20pressure%20sensor/BST-BMP280-DS001-11.pdf

## WL102-341 433MHz radio transmitter and antenna

Not knowing the stability of the WiFi connection in flight, I decided to add a 433 MHz transmitter on board, for transmission of a summary of the telemetry.  Moreover, this could serve as a beacon for Doppler measurements, which could later be correlated to the determined flight path.  This is not done yet.

This is the only board in the stack that needs to be powered at 3.3V instead of 5V.  This power is provided by the ESP32 minikit board.

The signal feeding the transmitter is digital output IO26 of the ESP32 minikit board, and this OOK (on/off keying) signal is then transmitted as is by switching the transmitter on and off.

The antenna for the 433 MHz is screwed on top of the rocket, and also holds the fairing in place.

## Battery and 134N3P battery charger

The on-board battery is a 300 mAh 3.7V Li-ION battery.  This provides an autonomy of roughly 20 minutes for a fully active system.  

The battery is not directly driving the Fli3d electronics, but connected to a 134N3P battery charger.  This is basically a circuit as used in power banks.  It converts the battery output to a steady 5V, it allow charging the battery, and while connected for charging, 5V is neatly provided.  Hence, it allows for tethered operations, and just before launch the power tether can be detached, and Fli3d is seamlessly on autonomous power with a fully charged battery.

Mechanically, the type A USB connector on the board needs to be unsoldered.  

## Wiring

There is not much physical space available for wire routing or connection.  Originally, I intended to use directly soldered wire connections for reliability, and to unsolder the headers where the boards came with headers pre-mounted.  The latter was not easy given my limited soldering skills and equipment, so I decided to keep the headers and use a combination of header sockets and direct soldering.

Friction connectors without latching do not perform well under mechanical stress, and the assembly is fragile and hard to repair.  Hence, the haressing is something that could definitely be improved.

Two rows of 8-pin female 2.54mm sockets are used for VCC and GND distribution.

An overview of the wiring connections is given below.

<img src="https://github.com/jmwislez/fli3d/blob/master/Hardware/Wiring/Fli3d%20wiring.png" width="800px">

## Structure

The Fli3d structure was designed using FreeCAD, and is 3D printed with PLA on a Prusa i3 clone printer.  Total mass is 30 grams.  Assembly is mainly done with M2.5 screws and contact glue.

<img src="https://github.com/jmwislez/fli3d/blob/master/Hardware/Structure/fli3d%20structure%20v4.2%20-%201.png" width="600px">
<img src="https://github.com/jmwislez/fli3d/blob/master/Hardware/Structure/fli3d%20structure%20v4.2%20-%202.png" width="600px">
<img src="https://github.com/jmwislez/fli3d/blob/master/Hardware/Structure/fli3d%20v4.2%20fairing.png" height="400px">

The FreeCAD design files are here: https://github.com/jmwislez/fli3d/tree/master/Hardware/Structure

Each structural element coloured differently needs to be printed separately.
