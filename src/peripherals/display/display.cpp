/**
 * @file display.cpp
 * @author Martin Sobotka (sobotkama@gmail.com)
 * @brief This file handles display communication
 * @version 0.1
 * @date 2019-09-10
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#include <Arduino.h>
#include "display.h"
#include "debug/log.h"


/**
 * @brief Initialises display
 * 
 */
Display::Display() : paper(GxEPD2_290(/*CS=5*/ SS, /*DC=*/17, /*RST=*/16, /*BUSY=*/4)){
    dlog("hello");
    paper.init(115200);
    Serial.println(F("display inited"));
    };

void Display::startDisplay()
{   
    showLogo();
    prepare();
}

/**
 * @brief Shows our logo.
 * 
 */
void Display::showLogo()
{
    paper.setFullWindow();
    /**
     * @brief Display stays black otherwise
     * 
     */
    paper.fillScreen(GxEPD_WHITE);
    paper.drawInvertedBitmap(0, 0, logo, paper.epd2.WIDTH, paper.epd2.HEIGHT, GxEPD_BLACK);
    paper.display(false);
    delay(2000);
}

/**
 * @brief Draws a statusbar separator
 * @details Currently also shows a Hello There
 * 
 */
void Display::prepare()
{
    const char Hello[] PROGMEM = "Hello";
    const char World[] PROGMEM = "There";
    const char ping[] PROGMEM  = "General Kenobi";
    paper.fillScreen(GxEPD_WHITE);
    paper.setRotation(1);
    paper.setFont(&FreeMono9pt7b);
    paper.setTextColor(GxEPD_BLACK);
    //paper.display(true);
    paper.drawFastHLine(0, 8, 296, GxEPD_BLACK);
    //paper.display(true);
    int16_t tbx, tby;
    uint16_t tbw, tbh;
    paper.getTextBounds(Hello, 0, 0, &tbx, &tby, &tbw, &tbh);
    uint16_t utx = ((paper.width() - tbw)) - tbx;
    uint16_t uty = ((paper.height() / 4) - tbh / 2) - tby;
    paper.setCursor(utx, uty);
    paper.print(Hello);
    //paper.display(true);

    //delay(100);
    paper.getTextBounds(World, 0, 0, &tbx, &tby, &tbw, &tbh);
    utx = ((paper.width() - tbw)) - tbx;
    uty = ((paper.height() / 4) * 2 - tbh / 2) - tby;
    paper.setCursor(utx, uty);
    paper.print(World);
    //paper.display(true);

    //delay(100);
    paper.setFont(&Picopixel);
    paper.getTextBounds(ping, 0, 0, &tbx, &tby, &tbw, &tbh);
    utx = ((paper.width() - tbw)) - tbx;
    uty = tbh;
    paper.setCursor(utx, uty);
    paper.print(ping);
    paper.display(false);
}
/**
 * @brief Erases text from the display
 * @details Just draws the same text again. but inverts the color
 * 
 * @param text original text
 * @param x original cursor x position
 * @param y original cursor y position
 * @param font original text font
 * @param color original text color
 */
void Display::eraseText(String text, uint16_t x, uint16_t y, const GFXfont *font, uint16_t color)
{
    paper.setFont(font);
    paper.setTextColor(~color);
    paper.setCursor(x, y);
    paper.print(text);
}

/**
 * @brief Draws text buffer
 * @details Currently just displays a counter
 * 
 * @param mandatory parameter to be a valid task
 */
void Display::displayLoop(void *parameter)
{
    const GFXfont *font = &FreeMono9pt7b;
    uint16_t color = GxEPD_BLACK;
    uint16_t x = 0, y = 0;
    int16_t tbx, tby;
    uint16_t tbw, tbh;
    String ptext;
    paper.setFont(font);
    paper.setTextColor(GxEPD_BLACK);
    for (;;) //forever
    {
        for (int i = 0; i < 100; i++)
        {
            eraseText(ptext, x, y, font, color);
            paper.setTextColor(color);
            ptext = String(i);
            paper.getTextBounds(ptext, 0, 0, &tbx, &tby, &tbw, &tbh);
            x = ((paper.width() - tbw)) - tbx;
            y = ((paper.height() / 4) * 3 - tbh / 2) - tby;
            paper.setCursor(x, y);
            paper.print(ptext);
            paper.display(true);
            Serial.println(ptext);
            vTaskDelay(1);
        }
    }
}