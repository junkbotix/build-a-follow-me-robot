![Junkbotix Banner](./images/banner-1024px.jpg)

<br>

[![Part 11.1](./images/title-720px.jpg)](https://www.youtube.com/watch?v=7EC0L8-eelA)

Check out the latest on this project and other tutorials at the [Junkbotix Channel](https://www.youtube.com/channel/UCNxQ47xBEYjD-mey_lxj9Aw) on Youtube!

<br>

## Software (!!! WIP !!!)

Here you'll find links to all the source code and software developed for this tutorial...

<br>

## Quicklinks
* [State Machine Outline](./esp32/files/STATE-MACHINE-OUTLINE.md) - Basic outline for the firmware state machine process
* [Code for ESP32](./esp32)
  * [FMController](./esp32/FMController) - Base controller firmware
  * [Libraries](./esp32/libraries) - Custom support libraries
    * [Junkbotix_Beacons](./esp32/libraries/Junkbotix_Beacons) - Interface library for LED and audible beacons
    * [Junkbotix_Client](./esp32/libraries/Junkbotix_Client) - Class to model the client
    * [Junkbotix_Common](./esp32/libraries/Junkbotix_Common) - Common library/class structures, defines, etc
    * [Junkbotix_Comms](./esp32/libraries/Junkbotix_Comms) - Serial and web communications library
    * [Junkbotix_Etrex](./esp32/libraries/Junkbotix_Etrex) - Interface library for the Garmin Etrex GPS (serial)
    * [Junkbotix_Nav](./esp32/libraries/Junkbotix_Nav) - Navigation library
    * [Junkbotix_Planner](./esp32/libraries/Junkbotix_Planner) - Route planner library
    * [Junkbotix_Robot](./esp32/libraries/Junkbotix_Robot) - Class to model the robot
    * [Junkbotix_Victor884](./esp32/libraries/Junkbotix_Victor884) - Interface library for Victor-884 motor controllers
    * [Junkbotix_Webserver](./esp32/libraries/Junkbotix_Webserver) - Web server library
  * [Test Code](./esp32/tests) - Various prototype test code
    * [Flasher](./esp32/tests/flasher)
    * [Sweep Servo Test](./esp32/tests/sweep-servo-test)
    * [GPS Serial Test](./esp32/tests/gps-serial-test)
    * [Beacons and Motors Test](./esp32/tests/beacons-motors-test)

<br>

## License

Unless otherwise specified, all code is licensed as [GPLv3](http://www.gnu.org/licenses/gpl-3.0.en.html) and is Copyright (c) 2021 by Junkbotix

See the [`LICENSE.md`](./LICENSE.md) file for more information.

* If you wish to make a pull request against this repo, go for it, just know that any such request may or may not be used...
* I make no guarantees that any of the code will compile properly or work at all!
* I take no responsibility for your use or misuse of any of this code!
* Caveat emptor!