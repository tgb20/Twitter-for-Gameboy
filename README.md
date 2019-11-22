# Twitter-for-Gameboy

### Limits of Twitter for Gameboy

No single message can be greater than 40 characters or the gameboy runs out of memory, it can print up to 43 characters but then the memory that handles scrolling the screen is overwritten. This could be solved by reducing the interal memory buffer for incoming messages.

If you send byte `8` then it will tell the gameboy to move onto a new message. This is a checkmark on the gameboy, I am unsure of what it would be on the computer side.

### Wiring

To use this project you will need to connect a gameboy link cable to an arduino. I did this by cutting the cable and soldering breadboard wires to the leads. The pinout/colors for the GBA/GBC link cable are:
```
1 | 3 | 5       | SI | CO 
2 | 4 | 6    SO |    | G

SI - Socket In - Orange
SO - Socket Out - Red
CO - Clock - Green (could be brown)
G - Ground - Blue
```
with the rounded side up.
 
### Gameboy Code

The gameboy source code and rom are located in the root of the project.

main.c contains the source for the rom

main.gb is the rom file itself that can be written to a flash cart.

### Arduino Code

In ArduinoSerialRelay you will find the Arduino sketch for relaying serial to the gameboy. This sketch has no character or length checking built in and will relay whatever you send to the gameboy, this could cause the gameboy to crash.
