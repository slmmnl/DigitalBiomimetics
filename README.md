# Digital Biomimetics
The source code shared during 2019 Digital Biomimetics course at SUTD. The extrusion project folder can be used with either the Arduino / Wiring interface or Visual Studio Code. It contains the firmware logic for the Ardbox PLC devices used in conjuction with various extruders and the ABB robot.

This Fork includes code to connect the ArdRelay Box to an external Arduino UNO to extend the capabilities of the current Ardbox since most of the extra pins are used for 8-bit Communication already.

Using 2 spare digital pins, 4 states are created.
These allow for simple 2-bit communication.

The current External Uno code includes code in order to control the Variable Nozzle attachment. 
