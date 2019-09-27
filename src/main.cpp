/**
 * @file main.cpp
 * @brief Main file.
 * @details This is our main file.
 * @authors Martin Sobotka (sobotkama@gmail.com)
 * Adam
 * @version 0.1
 * @date 2019-09-08
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include <Arduino.h>
#include "peripherals/display/display.h"
#include "peripherals/keyboard/keyboard.h"

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Display display;
  display.startDisplay();
  xTaskCreate(
      display.loop,   /* Task function. */
      "displayLoop", /* String with name of task. */
      10000,     /* Stack size in bytes. */
      NULL,      /* Parameter passed as input of the task */
      2,         /* Priority of the task. */
      NULL);     /* Task handle. */
      keyInit();
      keyRead();

}

void loop()
{
  display.showLogo();
}
