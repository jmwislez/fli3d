# Fli3d Chicken - flight report

## Main flight characteristics

Fli3d Chicken was the maiden flight of the Fli3d electronics.  It was a weather balloon flight.

The flight was hit by many problems. Network problems at the launch site prevented check-out and configuration of Fli3d Chicken, and due to this the camera was not activated during flight.  During the flight, the electronics and software performed moderately well.  When the balloon 
reached 37km and burst (expected behaviour), Fli3d Chicken got ripped off its hook, and came down in freefall.  It survived the crash very well: all electronics is still working.  

Despite the problems, a load of interesting engineering data and experience were gathered, that will significantly contribute to improving the Fli3d system.  This page collects and presents all this experience. 

| Event | Details |
| - |- |
| Platform | IRM/KMI weather balloon<br />ON4IR-3 tracker |
| Launch   | 25/09/2022 15:18:31 UTC<br />IRM/KMI Uccle, Belgium |
| Burst    | 25/09/2022 17:26:35 UTC<br />at 37085 m altitude<br />Rupture from parachute line and start of freefall, with speeds up to 700 km/h |
| Crash    | 25/09/2022 17:39:58 UTC<br />in a field near Eppe-Sauvage, France (76.86 km distance), at 65 km/h |
| Duration | Ascent: 2h08m03s<br />Descent: 13m25s<br />Total: 2h21m28s |

## Pre-flight preparations

### Set-up and operational approach

The set-up consisted of a laptop, connected to internet through a smartphone access point, and providing a "Fli3d" private network access point for pre-flight communication with Fli3d Chicken using the MyPublicWifi software.

