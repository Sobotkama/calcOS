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
#define ENABLE_GxEPD2_GFX 0

#include <GxEPD2_BW.h>
#include <Fonts/FreeMonoBold9pt7b.h>
#include <Fonts/Picopixel.h>
#include "img.h"
GxEPD2_BW<GxEPD2_290, GxEPD2_290::HEIGHT> display(GxEPD2_290(/*CS=5*/ SS, /*DC=*/ 17, /*RST=*/ 16, /*BUSY=*/ 4));

void showLogo();
void prepare();


void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println("setup");
  Serial.println("some printing");
  delay(1000);
  Serial.println("delayed");
  display.init(115200);
  Serial.println("inited");
  showLogo();
  Serial.println("setup done");
  prepare();
}



void loop() {
  int ry;
  char cstr[16];
  itoa(0,cstr,10);
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_BLACK);
  for (int i = 0; i < 100; i++) {
    
    int16_t tbx, tby; uint16_t tbw, tbh;
    display.getTextBounds(cstr, 0, 0, &tbx, &tby, &tbw, &tbh);
    uint16_t utx = ((display.width() - tbw) ) - tbx;
    uint16_t uty = ((display.height() / 4) * 3 - tbh / 2) - tby;
    Serial.println(tbh);
    ry = uty - tbh;
    display.fillRect(utx + tbx, ry, tbw, tbh, GxEPD_WHITE);
    itoa(i, cstr, 10);
    display.getTextBounds(cstr, 0, 0, &tbx, &tby, &tbw, &tbh);
    utx = ((display.width() - tbw) ) - tbx;
    uty = ((display.height() / 4) * 3 - tbh / 2) - tby;
    
    display.setCursor(utx, uty);
    display.print(cstr);
    display.display(true);
    Serial.println(cstr);
  }
}

/**
 * @brief Shows our logo.
 * 
 */
void showLogo() {
  display.setFullWindow();
  //bool m = display.mirror(true);
  display.fillScreen(GxEPD_WHITE);
  display.drawInvertedBitmap(0, 0, logo, display.epd2.WIDTH, display.epd2.HEIGHT, GxEPD_BLACK);
  display.display();
  delay(2000);
  //display.mirror(m);
}


const char Hello[] = "Hello";
const char World[] = "There" ;
const char ping[] = "General Kenobi";

void prepare() {
  display.fillScreen(GxEPD_WHITE);
  display.setRotation(1);
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_BLACK);
  display.display(true);
  display.drawFastHLine(0, 8, 296, GxEPD_BLACK);
  display.display(true);
  int16_t tbx, tby; uint16_t tbw, tbh;
  display.getTextBounds(Hello, 0, 0, &tbx, &tby, &tbw, &tbh);
  uint16_t utx = ((display.width() - tbw) ) - tbx;
  uint16_t uty = ((display.height() / 4) - tbh / 2) - tby;
  display.setCursor(utx, uty);
  display.print(Hello);
  display.display(true);

  //delay(100);
  display.getTextBounds(World, 0, 0, &tbx, &tby, &tbw, &tbh);
  utx = ((display.width() - tbw) ) - tbx;
  uty = ((display.height() / 4) * 2 - tbh / 2) - tby;
  display.setCursor(utx, uty);
  display.print(World);
  display.display(true);

  //delay(100);
  display.setFont(&Picopixel);
  display.getTextBounds(ping, 0, 0, &tbx, &tby, &tbw, &tbh);
  utx = ((display.width() - tbw) ) - tbx;
  uty = tbh;
  display.setCursor(utx, uty);
  display.print(ping);
  display.display(true);
}