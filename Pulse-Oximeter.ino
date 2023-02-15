#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
 
 LiquidCrystal_I2C lcd(0x27, 16, 2);
 
#define n     1000
 
PulseOximeter abdullah;
uint32_t m = 0;
 
void BeatDetecton()
{
    Serial.println("Beat!");
}
 
void setup()
{    
    Serial.begin(9600);
    Serial.print("Initializing pulse oximeter..");
    
     lcd.backlight();
    lcd.begin(16,2);
    lcd.print("Initializing...");
    delay(3000);
    lcd.clear();
 
    // Checking power supply and wires are works or not
    if (!abdullah.begin()) {
        Serial.println("FAILED");
        for(;;);
    } else {
        Serial.println("SUCCESS");
    }
     abdullah.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);
 
    //Beat Detection
    abdullah.setOnBeatDetectedCallback(BeatDetecton);
}
 
void loop()
{
 
    abdullah.update();
    if (millis() - m > n) {
        Serial.print("Heart rate:");
        Serial.print(abdullah.getHeartRate());
        Serial.print("bpm / SpO2:");
        Serial.print(abdullah.getSpO2());
        Serial.println("%");
 
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("BPM : ");
        lcd.print(abdullah.getHeartRate());
        
        lcd.setCursor(0,1);
        lcd.print("SpO2: ");
        lcd.print(abdullah.getSpO2());
        lcd.print("%");
 
       m = millis();
    }
}
