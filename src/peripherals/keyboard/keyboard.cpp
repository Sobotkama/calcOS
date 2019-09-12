/**
 * @file keyboard.cpp
 * @author Adam Velik (you@domain.com)
 * @brief This file handles the keyboard
 * @version 0.1
 * @date 2019-09-10
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include <Arduino.h>
#include "keyboard.h"
void keyInit()
{
    bool keyField1[64];
    bool keyField2[64];
    int output[256] = {}; /// dopln asciiaunicode
    byte shiftst;
    byte altst;
    byte ctrlst;
    bool shiftonce;
    bool altonce;
    bool ctrlonce;
    bool shiftlock;
    bool ctrllock;
    bool altlock;
    int kOut[4] = {35, 32, 33, 26};
    int kInp[4] = {26, 27, 14, 12};
    pinMode(kOut[0], INPUT);
    pinMode(kOut[1], INPUT);
    pinMode(kOut[2], INPUT);
    pinMode(kOut[3], INPUT);
    pinMode(kInp[0], OUTPUT);
    pinMode(kInp[1], OUTPUT);
    pinMode(kInp[2], OUTPUT);
    pinMode(kInp[3], OUTPUT);
}

void write(int x, int y, bool state)
{
    int pos = x * 4 + y;
    if (keyField1[pos] == state)
    {
        keyField1[pos] = state;
    }
    else
    {
        keyField2[pos] = state;
    }
    keyPress(pos);
}


void keyLoad(void *parameter)
{

    for (;;)

    {
        for (int out = 0; out < 16; out++)
        {
            for (int i = 0, i < 4, i++)
            {
                bool bitStatus = (out >> i) & 1;
                digitalWrite(kInp[i], bitStatus);
            }
            for (int in = 0; in < 4, in++)
            {
                write(out, in, digitalRead(kInp[in]));
            }
        }
        vTaskDelay(25);
    }

    *
}
}

void keypress(int pos)
{
    switch (pos)
    { //registrace shift alt ctrl
    case 1:
        shiftst++;
        break;
    case 2:
        ctrlst++;
        break;
        case 3;
        altst++;
        break;

    }
    switch (shiftst%3){
        case 0:
            shiftlock = 0;
            shiftonce = 0;
            break;
        case 1:
            shiftlock = 0;
            shiftonce = 1;
            break;
        case 2;
        shiftlock=1;
        shiftonce=0;
        break;

    }
    switch (altstate%3){
        case 0:
            altonce = 0;
            altlock = 0;
            break;
        case 1:
            altonce = 1;
            altlock = 0;
            break;
        case 2:
            altonce = 0;
            altlock = 1;
            break;
        }
        switch (ctrlstate % 3)
        {
        case 0:
            ctrlonce = 0;
            ctrllock = 0;
            break : case 1 : clrlonce = 1;
            ctrllock = 0;
            break;
        case 2:
            ctrlonce = 0;
            ctrllock = 1;
            break;
        }
        int byteout = pos + (64 * (shiftlock + shiftonce)) + (128 * (ctrllock + ctrlonce)) + 196(altlock + altonce);
        ctrlonce = 0;
        shiftonce = 0;
        altonce = 0;
        int out = int output[byteout];
        void kOut(out);
}

void kOut(int x);