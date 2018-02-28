Arduino core for ESP8266 WiFi chip
===========================================

This project brings support for ESP8266 chip to the Arduino environment. It lets you write sketches using familiar Arduino functions and libraries, and run them directly on ESP8266, no external microcontroller required.

ESP8266 Arduino core comes with libraries to communicate over WiFi using TCP and UDP, set up HTTP, mDNS, SSDP, and DNS servers, do OTA updates, use a file system in flash memory, work with SD cards, servos, SPI and I2C peripherals.

# Contents
- Installing options:
  - [Using Boards Manager](#installing-with-boards-manager)
  - [Using git version](#using-git-version)
  - [Using PlatformIO](#using-platformio)
  - [Building with make](#building-with-make)
- [Documentation](#documentation)
- [Issues and support](#issues-and-support)
- [Contributing](#contributing)  
- [License and credits](#license-and-credits)   

### Installing with Boards Manager

Starting with 1.6.4, Arduino allows installation of third-party platform packages using Boards Manager. We have packages available for Windows, Mac OS, and Linux (32 and 64 bit).

- Install the current upstream Arduino IDE at the 1.8 level or later. The current version is at the [Arduino website](http://www.arduino.cc/en/main/software).
- Start Arduino and open Preferences window.
- Enter ```http://arduino.esp8266.com/stable/package_esp8266com_index.json``` into *Additional Board Manager URLs* field. You can add multiple URLs, separating them with commas.
- Open Boards Manager from Tools > Board menu and install *esp8266* platform (and don't forget to select your ESP8266 board from Tools > Board menu after installation).

### Documentation

Documentation for latest development version: https://arduino-esp8266.readthedocs.io/en/latest/

### Issues and support ###

[ESP8266 Community Forum](http://www.esp8266.com/u/arduinoanswers) is a well established community for questions and answers about Arduino for ESP8266.

If you find this forum useful, please consider supporting it with a donation. <br />
[![Donate](https://img.shields.io/badge/paypal-donate-yellow.svg)](https://www.paypal.com/webscr?cmd=_s-xclick&hosted_button_id=4M56YCWV6PX66)

If you encounter an issue which you think is a bug in the ESP8266 Arduino Core or the associated libraries, you are welcome to submit it here on Github: https://github.com/esp8266/Arduino/issues.

Please provide as much context as possible:

- ESP8266 Arduino core version which you are using (you can check it in Boards Manager)
- your sketch code; please wrap it into a code block, see [Github markdown manual](https://help.github.com/articles/basic-writing-and-formatting-syntax/#quoting-code)
- when encountering an issue which happens at run time, attach serial output. Wrap it into a code block, just like the code.
- for issues which happen at compile time, enable verbose compiler output in the IDE preferences, and attach that output (also inside a code block)
- ESP8266 development board model
- IDE settings (board choich, flash size)

### Contributing

For minor fixes of code and documentation, please go ahead and submit a pull request.

Check out the list of issues which are easy to fix — [easy issues for 2.5.0](https://github.com/esp8266/Arduino/issues?q=is%3Aopen+is%3Aissue+milestone%3A2.5.0+label%3A%22level%3A+easy%22). Working on them is a great way to move the project forward.

Larger changes (rewriting parts of existing code from scratch, adding new functions to the core, adding new libraries) should generally be discussed by opening an issue first.

Feature branches with lots of small commits (especially titled "oops", "fix typo", "forgot to add file", etc.) should be squashed before opening a pull request. At the same time, please refrain from putting multiple unrelated changes into a single pull request.

### License and credits ###

Arduino IDE is developed and maintained by the Arduino team. The IDE is licensed under GPL.

ESP8266 core includes an xtensa gcc toolchain, which is also under GPL.

Esptool written by Christian Klippel is licensed under GPLv2, currently maintained by Ivan Grokhotkov: https://github.com/igrr/esptool-ck.

Espressif SDK included in this build is under Espressif MIT License.

ESP8266 core files are licensed under LGPL.

[SPI Flash File System (SPIFFS)](https://github.com/pellepl/spiffs) written by Peter Andersson is used in this project. It is distributed under MIT license.

[umm_malloc](https://github.com/rhempel/umm_malloc) memory management library written by Ralph Hempel is used in this project. It is distributed under MIT license.

[axTLS](http://axtls.sourceforge.net/) library written by Cameron Rich, built from https://github.com/igrr/axtls-8266, is used in this project. It is distributed under [BSD license](https://github.com/igrr/axtls-8266/blob/master/LICENSE).
