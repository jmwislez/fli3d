# The Fli3d Project

## Purpose

Fli3d (pronounced "flight") is a project by Jean-Marc Wislez for the 2020 edition of the Belgian "Fri3d Camp" hacker event. Its purpose is to develop and launch an ESP32 payload on top of a microrocket.  And this payload needs to be as cool as possible ...

The name is obviously derived from "Fri3d Camp", and hints to the "Chinese electronics" used to build it.

I have been working in the space industry for more than 20 years now, and this included design, building, testing and operations of payloads on Shuttle missions and ISS.  Basically I used this experience and the typical approaches here, but doing everything myself instead of collaborating in large teams.

## Overview

The Fli3d payload has roughly the size of a toilet paper roll, and weighs less than 100g.  Hardware costs for one unit are below 25 euros.  The payload is intended for launch on a microrocket with minimally a B-motor.  The payload contains the following:
  - a 3D-printed structure and fairing
  - an ESP32 minikit MH-ET microprocessor board, running custom software (developed in Arduino IDE) to control all Fli3d subsystems and transmit live telemetry and receive commands over WiFi
  - an MPU6050 accelerometer/gyroscope sensor unit for determining accelerations and orientation
  - a BMP280 barometric sensor for determination of the rocket altitude
  - a NEO6MV2 GPS module, for determination of position and speed
  - an ESP32CAM module with an OV2640 camera and SD-card module, for image acquisition, in-flight image and telemetry storage, and live transmission of telemetry and images over WiFi
  - a WL102-341 433 MHz radio transmitter module, for in-flight transmission of selected telemetry
  - a 240 mAh Li-ION battery for standalone autonomy of 20 (TBC) minutes, with 134N3P charger for tethered operation or pre-launch charging
  - separation detection, for detection of opening of parachute compartment
  
All flight data is to be monitored live on a ground computer running Yamcs (open source software developed for ISS payload and satellite operations), and to be retrievable after flight, both physically and through file transfer.

## Flights

To date, the payload has not flown yet.  It is hoped to do one or more test flights before Fri3d Camp in August 2020, and one or more demo flights at Fri3d Camp.

Each flight will be designated through a successive starting letter, and have a corresponding name (another cheesy reference to the Chinese electronics used):
  - Fli3d Aubergine 
  - Fli3d Banana 
  - Fli3d Chicken
  - Fli3d Dumplings
  - Fli3d Eggs
  - Fli3d Fries
  - ...
  - Fli3d Rice

## Available documentation and repositories

  - https://github.com/jmwislez/fli3d :
    - Project introduction
    - Hardware design files
    - Yamcs (ground segment software) configuration
  - https://github.com/jmwislez/fli3d_esp32 :
    - Arduino IDE code for fli3d ESP32 MH-ET LIVE MiniKit
  - https://github.com/jmwislez/fli3d_esp32cam :
    - Arduino IDE code for fli3d ESP32-CAM
  - https://github.com/jmwislez/fli3d_lib :
    - Common Arduino IDE code for fli3d ESP32 MH-ET LIVE MiniKit and ESP32-CAM
