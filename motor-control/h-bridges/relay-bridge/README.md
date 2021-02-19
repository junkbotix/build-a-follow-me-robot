![Junkbotix Banner](./images/banner-1024px.jpg)

<br>

## Relay Bridges

![Relay Module](./images/relay-module-720px.jpg)

<br>

These relay modules are also widely available and inexpensive. They come in a variety of configurations, having 1, 2, 4, or 8 relays. Each relay is usually a 10A SPDT. Some boards, like this one, are opto-isolated (and as such, usually can be used with 3.3v TTL outputs, too). But not all are.

<br>

## Schematic

![4 channel relay module schematic](./files/4_channel_relay_schematic.png)

<br>

## Relay H-Bridge

A pair of the relays can be used to build a simple and controllable h-bridge:

![Transistor Control](./files/bridge-relay-2.jpg)<br>
Note the dual-ended motor power supply in the above schematic; compare it with the following (which is also opto-isolated):

![Opto-Isolator Control](./files/isolated-bi-directional-motor-control.jpg)

<br>

## Using Bosch Relays

It might also be possible to desolder the relays from such a relay module, and replace them with pairs of Bosch automotive relays, for greater current handling:

Bosch SPDT Relay<br>
![Bosch SPDT Relay](./files/bosch-relay-720px.jpg)

Bosch SPDT Relay Pinout<br>
![Bosch SPDT Relay Pinout](./files/bosch-spdt-relay-pinout.jpg)

Motor Control<br>
![Bosch SPDT Relay Motor Control](files/bosch-relay-motor-control.jpg)

Alternatively, you can just replace the switches with transistors, as before, to control the relays.

<br>

## MOSFET Speed Control (hybrid bridge)

A mosfet can also be used on the low-side of the bridge to control the speed of the motor:

![MOSFET Control](./files/dpdt-h-bridge.jpg)

Note that this schematic shows a DPDT relay being used, but it isn't common to find such relays with high-current carrying contacts, which is why pairs of SPDT relays are usually used.