<p align="center"><h2>Apple HomeKit for IKEA VINDRIKTNING PM2.5 Air Quality sensor</h2></p>


<div align="center"><img src="./img/qrcode.svg" alt="pair_code" width="100"/></div>

ESP8266 firmware, for IKEA VINDRIKTNING PM2.5 Air Quality sensor.
The modification doesn't interfere with the normal operation of the device in any way.
The ESP8266 just adds another data sink beside the colored LEDs.

This Firmware is Frankenstein Monster between MQTT ESP8266 IKEA VINDRIKTNING Firmware from Hypfer and ESP8266 HomeKit implementation from Mixiaoxiao. 
It's my first project in C for ESP8266, so don't expect any warranties. But it works on my device. 
I am not liable for any damage to your devices. If you use this firmware, it's your own risk.

![welcome_picture](./img/IMG_0499.jpg)

## Prerequisites

- An ESP8266 with a 5v voltage regulator (e.g. a Wemos D1 Mini)
- Some short cables
- A soldering iron
- A long PH0 Screwdriver

Fortunately, there is a lot of unused space in the enclosure, which is perfect for our ESP8266.
Also, everything we need is accessible via easy to solder test points.

## Hardware

To install the ESP8266, you need to unscrew the four visible screws in the back of the enclosure.

Then, there are also three screws holding the tiny PCB in place. These aren't necessary to remove since you can solder
in-place, however personally, I'd recommend taking the board out of there since it will be easier to solder without fear
of accidentally melting some plastic.

![board](./img/IMG_0502.jpg)

As you can see in this image, you'll need to solder wires to GND, 5V, and the Testpoint that is connected to TX of the
Particle Sensor.

Then just connect these Wires to GND, VIN (5V), and D2 (if you're using a Wemos D1 Mini).

Done.

## Software

The firmware can be built and flashed using the Arduino IDE.

For this, you will need to add ESP8266 support to it by [using the Boards Manager](https://github.com/esp8266/Arduino#installing-with-boards-manager).

1. Go to this GitHub repo and download it as ZIP - https://github.com/Mixiaoxiao/Arduino-HomeKit-ESP8266
2. In Arduino IDE select "Sketch" -> "Include Library" and "Add .ZIP Library..." and select downloaded ZIP
3. Download and open this repository in Arduino IDE
5. Set the ESP8266 CPU to run at 160MHz
3. Build, flash, and you're done.

## Connect to HomeKit

1. Plug your Air Quality sensor to power (ESP8266 is powered through VINDRIKTNING)
2. Go to WiFi Settings on your iPhone/iPad and connect to "VINDRIKTNING" WiFi
3. Page is opened automatically where you select your Home network and make a connection
4. Go to your Home app and select "Add Accessory"
5. Now Scan code on top of this webpage, alternatively select "More Options" and you should see your Air Quality Sensor there (Password is 111-11-111).

## ToDo

✅ <strike>Easier WiFi pairing process</strike>

✅ <strike>Reset function for WiFi</strike>

✅ <strike>OTA Updates</strike>

## References and sources

- [@Hypfer](https://twitter.com/hypfer?lang=en) for MQTT ESP8266 VINDRIKTNING custom firmware [GitHub link](https://github.com/Hypfer/esp8266-vindriktning-particle-sensor)
- [@Mixiaoxiao](https://twitter.com/haxfleisch) for ESP8266 HomeKit firmware [GitHub link](https://github.com/Mixiaoxiao/Arduino-HomeKit-ESP8266)
- [@haxfleisch](https://twitter.com/haxfleisch) for their teardown of the device.
- [Gabriel Valky](https://github.com/gabonator) for the incredibly useful [LA104 custom firmware + tools](https://github.com/gabonator/LA104)
