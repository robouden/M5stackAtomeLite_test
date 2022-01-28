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

#define VERSION "0.96"

// setting PWM properties

unsigned int freq_base = 1000;
unsigned int freq = 100000;
unsigned int freq_min = 10000;
unsigned int freq_max = 39000000;
unsigned int freq_rough =1;
unsigned int freq_fine =1;
unsigned int freq_superfine =1;

int PWMChannel = 0;
int resolution = 1;
int dutyCycle = 1;
int duty_max=16;
int resolution_max=16;

unsigned int pot_Freq_Rough_Read;
unsigned int pot_Freq_Rough_Read_old;
unsigned int pot_Freq_Fine_Read;
unsigned int pot_Freq_Fine_Read_old;
unsigned int pot_DutyCycle_Read;
unsigned int pot_DutyCycle_Read_old;

int PWM_Pin = 33;  //outpin for driver
int pot_Freq_Rough_pin=39;
int pot_Freq_Fine_pin=32;
int pot_Freq_SuperFine_pin=36;
int pot_Resolution_pin=34;
int pot_DutyCycle_pin=35;

void setup() {
  Serial.begin(115200);
  //I2C setup for display
  Wire.begin(22,21); //I2C 

  //Setup PWM parameters
  ledcSetup(PWMChannel, freq, resolution);
  ledcAttachPin(PWM_Pin, PWMChannel);
  ledcWrite(PWMChannel, dutyCycle);

  // GPIO pins setup
  pinMode(pot_Freq_Rough_pin, ANALOG); // PIN  (INPUT, OUTPUT, ANALOG) //freq rough
  pinMode(pot_Freq_Fine_pin, ANALOG); // PIN  (INPUT, OUTPUT, ANALOG) //freq fine
  pinMode(pot_Freq_SuperFine_pin, ANALOG); // PIN  (INPUT, OUTPUT, ANALOG) //Freq supperfine
  pinMode(pot_Resolution_pin, ANALOG); // PIN  (INPUT, OUTPUT, ANALOG) //Resolution
  pinMode(pot_DutyCycle_pin, ANALOG); // PIN  (INPUT, OUTPUT, ANALOG) //DutyCycle

  // freq_rough = map(analogRead(pot_Freq_Rough_pin), 0, 4096, freq_min, freq_max);
  // freq_fine = map(analogRead(pot_Freq_Fine_pin), 0, 4096, 1000, 10000);

  
  //add fequency and frequency rought and fine
    unsigned int freq=freq_fine+freq_rough+freq_superfine;

  //Display startup serial info
    Serial.println("start setup");
    Serial.printf("Duty = %d  Resolution= %d Freqency = %d HZ \n", (int)dutyCycle,(int)resolution,freq);
    Serial.printf("Version =");
    Serial.println(VERSION);

 //Display startup info
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.clearDisplay();
    display.setTextSize(2);              // Normal 1:1 pixel scale
    display.setTextColor(SSD1306_WHITE); // Draw white text
    display.setCursor(0,0);              // Start at top-left corner
    display.printf("ZPE V%d  \n", (int)VERSION);
    display.printf("Duty = %d  \n", (int)dutyCycle);
    display.printf("Freq = %d  \n", (int)freq);
    display.printf("Resolution = %d  \n", (int)resolution);

    // display.println(F("OUT2 ="));
    display.display();

    //Setup brighter display
    display.ssd1306_command(SSD1306_SETCONTRAST);
    display.ssd1306_command(255);
} 

void loop() {
int freq_rough = map(analogRead(pot_Freq_Rough_pin), 0, 4096, 1, 380);
int freq_fine = map(analogRead(pot_Freq_Fine_pin), 0, 4096, 0, 99);
int freq_superfine = map(analogRead(pot_Freq_SuperFine_pin), 0, 4096, 0, 99);
int dutyCycle = map(analogRead(pot_DutyCycle_pin), 0, 4096, 1, duty_max);
int resolution = map(analogRead(pot_Resolution_pin), 0, 4096, 1, resolution_max);

//Create final frequency base on the two pots
freq_rough=freq_rough*freq_base*1000;
freq_fine=freq_fine*freq_base*100;
freq_superfine =freq_superfine*freq_base*10;
freq=freq_rough+freq_fine+freq_superfine;

if ((freq_min<freq) & (freq<freq_max)){;
      // //Write new data to controller
          ledcSetup(PWMChannel, freq, resolution);
          ledcWrite(PWMChannel, dutyCycle);
          ledc_set_freq(LEDC_HIGH_SPEED_MODE,LEDC_TIMER_0,freq);
  } else{

   Serial.printf("Freq is out of range freq_rough=%d  freq_fine= %d freq_super_fine= %d \n", freq_rough,freq_fine, freq_superfine);
  }

    //Serial print updated data
  Serial.printf("Duty = %d  Resolution= %d Freqency = %d HZ \n", (int)dutyCycle,(int)resolution,freq);

    //Display results
    display.clearDisplay();
    display.setTextSize(1);              // Normal 1:1 pixel scale
    display.setTextColor(SSD1306_WHITE); // Draw white text
    display.setCursor(0,0);              // Start at top-left corner
    display.print(F("ZPE V"));
    display.println(F(VERSION));  
    display.println();  
    display.printf("Duty = %d  \n", (int)dutyCycle);
    display.printf("Freq = %d  \n", (int)freq);
    display.printf("Resolution = %d  \n", (int)resolution);
    display.display();
  delay(1000);
}
