#include <M5Atom.h>


CRGB dispColor(uint8_t r, uint8_t g, uint8_t b) {
  return (CRGB)((r << 8) | (g << 16) | b);
}


float r,g,b;        //LED明るさ指定用（赤、緑、青）
int select =0;


void setup() {
  // initialize serial communication:
    Serial.begin(115200);
    M5.begin(true, false, true);  // (Serial, I2C, NeoPixel)
    Serial.println("start setup");
}

void loop() {
  // read the sensor:

   r=255;
   g=0; 
   b=0;

           M5.dis.drawpix(0, dispColor((int)r, (int)g, (int)b)); //LED点灯
             Serial.println("red");

             
  if (M5.Btn.wasPressed()) {      
    select++;
    switch (select) {
      case 0:
         M5.dis.drawpix(0,  HSVHue::HUE_RED);
             Serial.println("red");
        break;
      case 1:
        M5.dis.drawpix(0,  HSVHue::HUE_BLUE);
        Serial.println("blue");
      case 2:
         M5.dis.drawpix(0,  HSVHue::HUE_GREEN);
         Serial.println("green");
        break;
      case 'd':
        digitalWrite(5, HIGH);
        break;
      case 'e':
        digitalWrite(6, HIGH);
        break;
      default:
        break;
        }
    }
  }


