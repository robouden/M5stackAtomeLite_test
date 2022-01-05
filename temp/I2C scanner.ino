#include <M5Atom.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);
 
void setup()
{
  Serial.begin(115200);
  M5.begin(true,false,true);
  Wire.begin(21,25);//I2C
  Serial.println("start setup");

}

void loop()
{
  Serial.println("I2C Scan");
  for (int address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    int error = Wire.endTransmission();
    if (error == 0) {
      Serial.printf("%02X", address);
    } else {
      Serial.print(" .");
    }

    if (address % 16 == 0) {
      Serial.print("\n");
    }

    delay(10);
  }

  Serial.print("\n\n");
  delay(1000);
}