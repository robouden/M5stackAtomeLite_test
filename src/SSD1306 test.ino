#include <M5Atom.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);
 
void setup() {
  Serial.begin(115200);
  M5.begin(true,false,true);
  Wire.begin(21,25);
  Serial.println("start setup");
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  display.clearDisplay();
  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(20,32);             // Start at top-left corner
  display.println(F("Hello World!"));
  display.display();
}
void loop(){
}