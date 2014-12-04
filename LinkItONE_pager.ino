/*
 * Modified from SMS Control Light and LCD Hello World
 * 
 * You should insert a SIM car and attach the GPRS antenna 
 * Send a text to display senders number and first 16 chars
 * R/G/B/W as first letter will change background colour
 *
 * LCD display connected to I2C on LinkIt ONE
 */

#include <Wire.h>
#include "rgb_lcd.h"
#include <LTask.h>
#include <LGSM.h>

rgb_lcd lcd;

int colorR = 0;
int colorG = 255;
int colorB = 0;
int waitcount =0;

void setup() 
{
    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
    
    lcd.setRGB(colorR, colorG, colorB);
    
    // Print a message to the LCD.
    lcd.print("hello, world!");
    
    while(!LSMS.ready())
    {
        delay(1000);
        lcd.setCursor(0,0);
        lcd.print("Waiting for GSM "+waitcount);
        waitcount++;
    }
    
    lcd.setCursor(0,0);
    lcd.print("GSM OK!!        ");

    delay(1000);
}

/*void loop() 
{
    // set the cursor to column 0, line 1
    // (note: line 1 is the second row, since counting begins with 0):
    lcd.setCursor(0, 1);
    // print the number of seconds since reset:
    lcd.print(millis()/1000);

    delay(100);
}*/
void loop()
{

    char p_num[20];
    int len = 0;
    char dtaget[500];

    if(LSMS.available()) // Check if there is new SMS
    {
    
        LSMS.remoteNumber(p_num, 20); // display Number part
        lcd.setCursor(0,0);
        lcd.print(p_num);
        lcd.setCursor(0,1);
        while(true)
        {
            int v = LSMS.read();
            if(v < 0)
            break;

            dtaget[len++] = (char)v;
            lcd.print((char)v);
        }
        lcd.print("               ");
        LSMS.flush(); // delete message

        
        if((dtaget[0] == 'R') || (dtaget[0] == 'r'))
        {
            int colorR = 255;
            int colorG = 0;
            int colorB = 0;
            lcd.setRGB(colorR, colorG, colorB);
        }

        else if((dtaget[0] == 'G') || (dtaget[0] == 'g'))
        {
            int colorR = 0;
            int colorG = 255;
            int colorB = 0;
            lcd.setRGB(colorR, colorG, colorB);
        }
        else if((dtaget[0] == 'B') || (dtaget[0] == 'b'))
        {
            int colorR = 0;
            int colorG = 0;
            int colorB = 255;
            lcd.setRGB(colorR, colorG, colorB);
        }
        else if((dtaget[0] == 'W') || (dtaget[0] == 'w'))
        {
            int colorR = 255;
            int colorG = 255;
            int colorB = 255;
            lcd.setRGB(colorR, colorG, colorB);
        }
    }
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
