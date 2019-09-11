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

bool keyField [64];
}
int kOut [4] = {35,32,33,26};
int kInp [4] = {26,27,14,12};
    pinMode(kOut[0], INPUT);
    pinMode(kOut[1], INPUT);
    pinMode(kOut[2], INPUT);
    pinMode(kOut[3], INPUT);
    pinMode(kInp[0], OUTPUT);
    pinMode(kInp[1], OUTPUT);
    pinMode(kInp[2], OUTPUT);
    pinMode(kInp[3], OUTPUT);

}
void keyLoad(void *parameter)
{
    pinMode()

        for (;;)
    {
     for (int out=0; out<16;out++){
         for (i=0,i<4,i++){
            bool bitStatus = (out >> i) &1;
            digitalWrite(kInp[i],bitStatus);
         }
         for(int in=0; in<4,in++){
             keyFiled [out*4+in] = digitalRead(kInp[in]);
         }
     }   
    }

*    }
}