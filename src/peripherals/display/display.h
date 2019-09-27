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
extern Display display;
void showLogo();
void prepare();
void setupDisplay();
void displayLoop( void * parameter );
void eraseText(String text, uint16_t x, uint16_t y, const GFXfont *font, uint16_t color);

class Display {
    public:
        Display() : paper(GxEPD2_290(/*CS=5*/ SS, /*DC=*/17, /*RST=*/16, /*BUSY=*/4)){};
    private:
        GxEPD2_BW<GxEPD2_290, GxEPD2_290::HEIGHT> paper;
    public:
        void showLogo();
        void startDisplay();
        void setupDisplay();
        void showLogo();
        void prepare();
        void loop();
        void eraseText(String text, uint16_t x, uint16_t y, const GFXfont *font, uint16_t color);
        void displayLoop(void *parameter);
    
};

extern Display display;