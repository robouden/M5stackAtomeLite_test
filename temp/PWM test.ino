#include <M5Atom.h>

//from https://forum.micropython.org/viewtopic.php?t=3717
// The maximum PWM frequency with the currently used ledc duty resolution of 10 bits in PWM module is 78.125KHz.
// The duty resolution can be lowered down to 1 bit in which case the maximum frequency is 40 MHz, but only the duty of 50% is available.
// For duty resolution of 8 buts, the maximal frequency is 312.5 kHz.
// The available duty levels are (2^bit_num)-1, where bit_num can be 1-15.
// The maximal frequency is 80000000 / 2^bit_num

//Atom Lite pins
// PIN Port	G19, G21，G22，G23，G25, G33
  // RGB Led	G27
  // Btn	    G39
  // IR	      G12

// the number of the PWM pin
const int PWMPin = 19;  
// setting PWM properties
const int freq = 5000000;
const int PWMChannel = 0;
const int resolution = 4;
int dutyCycle = 2;
 
void setup(){
  Serial.begin(115200);
  M5.begin(true, false, true);  // (Serial, I2C, NeoPixel)
  // Wire.begin(21,25);//I2C
  Serial.println("start setup");
  Serial.printf("Duty = %d  Freq = %d HZ \n", (int)dutyCycle,freq);
  // configure LED PWM functionalitites
  ledcSetup(PWMChannel, freq, resolution);
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(PWMPin, PWMChannel);
  ledcWrite(PWMChannel, dutyCycle);
}
 
void loop(){
  // // increase the LED brightness
  // for(int dutyCycle = 0; dutyCycle <= 255; dutyCycle++){   
    // changing the LED brightness with PWM

    // dutyCycle = 255;
    // ledcWrite(PWMChannel, dutyCycle);
    // delay(15);
  // }

  // // decrease the LED brightness
  // for(int dutyCycle = 255; dutyCycle >= 0; dutyCycle--){
  //   // changing the LED brightness with PWM
  //   ledcWrite(PWMChannel, dutyCycle);   
  //   delay(15);
  // }
}