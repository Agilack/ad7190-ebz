Led and Buttons Unit Test for AD7190-EBZ
========================================

    This program is a unit-test firmware that can be loaded into
the Cypress MCU. The goal of this app is to demonstrate the use
of push-buttons (S1 to S4) and the debug LED.

Build
-----

    A makefile script is available to compile the (single :p) C source
file, so just call "make" :
 $ make

Install / load
--------------

    The firmware can be loaded to MCU using USB. It is also possible to
put it into an i2c external memory but why for a unit test ? :) The load
process has been tested using fxload and cycfx2prog.
    The USB vid/pid of the board with the default firmware is 0456:b483 
which is an Analod Devices ID. If the external memory is erased or disconnected
the default FX2 chip ID is used 04b4:8613.

 $ cycfx2prog -id=0456.b483 prg:ut-led_button.ihx run
