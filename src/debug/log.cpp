/**
 * @file log.cpp
 * @author Martin Sobotka (sobotkama@gmail.com)
 * @brief Contains dlog function
 * @version 0.1
 * @date 2019-09-10
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include <Arduino.h>

/**
 * @brief Prints message to serial
 * @details I got bored writing Serial.println over and over again.
 * dlog stands for debug log. log() was already taken.
 * @param text text to print
 */
void dlog(String text)
{
    Serial.println(text);
}