# RGB-LED
Arduino Nano, 12V Led Strip &amp; Python GUI Project

This is a project that I made during the Christmas holiday to use at my deskp for some ambiental lightning. It is based on an Arduino Nano, which is connected to the PC through the USB.
The GUI is made in Python using Tkinter Toolkit and has some nice features. You can select only one colour based on the values of red, green, blue (0-255...PWM) or you have some buttons for different lightning games. The data is sent through the serial and the Arduino codes reads and parses this data.

The actual hardware part that gives you the light is based on three TIP120 NPN Darlington transistors, each connected
at a PWM pin from Arduino and a 12V RGB Led Strip which is powered from a 12V supply (same GND!!).

I send a PWM signal to each channel to make a colour game.
