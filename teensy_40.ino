/*
 * This file is part of the FreeRTOS port to Teensy boards.
 * Copyright (c) 2020-2024 Timo Sandmann
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library. If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * Note for the FreeRTOS library:
 * This lib is obtained from
 * https://github.com/tsandmann/freertos-teensy
 * Release v11.0.1_v1
 * The following steps are taken in order to use this lib:
 * (1) Get the Release from above URL and unpack the zip file.
 *     Use only the contents from the 'src' folder.
 * (2) Create folder 'src/freertos-teensy' in your sketch folder.
 *     You should have something like 'sketch/src/freertos-teensy'.
 * (3) Put everything according to (1) into this folder.
 *     That is, 'freertos-teensy/src/*' go into 'sketch/src/freertos-teensy/'.
 * (4) In files in the 'portable' folder, change relative #include to include "../"
 *     so they point to their parent folder instead, in this case, the 'freertos-teensy' folder.
 *
 * There's a small bug for using Teensy4.0.  To fix this,
 * add #ifdef ARDUINO_TEENSY41 around the ram3_usage() function in 2 files:
 * teensy.h and teensy_4.cpp.
 * 
 * This repo already have the above changes included, so you can just copy this folder and use as is.
 *
 * Next, modify the Teensyduino core.  For example, the core of v1.59.0 is located at
 * AppData\Local\Arduino15\packages\teensy\hardware\avr\1.59.0\cores.
 * Make changes as indicated by diffs in
 * https://github.com/PaulStoffregen/cores/pull/683/files.
 * 
 * Do this for every computer that you want to work on the Teensy FreeRTOS port.
 * 
 */

#include "src/freertos-teensy/arduino_freertos.h"
#include "avr/pgmspace.h"

static void task1(void *)
{
  pinMode(arduino::LED_BUILTIN, arduino::OUTPUT);
  while (true)
  {
    digitalWriteFast(arduino::LED_BUILTIN, arduino::LOW);
    vTaskDelay(pdMS_TO_TICKS(500));

    digitalWriteFast(arduino::LED_BUILTIN, arduino::HIGH);
    vTaskDelay(pdMS_TO_TICKS(500));
  }
}

static void task2(void *)
{
  Serial.begin(0);
  while (true)
  {
    Serial.println("TICK");
    vTaskDelay(pdMS_TO_TICKS(1'000));

    Serial.println("TOCK");
    vTaskDelay(pdMS_TO_TICKS(1'000));
  }
}

FLASHMEM __attribute__((noinline)) void setup()
{
  Serial.begin(0);
  delay(2'000);

  if (CrashReport)
  {
    Serial.print(CrashReport);
    Serial.println();
    Serial.flush();
  }

  Serial.println(PSTR("\r\nBooting FreeRTOS kernel " tskKERNEL_VERSION_NUMBER ". Built by gcc " __VERSION__ " (newlib " _NEWLIB_VERSION ") on " __DATE__ ". ***\r\n"));

  xTaskCreate(task1, "task1", 128, nullptr, 2, nullptr);
  xTaskCreate(task2, "task2", 128, nullptr, 2, nullptr);

  Serial.println("setup(): starting scheduler...");
  Serial.flush();

  vTaskStartScheduler();
}

void loop() {}
