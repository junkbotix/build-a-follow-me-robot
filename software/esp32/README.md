![Junkbotix Banner](./images/banner-1024px.jpg)

Check out the latest on this project and other tutorials at the [Junkbotix Channel](https://www.youtube.com/channel/UCNxQ47xBEYjD-mey_lxj9Aw) on Youtube!

<br>

## Firmware for the Junkbotix Build A "Follow-Me" Robot (!!! WIP !!!)

* [FMController](./FMController) - Base controller firmware
* [Libraries](./libraries) - Custom support libraries
  * [Junkbotix_Beacons](./libraries/Junkbotix_Beacons) - Interface library for LED and audible beacons
  * [Junkbotix_Comms](./libraries/Junkbotix_Comms) - Serial and web communications library
  * [Junkbotix_Etrex](./libraries/Junkbotix_Etrex) - Interface library for the Garmin Etrex GPS (serial)
  * [Junkbotix_Nav](./libraries/Junkbotix_Nav) - Navigation library
  * [Junkbotix_Planner](./libraries/Junkbotix_Planner) - Route planner library
  * [Junkbotix_Victor884](./libraries/Junkbotix_Victor884) - Interface library for Victor-884 motor controllers
  * [Junkbotix_Webserver](./libraries/Junkbotix_Webserver) - Web server library
* [Tests](./tests) - Various prototype test code

<br>

### Notes:

* This ESP32 firmware is currently in an incomplete state, and may or may not work as-is. Certain 3rd-party libraries will also need to be installed to for it to compile properly. Please consider this a "work-in-progress".
* For now, there are no unit-tests or other such framework for these files. I had considered adding some (using [AUnit](https://github.com/bxparks/AUnit)), but I felt the task of learning the implementation details both outweighed the need for getting this code implemented in a somewhat timely manner, and would distract from the effort.

<br>

### To Compile for the ESP32

1. Install the [Arduino IDE](https://www.arduino.cc/en/software) and the [Arduino core for the ESP32](https://github.com/espressif/arduino-esp32).
2. Set your sketch folder to the root of this directory.
3. Open [FMController.ino](./FMController/FMController.ino) in the Arduino IDE and compile.

<br>

## License

Unless otherwise specified, all code is licensed as [GPLv3](http://www.gnu.org/licenses/gpl-3.0.en.html) and is Copyright (c) 2021 by Junkbotix

See the [`LICENSE.md`](./LICENSE.md) file for more information.

* If you wish to make a pull request against this repo, go for it, just know that any such request may or may not be used...
* I make no guarantees that any of the code will compile properly or work at all!
* I take no responsibility for your use or misuse of any of this code!
* Caveat emptor!