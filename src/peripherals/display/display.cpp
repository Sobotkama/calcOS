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
GxEPD2_BW<GxEPD2_290, GxEPD2_290::HEIGHT> display(GxEPD2_290(/*CS=5*/ SS, /*DC=*/17, /*RST=*/16, /*BUSY=*/4));

/**
 * @brief Initialises display
 * 
 */
void setupDisplay()
{
    display.init(115200);
    Serial.println(F("display inited"));
    showLogo();
    prepare();
}

/**
 * @brief Shows our logo.
 * 
 */
void showLogo()
{
    display.setFullWindow();
    /**
     * @brief Display stays black otherwise
     * 
     */
    display.fillScreen(GxEPD_WHITE);
    display.drawInvertedBitmap(0, 0, logo, display.epd2.WIDTH, display.epd2.HEIGHT, GxEPD_BLACK);
    display.display();
    delay(2000);
}

/**
 * @brief Draws a statusbar separator
 * @details Currently also shows a Hello There
 * 
 */
void prepare()
{
    const char Hello[] PROGMEM = "Hello";
    const char World[] PROGMEM = "There";
    const char ping[] PROGMEM  = "General Kenobi";
    display.fillScreen(GxEPD_WHITE);
    display.setRotation(1);
    display.setFont(&FreeMono9pt7b);
    display.setTextColor(GxEPD_BLACK);
    //display.display(true);
    display.drawFastHLine(0, 8, 296, GxEPD_BLACK);
    //display.display(true);
    int16_t tbx, tby;
    uint16_t tbw, tbh;
    display.getTextBounds(Hello, 0, 0, &tbx, &tby, &tbw, &tbh);
    uint16_t utx = ((display.width() - tbw)) - tbx;
    uint16_t uty = ((display.height() / 4) - tbh / 2) - tby;
    display.setCursor(utx, uty);
    display.print(Hello);
    //display.display(true);

    //delay(100);
    display.getTextBounds(World, 0, 0, &tbx, &tby, &tbw, &tbh);
    utx = ((display.width() - tbw)) - tbx;
    uty = ((display.height() / 4) * 2 - tbh / 2) - tby;
    display.setCursor(utx, uty);
    display.print(World);
    //display.display(true);

    //delay(100);
    display.setFont(&Picopixel);
    display.getTextBounds(ping, 0, 0, &tbx, &tby, &tbw, &tbh);
    utx = ((display.width() - tbw)) - tbx;
    uty = tbh;
    display.setCursor(utx, uty);
    display.print(ping);
    display.display(false);
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
void eraseText(String text, uint16_t x, uint16_t y, const GFXfont *font, uint16_t color)
{
    display.setFont(font);
    display.setTextColor(~color);
    display.setCursor(x, y);
    display.print(text);
}

/**
 * @brief Draws text buffer
 * @details Currently just displays a counter
 * 
 * @param mandatory parameter to be a valid task
 */
void displayLoop(void *parameter)
{
    const GFXfont *font = &FreeMono9pt7b;
    uint16_t color = GxEPD_BLACK;
    uint16_t x = 0, y = 0;
    int16_t tbx, tby;
    uint16_t tbw, tbh;
    String ptext;
    display.setFont(font);
    display.setTextColor(GxEPD_BLACK);
    for (;;) //forever
    {
        for (int i = 0; i < 100; i++)
        {
            eraseText(ptext, x, y, font, color);
            display.setTextColor(color);
            ptext = String(i);
            display.getTextBounds(ptext, 0, 0, &tbx, &tby, &tbw, &tbh);
            x = ((display.width() - tbw)) - tbx;
            y = ((display.height() / 4) * 3 - tbh / 2) - tby;
            display.setCursor(x, y);
            display.print(ptext);
            display.display(true);
            Serial.println(ptext);
            vTaskDelay(1);
        }
    }
}