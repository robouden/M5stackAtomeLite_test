# 1 "/tmp/tmpvfmh2p2e"
#include <Arduino.h>
# 1 "/home/rob/Documents/PlatformIO/Projects/M5stackAtomeLite_test/src/Serial read and switch case.ino"
#include <M5Atom.h>
CRGB dispColor(uint8_t r, uint8_t g, uint8_t b);
void setup();
void loop();
#line 4 "/home/rob/Documents/PlatformIO/Projects/M5stackAtomeLite_test/src/Serial read and switch case.ino"
CRGB dispColor(uint8_t r, uint8_t g, uint8_t b) {
  return (CRGB)((r << 8) | (g << 16) | b);
}


float r,g,b;
int select =0;


void setup() {

    Serial.begin(115200);
    M5.begin(true, false, true);
    Serial.println("start setup");
}

void loop() {

 if (M5.Btn.wasPressed()) {
   r=255;
   g=0;
   b=0;

           M5.dis.drawpix(0, dispColor((int)r, (int)g, (int)b));
             Serial.println("red");
    select++;
    switch (select) {
      case 0:
         M5.dis.drawpix(0, HSVHue::HUE_RED);
             Serial.println("red");
        break;
      case 1:
        M5.dis.drawpix(0, HSVHue::HUE_BLUE);
        Serial.println("blue");
      case 2:
         M5.dis.drawpix(0, HSVHue::HUE_GREEN);
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