A [checklist for launch preparations](https://github.com/jmwislez/fli3d/blob/master/Fli3d%20Chicken/Fli3d%20Chicken%20procedure.xlsx) was prepared (dry-run at home before).

### Known issues

The Fli3d software/system is still under development, and by the time of the launch, the following issues were known (and all hit):

- intermittently, GPS module would not lock
- Real-Time-Clock module (last minute addition) on ESP32CAM not tested
- Spontaneous reboots happen occasionally
- Occasional frying of SD cards
- FTP to ESP32CAM flash filesystem unstable

### Pre-flight anomalies

One of the very first steps, starting the Yamcs server for Telecommand/Telemetry communication with Fli3d, failed.  Afterwards, this turned out to be the consequence of a hidden and unnecessary network dependency from my home network.  It has been recognized as an issue to be fixed in Yamcs, and a work-around would have been activating my VPN connection to home.  But I did not thinks of that ...

Without Yamcs, any verification of Fli3d Chicken and any configuration commanding was impossible.  I could only confirm through MyPublicWifi that both ESP32 were connected to the WiFi, hence active.

Mandatory commanding was to set both ESP32 from "checkout" to "nominal" operations mode, and to freeze them in that mode in case of spontaneous reboots.  For ESP32 this just sets some internal processing of acquired data, but for the ESP32CAM, this starts the camera frame grabbing.  Crucial ...

The effect of the freezing command is to create an "opsmode.lock" file on the filesystem, with one 0x02 character, indicating a reboot in mode 2 (nominal).  So I created such file (with help of my radioamateur friends), and put it on ESP32 (flash file system over FTP) and ESP32CAM (physically on SD card).

The ESP32CAM SD card just fried at that moment, so I had to take a new one.  After the faulty SD card, I also had to reboot my computer for the new SD to work.  At the last moment, I also added the latest configuration files on the SD card.  The latter I should not have done ...  These configuration files tell ESP32CAM to look for the "opsmode.lock" on the flash file system, while the default is the SD card.  Hence, during flight it did not find the file, and ESP32CAM stayed in "checkout" mode, without taking pictures ...

Also, with rebooting the laptop and not the MyPublicWifi software, the ESP32s could not acquire an NTP time reference before launch.

### Handover and launch

Due to the anomalies closure of the Fli3d Chicken box was done very fast and without checks, since there was a crowd waiting for the now delayed launch.  The ON4IR-3 tracker was taped to Fli3d Chicken with duct tape, and the rope of the balloon was knot to the hook on Fli3d Chicken.  No time for configuration pictures.

I got the occasion to explain Fli3d Chicken to the audience, in French and in Dutch, and let Fli3d rise in the blue-patched sky ... [[Facebook video](https://www.facebook.com/gaetan.horlin/videos/755262105775191)]

## Flight

The ON4IR-3 tracker, provided by the radio amateur community, worked flawlessly throughout the whole flight, and allowed for easy remote tracking and real-time landing site prediction.  

The timestamping of the events below is performed by correlation of ON4IR-3 GPS timestamp and events with ESP32 relative timestamps and measurements.  A deviation of up to 10 seconds is possible.

| Time in flight                                 | Timestamp (UTC)                                              | Altitude                                       | Event / comments                                             |
| ---------------------------------------------- | ------------------------------------------------------------ | ---------------------------------------------- | ------------------------------------------------------------ |
| -0:06:25                                       | 25/09/2022 15:12:06                                          | 100 m                                          | Power-up of Fli3d Chicken for flight                         |
| 0:00:00                                        | 25/09/2022 15:18:31                                          | 100 m                                          | Balloon release                                              |
| 0:06:50<br />0:20:11<br />0:32:59<br />0:45:47 | 25/09/2022 15:25:20<br />25/09/2022 15:38:42<br />25/09/2022 15:51:29<br />25/09/2022 16:04:17 | 2050 m<br />5704 m<br />8895 m<br />12261 m    | ESP32 reboots                                                |
| 0:55:08                                        | 25/09/2022 16:13:38                                          | 14708 m                                        | BMP280 sensor stops                                          |
| 0:59:24<br />1:16:24<br />1:33:15<br />1:49:24 | 25/09/2022 16:18:16<br />25/09/2022 16:35:21<br />25/09/2022 16:52:16<br />25/09/2022 17:08:30 | 16012 m<br />20922 m<br />26205 m<br />31600 m | ESP32 reboots                                                |
| 2:08:03                                        | 25/09/2022 17:26:35                                          | 37085 m                                        | Balloon burst, rip-off of hook, and ESP32 reboot             |
| 2:21:28                                        | 25/09/2022 17:39:58                                          | 186 m                                          | Crash landing of Fli3d Chicken and ON4IR-3 at 65 km/h, after freefall |
| 2:26:27                                        | 25/09/2022 17:44:57                                          | 186 m                                          | ESP32 reboot                                                 |
| 2:43:53                                        | 25/09/2022 18:02:23                                          | 186 m                                          | Pick-up by recovery team                                     |
| 2:45.38                                        | 25/09/2022 18:04:09                                          | 186 m                                          | ESP32 reboot                                                 |
| 2:55:41                                        | 25/09/2022 18:14:12                                          | 186 m                                          | Deactivation by recovery team                                |

## Post-landing videos

![Fli3d Chicken/VID-20220925-WA0020.mp4](https://raw.githubusercontent.com/jmwislez/fli3d/master/Fli3d%20Chicken/VID-20220925-WA0020.mp4)

![Fli3d Chicken/VID-20220925-WA0021.mp4]([https://github.com/jmwislez/fli3d/blob/master/Fli3d%20Chicken/VID-20220925-WA0021.mp4](https://raw.githubusercontent.com/jmwislez/fli3d/master/Fli3d%20Chicken/VID-20220925-WA0021.mp4))

## System performance assessment

| **Subsystem**             | **Lessons**                                                  | **Suggestion for next version**                              |
| ------------------------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| **Network**               | Ok! <br />Worked out of the box and connection with 2 ESP32s was visible shortly after start-up. | MyPublicWifi is ideal for pre-launch configuration and check-out, and for quick set-up in a foreign environment.  For in-flight data acquisition, the range of a MyPublicWifi is likely too limited and real network infrastructure is preferred. |
| **Yamcs**                 | Hung during startup, waiting for (unneeded) home network.  Confirmed bug in Yamcs.<br />This problem prevented check-out and configuration of Fli3d Chicken before flight. | Update yamcs server after bug fix. <br />Try connecting to Home VPN if re-occurrence.<br />Yamcs has always been very stable though, so this was just Murphy. |
| **Housing**               | Excellent thermal isolation: minimal internal temperature was -21.5 degC, while external temperature at -40 degC or maybe worse.  <br />Excellent shock protection:  electronics operations continued uninterrupted at 65 km/h impact, after 37km freefall.  All electronics survived crash.<br />Attachment hook got loose at burst (aluminium tape ruptured). | Make inner volume slightly larger for easier harness accommodation.<br />Anchor the hook to the structure, and not only to the easily shearable aluminium tape layer.  <br />Potentially add an elastic, to reduce shock on hook at burst. |
| **Battery**               | Ok!  <br />Type: POWERFULL 708960 Li-Ion Batery Power Bank - 5000 mAh (bought at Colruyt)<br />Survived temperatures down to -21.5 degC.  Provided power throughout the full flight, and still full at 3/4 after recovery. | Spare power is available for additional electronics or heaters.  <br />Smaller/lighter battery can be considered. |
| **ESP32**                 | Worked throughout the whole flight.<br />Rebooted 12 times over flight, at relatively regular interval, so likely software-induced rather than hardware/thermal problems.<br />![Fli3d Chicken/ESP32_millis.png](https://github.com/jmwislez/fli3d/blob/master/Fli3d%20Chicken/ESP32_millis.png) | Debug software for reboot cause.<br />Improve resilience/continuity in case of reboot. |
| **BMP280**                | Good temperature and pressure measurements down to -40 degC / 134 mbar.  At the end of the measurements, temperatures were stable, fluctuating between -36.5..-40 degC. <br />![Fli3d Chicken/BMP280_temperature.png](https://github.com/jmwislez/fli3d/blob/master/Fli3d%20Chicken/BMP280_temperature.png)<br />![Fli3d Chicken/BMP280_pressure.png](https://github.com/jmwislez/fli3d/blob/master/Fli3d%20Chicken/BMP280_pressure.png)<br />Worked properly after a post-landing reboot. | Datasheet range of BMP280 is 300..1100 hPa, -40..+85 degC, so malfunction at the observed pressure/temperature is not unexpected.<br />Suggest to put BMP280 inside the housing for pressure measurements, and use an external passive temperature sensor (PT100 or similar). |
| **MPU9250**               | Worked properly throughout the full flight.<br />Acceleration sensor data clearly show the different phases, but further interpretation is difficult.  During the freefall, the accelerometer gets saturated occasionally, while its range was set to +/- 16G.  The ride down was bumpy ...  <br />![Fli3d Chicken/MPU9250_accel_x.png](https://github.com/jmwislez/fli3d/blob/master/Fli3d%20Chicken/MPU9250_accel_x.png)<br />Gyroscope date show mainly rotations around the X-axis (vertical axis of Fli3d Chicken) during ascent, and random during descent.  Rotations of 100-200 deg/s are common, so many pictures would have been blurry. At the highest altitudes, the probe clearly stabilises.  Y and Z axes are more stable.  The head-down orientation of the crashed Fli3d Chicken is visible in the data.<br />![Fli3d Chicken/MPU9250_gyro_x.png](https://github.com/jmwislez/fli3d/blob/master/Fli3d%20Chicken/MPU925gyro_x.png)<br />Instantaneous absolute orientation of Fli3d Chicken could be derived from the magnetometer, but without camera this information is of limited value. | Think of stabilisation means for imaging: mechanical/electronic stabilizers, or simply fins.<br />Check whether one more significant number is possible in the magnetometer telemetry. |
| **GPS**                   | The GPS never locked on a signal during flight.  From the recovery video, it is visible that there is no GPS light red flashing, so the lack of lock is at hardware level.  Intermittent unability to lock has been regularly observed during development and is not yet understood.  <br />The very same GPS board has been observed to work since (in open box configuration).<br />Without GPS data, ESP32 had no absolute time reference during flight. Hence, all events needed to be correlated post-flight. | Assess why GPS  sometimes does not lock.  Assess whether the aluminiumless window for the antenna is sufficiently large, whether there is a preferred antenna orientation, if the antenna connector always properly connects.<br />Consider external antenna. |
| **DHT22**                 | Worked flawlessly during the flight, and proved good performance of the thermal isolation.  The temperature initially decreases during freefall, which is likely due to the breaching of the thermal isolation with the rip-off of the hook.<br />![Fli3d Chicken/ESP32_temperature.png](https://github.com/jmwislez/fli3d/blob/master/Fli3d%20Chicken/ESP32_temperature.png) | Indeed interesting to include an internal temperature sensor (last minute addition) |
| **ESP32CAM**              | **TBW**                                                      |                                                              |
| **Camera**                | No pictures due to hack not working …<br />Camera worked properly post-flight. |                                                              |
| **SD card**               | Worked well during flight (for ESP32CAM TM storage, no images)<br />Fried one SD just before flight. | Assess why so often an SD card is fried                      |
| **RTC**                   | **TBW**                                                      |                                                              |
| **In-flight TM archive** | CCSDS TM archive present (recovered from ESP32 FS through FTP and ESP32CAM SD physically) and error-free, but no time information available.<br />Not all status messages seem to have been recorded. | Include replay functionality in software<br />Introduce secondary header with absolute timestamps<br />Assess completeness of archive. |
| **Operational**           | Time-pressured after anomalies, let go for flight without confidence in readiness. | Dry-run on field.  <br />Develop "what-if" for the full preparation procedure.  <br />Do initial check-out  hours before, even if done at home, and foresee full development and checkout  environment on-site. |
| **Software**              | The ESP32/ESP32CAM software performed well throughout flight, with the following observations:<br />* ESP32 rebooted at almost regular intervals, hinting a software problem<br />* Commanding is mandatory  to start acquisition, and for checkout<br />* The hack worked for ESP32 (moved  to "nominal" opsmode after each reboot)<br />* The hack did not work for ESP32CAM (stayed in "checkout" opsmode after each reboot)<br />* There was no way to start the camera without commanding<br />* The use of SD or FS is fully configurable, which adds possibility for configuration errors, and prevented the hack to work.  In general, the software may be too configurable,  which can lead to errors<br />* FTP not working for accessing ESP32CAM SD/FS | Debug reboots (when permanently disconnected from WiFi?)<br />Think of simple possibilities to confirm proper operations and configure minimal flight configuration without TC/TM<br />Cleanup SD/FS, and  think of SD/FS data accessibility |
| **ON4IR-3**               | Not part of Fli3d Chicken.  Worked flawlessly, and was invaluable in post-processing the data.<br />ON4IR-3 acquired GPS positioning and altitude data, as well as horizontal and vertical velocity.<br />The flight track (blue) shows how the balloon flew to the north of France.  Burst was at the last sharp turn in the track.  Details of the track just before landing show the swirling trajectory of Fli3d Chicken.<br />![Fli3d Chicken/all_tracks.jpg](https://github.com/jmwislez/fli3d/blob/master/Fli3d%20Chicken/all_tracks.jpg)<br />![Fli3d Chicken/swirl_track.jpg](https://github.com/jmwislez/fli3d/blob/master/Fli3d%20Chicken/swirl_track.jpg)<br />The figure below shows the correlation between the GPS altitude (blue) and the pressure/temperature derived altitude (orange).<br />![Fli3d Chicken/altitude.png](https://github.com/jmwislez/fli3d/blob/master/Fli3d%20Chicken/altitude.png)<br />The vertical velocity graph below shows a steady upward velocity of on average 4.77 m/s.  After burst, freefall goes initially up to 195 m/s (700 km/h)!   After that, it is slowed down by air friction up to 18 m/s (65 km/h).  Signal is lost 20 seconds before the crash (no line-of-sight).  ONI4R-3 was still working after the crash.<br />![Fli3d Chicken/velocity.png](https://github.com/jmwislez/fli3d/blob/master/Fli3d%20Chicken/velocity.png) | This module saved the mission!                               |


## Acknowledgements

Many thanks to IRM/KMI for this unique and amazing flight opportunity!  

I'm also very grateful to the very kind radio amateur team, for providing the ON4IR-3 tracker (with batteries!), the support before launch, the tracking infrastructure, the field recovery and shipping of Fli3d Chicken, and the very careful documenting of each step with nice videos.  You guys are delightful!  Special thanks to Manoel, Benoit and Olivier.
