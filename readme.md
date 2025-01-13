# Teensy_40

## Description
This repo is a template for Teensy 4.0 development board.  It is based on [Teensyduino](https://www.pjrc.com/teensy/teensyduino.html), by PJRC, so it's assumed that you already have this framework setup on your PC.  In this repo, [FreeRTOS](https://www.freertos.org/) is added to the *Teensyduino* framework.  The FreeRTOS port is made available by <ins>tsandman</ins> on GitHub: [freertos-teensy](https://github.com/tsandmann/freertos-teensy).  The release used in this repo is from version [v11.0.1_v1](https://github.com/tsandmann/freertos-teensy/releases/tag/v11.0.1_v1), which utilizes FreeRTOS version 11.0.1.

## FreeRTOS Integration
The following steps are taken in order to make *freertos-teensy* work with *Teensyduino*:
1. Get source code from the [GitHub Release](https://github.com/tsandmann/freertos-teensy/releases/tag/v11.0.1_v1) and unpack.  We will use only contents from the ```src``` folder.
2. Create folder ```src/freertos-teensy``` in your sketch folder. You should have something like ```sketch/src/freertos-teensy```.
3. Put everything according to (1) into this folder. That is, everything in ```freertos-teensy/src/``` goes into ```sketch/src/freertos-teensy/```.
4. In files in the ```portable``` folder, change relative ```#include``` to include ```"../"``` so they point to their parent folder instead, in this case, the ```freertos-teensy``` folder.

There's a small bug for using Teensy4.0.  To fix this,
add ```#ifdef ARDUINO_TEENSY41``` around the ```ram3_usage()``` function in 2 files: *teensy.h* and *teensy_4.cpp*.
 
This repo already have the above changes included, so you can just copy this folder and use as is.


## Teensyduino Core Modification
According to *freertos-teensy*, the *Teensyduino* core must be modified to prevent freezes.
* Locate the core.  For example, on Windows, the core of v1.59.0 is located at ```AppData\Local\Arduino15\packages\teensy\hardware\avr\1.59.0\cores```.  
* Make changes as indicated by diffs in this [pull request](
https://github.com/PaulStoffregen/cores/pull/683/files).

Do this for every computer that you want to work on the Teensy FreeRTOS port.

