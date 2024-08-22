# Fli3d Aubergine – flight report
## Main flight characteristics
Fli3d Aubergine was the first flight of the Fli3d payload on a microrocket.  It was the second flight of the Fli3d electronics. [Click here](https://github.com/jmwislez/fli3d/blob/master/README.md#flights) for an overview of the flights and their naming.

| Characteristic | Value |
| - | - |
| Launch date / time | 18-Aug-2024 12:41 CEST |
| Launch location | De Kluis, Sint-Joris-Weert, Belgium |
| Height (without antenna) | 50 cm |
| Height (with antenna) | 65 cm |
| Diameter | 35 mm |
| Mass | 145 g |
| Motor | C6-3 |
| Parachute | 45 cm by Klima |
| Fin: | 3D printed (3) |
| Stability number | 4.94 calibre |

[[Fli3d Aubergine photo album](https://photos.app.goo.gl/HriTFwFs2qNNNqe7A)]

## Ground segment
The ground segment set-up consisted of a Windows 10 laptop running [Yamcs 5.9.8](https://yamcs.org), a NodeMCU ESP8266 microcontroller running [fli3d-rx433](https://github.com/jmwislez/fli3d_rx433) for translating the telemetry packets received over radio (433.700 MHz) to UDP packets towards Yamcs, and a WRT-54GL router for creating a private 2.4 GHz Wi-Fi network with fixed IP address assignments for the rocket, laptop and radio receiver.

## System status before launch
The original Fli3d Payload [as described here](https://github.com/jmwislez/fli3d/blob/master/HARDWARE.md#fli3d-hardware) was flown.

The rocket software was way more stable than during Fri3d Camp 2022.  This is mainly thanks to some bug fixing, code clean-up to eliminate all compilation warnings for the Fli3d native code, and porting to the latest ESP32 core (v3.0.4) and libraries.  The software version was as below (tagged "aubergine" in repositories):

| Subsystem | Software version |
| - | - |
| ESP32 | [fli3d_esp32](https://github.com/jmwislez/fli3d_esp32/) v1.2.0 dated 2-Aug-2024 <br /> [fli3d_lib](https://github.com/jmwislez/fli3d_lib/) v1.2.2 dated 13-Aug-2024 |
| ESP32CAM | [fli3d_esp32cam](https://github.com/jmwislez/fli3d_esp32cam/) v2.2.0 dated 2-Aug-2024 <br /> [fli3d_lib](https://github.com/jmwislez/fli3d_lib/) v1.2.2 dated 13-Aug-2024 |

The only subsystem not working was the NEO6mv2 GPS receiver, that would not lock for unknown reasons.  This is an intermittent problem which I did not yet try to debug.  It is possibly linked to the positioning of the GPS antenna too close to other electronics (though it used to mostly work in the past).

The final assembly of the payload and rocket were achieved only just before flight. I had no time to do any further testing or preparations.  

Near the launch site I started all systems, checked system health and communication with the system.  All were as expected, though I found later that no packets were being received over 443.700 MHz radio. I sent the command to start the picture acquisition and brought the rocket to the launch ramp some 15 meters from there.

## Launch and Flight
The rocket was launched in between a series of smaller children’s rockets, in the idea to attempt a reflight with a stronger motor towards the end of the launch campaign.  I gave a short explanation, unplugged the tethering, installed the rocket on the launch platform and ignited the wick. 

The rocket left the launch pad properly and had a stable flight, which was a great relieve given its mass and top-loading.  It soon started flying much more horizontally than the smaller microrockets that day and had its culmination and separation above the surrounding woods instead of above the grass terrain. Separation was clearly visible, but the parachute could not be observed to deploy before visual contact was lost behind the trees.

The reason for the horizontal flight is twofold.  With the weight of the rocket, the launch pad rod bent, which accounted for a larger launch pitch than the smaller rockets.  The main factor is however that I designed the rocket to be significantly “overstable”, in fear of instability when leaving the launch rod.  With this feature, the rocket has a strong tendency to orient itself towards the wind, which is horizontal. 

## Recovery
Despite searching attempts, the rocket could not be found back after flight.  The search area was too large, with large trees and brambles, with no visual hint on where to concentrate the search.
[map]

## Telemetry analysis
[screenshot]
Yamcs performed very well, and properly recorded all telemetry received.  From this, the following can be observed:
*	The rocket systems are booted at 10:32:17 UTC. All systems are nominal during the preparation phase, with the exception of known anomalies.
*	The camera starts acquiring at 10:36:42 UTC.
*	When taking the rocket to the launch pad, the quality of the Wi-Fi connection decreases, and packets are lost.  The 2.4 GHz Wi-Fi bands at Fri3d Camp are significantly overloaded and they perturbed my private network.  The 433 MHz transmission does not seem to have worked, which I failed to notice during check-out.
*	The moving of the rocket is visible from accelerometer data when I do the explanation.  
*	At 10:40:16 UTC, I untethered the rocket from the battery pack.  Both ESP32 in the rocket reboot due to this, very likely following a brownout detection (temporary low voltage).  I had seen this behaviour occasionally 2 years ago but forgot about it.
*	With the Fli3d Wi-Fi basestation drowning in the Fri3d Camp radio smog, the rocket did not connect back to the network and no further packets are received over Wi-Fi.  
*	With the reboot, the ESP32CAM camera is out of nominal mode, and thus stops taking pictures.  The camera was thus (again!) not working during the flight.  
*	With the reboot, the ESP32 altitude meter based on atmospheric pressure is in calibration status, and thus does not translate pressure changes in altitudes.
*	Three loose telemetry packets are then received over the 433.700 MHz radio channel, showing a proper reboot of all systems, but without Wi-Fi connection.
*	According to the datestamp of a picture taken by Jan De Bleser, the launch is at 12:41 local time, 10:41 UTC.
*	To my surprise, the telemetry archive contains a last packet received at 10:44:28 UTC, by when the rocket has landed already.  The telemetry does not contain much useful data, but it shows a static rocket with separation activated!  So the rocket still worked after landing, and 433.700 MHz radio did work over a longer distance (likely 100-200m).  The radio environment was just too noisy to receive more packets.
With the rocket unrecovered and Wi-Fi contact lost, the onboard telemetry could not be retrieved.  If the rocket is found by accident and returns to me by miracle, it may still be recoverable.
[graphs of TM]

## Lessons Learnt
I compiled a detailed list of lessons learnt to guide the design of Fli3d Payload v2 towards future flights, but these are the main ones:
* The main lesson I learnt is that for achieving overall results, all aspects of the mission deserve attention.  I launched a pretty functional payload, but with too many uncertainties or improvisation on many other aspects.
* I should redesign the rocket length and fins to resolve the overstability.
* The only way to have reliable radio communication at Fri3d Camp is to migrate to 5 GHz wifi or to use a much stronger radio transmitter.
* I should better know the speed at which the memory of the rocket fills and the battery depletes.  Now I felt in a hurry to launch, while that was likely not necessary.
* I should implement means that facilitate recovery of the rocket after landing: bright colours, buzzing sound, flashing light, contact information on rocket, portable radio receiver, airtag, etc.

## Acknowledgements
Thanks to the organizers of Fri3d Camp for creating the inspiring environment that made me build this rocket payload and created a forum for sharing this project with others.

Thanks to Benny Geys for providing the launch facilities and practical support regarding the rocket.  Thanks also to David Steeman for searching the rocket, even if unsuccessful!  

Finally, I am grateful to Mieke Praet for gracefully granting me the time and space to play.
