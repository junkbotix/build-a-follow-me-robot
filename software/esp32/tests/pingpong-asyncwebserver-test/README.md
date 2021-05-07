![Junkbotix Banner](./images/banner-1024px.jpg)

Check out the latest on this project and other tutorials at the [Junkbotix Channel](https://www.youtube.com/channel/UCNxQ47xBEYjD-mey_lxj9Aw) on Youtube!

<br>

## Ping-Pong Async Web Server Test

This test is meant to verify operation of several parts needed for this project, specifically:

* Setting up an access point (SoftAP)
* Setting up a webserver (AsyncTCP and ESPAsyncWebServer)
* Serving up a webpage for controlling the ESP32 (via Ajax)
* Acting on async ajax requests, issuing responses, etc

In short, this test code is a complete example on how to control the ESP32 via an on-board application it serves up!

When the ESP32 is reset or rebooted, it:

1. Initializes the access point using the defined SSID and password (on-board LED blinks on and off slowly)
2. Waits for the access point to finish starting up, then configures it with an IP address
3. Waits for a station (browser or other client) to connect
4. Once a connection is made, the web server is started and the request handlers are configured
5. Information is given to the user (via the serial port) about how to connect to the web server
6. The on-board LED then blinks faster (500ms)
7. The user can then access the URL to control the ESP32, by pressing a couple of buttons, labled "Ping!" and "Pong!"
8. These buttons alter a count, which is sent back to the server, which then uses the count to alter the blinking rate of the LED
9. If an invalid request is received (such as going to an unsupported page or path), a 404 error page is shown to the user

<br>

## More Information

These are handy for figuring out what these pieces do, and what parameters are needed, etc. There's not a lot of official documentation for the SoftAP and WiFi library in general; I had to piece what I could together from some tutorials and from the source code of the library itself. The Async Web Server has much better documentation, in comparison. Even so, expect to do a little or a lot of experimentation and research to get it working properly!

* [WiFi Library (SoftAP)](https://github.com/espressif/arduino-esp32/tree/master/libraries/WiFi)
* [Async Web Server (ESPAsyncWebServer)](https://github.com/me-no-dev/ESPAsyncWebServer)

<br>

## Additional Tutorials for Reference

I found the tutorials below to be very useful in figuring out how to bring all of this together for this test. You'll probably find them helpful, too, as you play around with these libraries.

* [ESP32 Async Web Server: Control Outputs with Arduino IDE](https://randomnerdtutorials.com/esp32-async-web-server-espasyncwebserver-library/)
* [How to Set an ESP32 Access Point (AP) for Web Server](https://randomnerdtutorials.com/esp32-access-point-ap-web-server/)
* [ESP32 Useful Wi-Fi Library Functions](https://randomnerdtutorials.com/esp32-useful-wi-fi-functions-arduino/)

<br>

## License

Unless otherwise specified, all code is licensed as [GPLv3](http://www.gnu.org/licenses/gpl-3.0.en.html) and is Copyright (c) 2021 by Junkbotix

See the [`LICENSE.md`](./LICENSE.md) file for more information.

* If you wish to make a pull request against this repo, go for it, just know that any such request may or may not be used...
* I make no guarantees that any of the code will compile properly or work at all!
* I take no responsibility for your use or misuse of any of this code!
* Caveat emptor!