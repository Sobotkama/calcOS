/**
 * @file display.h
 * @author Martin Sobotka (sobotkama@gmail.com)
 * @brief display header file
 * @version 0.1
 * @date 2019-09-10
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#pragma once
#include <GxEPD2_BW.h>
#include <Fonts/FreeMono9pt7b.h>
#include <Fonts/Picopixel.h>
#include "img.h"

void showLogo();
void prepare();
void setupDisplay();
void displayLoop( void * parameter );
