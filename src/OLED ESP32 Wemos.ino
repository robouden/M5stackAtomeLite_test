//To be done.
// map 2 potmeters to dutycycle, Freqency
// check graph on webserver for ESP32 at https://randomnerdtutorials.com/esp32-esp8266-plot-chart-web-server/


//for PWM https://docs.m5stack.com/en/api/pwm
// https://github.com/m5stack/m5-docs/blob/master/docs/en/core/atom_lite.md
// Peripherals Pin Map
// RGB Led	G27
// Btn	G39
// IR	G12A
// Bit	resolution	maximum frequency
// 16	65536	1,220.70Hz
// 15	32768	2,441.41Hz
// 14	16384	4,882.81Hz
// 13	8192	9,765.63Hz
// 12	4096	19,531.25Hz
// 11	2048	39,062.50Hz
// 10	1024	78,125.00Hz
// 9	512	  156,250.00Hz
// 8	256	  312,500.00Hz
// 7	128	  625,000.00Hz
// 6	64	  1,250,000.00Hz
// 5	32	  2,500,000.00Hz
// 4	16	  5,000,000.00Hz
// 3	8	    10,000,000.00Hz
// 2	4	    20,000,000.00Hz
// 1	2	    40,000,000.00Hz// The maximal frequency is 80000000 / 2^bit_num


#include <Wire.h>
#include "driver/ledc.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
// #include "ESP32MotorControl.h" 	// https://github.com/JoaoLopesF/ESP32MotorControl
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define VERSION "0.91"

// setting PWM properties
const int PWMPin = 32;  //outpin for driver
int freq = 100000;
int PWMChannel = 0;
int resolution = 4;
int dutyCycle = 1;
float pot_Freq_Rough_Read;
float pot_Freq_Rough_Read_old;
float pot_Freq_Fine_Read;
float pot_Freq_Fine_Read_old;
float pot_DutyCycle_Read;
float pot_DutyCycle_Read_old;
int pot_DutyCycle_pin=35;
int pot_Freq_Fine_pin=34;
int pot_Freq_Rough_pin=36;

void setup() {
  Serial.begin(115200);
  //I2C setup for display
  Wire.begin(22,21); //I2C 
  
  //Setup PWM parameters
  ledcSetup(PWMChannel, freq, resolution);
  ledcAttachPin(PWMPin, PWMChannel);
  ledcWrite(PWMChannel, dutyCycle);

  // GPIO pins setup
  pinMode(35, ANALOG); // PIN  (INPUT, OUTPUT, ANALOG) //DutyCycle
  pinMode(34, ANALOG); // PIN  (INPUT, OUTPUT, ANALOG) //freq fine
  pinMode(36, ANALOG); // PIN  (INPUT, OUTPUT, ANALOG) //freq rough

  //Display startup serial info
    Serial.println("start setup");
    Serial.printf("Duty = %d  Freq = %d HZ \n", (int)dutyCycle,freq);

 //Display startup info
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.clearDisplay();
    display.setTextSize(2);              // Normal 1:1 pixel scale
    display.setTextColor(SSD1306_WHITE); // Draw white text
    display.setCursor(0,0);              // Start at top-left corner
    display.print(F("ZPE V"));
    display.println(F(VERSION));  
    display.println();  
    display.print(F("Duty ="));
    display.println(dutyCycle);  
    display.print(F("Freq = "));
    display.println(freq);
    // display.println(F("OUT2 ="));
    display.display();
} 


void loop() {

      //Read analog pot variables and map to duty cycle and frequency
      // for frequency rough the idea is:
      int pot_Freq_Rough_Read = analogRead(pot_Freq_Rough_pin);
      if (abs(pot_Freq_Rough_Read-pot_Freq_Rough_Read_old)>300){
        pot_Freq_Rough_Read_old=pot_Freq_Rough_Read;
        Serial.print("Pot frequency rough changed new value=");
        Serial.println(pot_Freq_Rough_Read);
      }

      int pot_Freq_Fine_Read = analogRead(pot_Freq_Fine_pin);
      if (abs(pot_Freq_Fine_Read-pot_Freq_Fine_Read_old)>300){
        pot_Freq_Fine_Read_old=pot_Freq_Fine_Read;
        Serial.print("Pot frequency fine changed new value=");
        Serial.println(pot_Freq_Fine_Read);
      }

      int pot_DutyCycle_Read = analogRead(pot_DutyCycle_pin);
      if (abs(pot_DutyCycle_Read-pot_DutyCycle_Read_old)>300){
        pot_DutyCycle_Read_old=pot_DutyCycle_Read;
        Serial.print("Pot dutycycle changed new value=");
        Serial.println(pot_DutyCycle_Read);
      }
  // if (M5.Btn.wasPressed()) {
  //   //Serial print button pressed
  //   Serial.println("Btn was pressed");

    //increase dutycycle
    // dutyCycle++;
    // if (dutyCycle>= 15) dutyCycle=0;

    //Write to PWM controller
    ledcWrite(PWMChannel, dutyCycle);

    //increase PWMchannels and frequency
      // PWMChannel++;
      dutyCycle++;
      freq=freq+100000;
 
    ledc_set_freq(LEDC_HIGH_SPEED_MODE,LEDC_TIMER_0,freq);


    //Serial print updated data
     Serial.printf("Duty = %d  Freq = %d HZ \n", (int)dutyCycle,freq);

    //Display results
    display.clearDisplay();
    display.setTextSize(1);              // Normal 1:1 pixel scale
    display.setTextColor(SSD1306_WHITE); // Draw white text
    display.setCursor(0,0);              // Start at top-left corner
    display.print(F("ZPE V"));
    display.println(F(VERSION));  
    display.println();  
    display.print(F("Duty ="));
    display.println(dutyCycle);  
    display.print(F("Freq = "));
    display.println(freq);
    // ledc_get_freq(LEDC_HIGH_SPEED_MODE,LEDC_TIMER_0);
    display.display();
  // }
  delay(2000);
}
