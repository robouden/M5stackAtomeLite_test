//for PWM https://docs.m5stack.com/en/api/pwm
// https://github.com/m5stack/m5-docs/blob/master/docs/en/core/atom_lite.md
// Peripherals Pin Map
// RGB Led	G27
// Btn	G39
// IR	G12


// ledcSetup() is needed
// code from https://shikarunochi.matrix.jp/?p=3859
#include <M5Atom.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);

#define VERSION "0.9"


void setup() {
  Serial.begin(115200);
  M5.begin(true, false, true);  // (Serial, I2C, NeoPixel)
  Wire.begin(21,25);

    // GPIO初期化
  pinMode(22, INPUT); // PIN  (INPUT, OUTPUT,       )
  pinMode(19, INPUT); // PIN  (INPUT, OUTPUT,       )
  pinMode(23, INPUT); // PIN  (INPUT, OUTPUT,       )
  pinMode(33, INPUT); // PIN  (INPUT, OUTPUT, ANALOG)
  pinMode(21, INPUT); // PIN  (INPUT, OUTPUT,       )
  pinMode(25, INPUT); // PIN  (INPUT, OUTPUT, ANALOG)無線利用時にはANALOG利用不可
  pinMode(26, INPUT); // GROVE(INPUT, OUTPUT, ANALOG)無線利用時にはANALOG利用不可, DAC出力可
  pinMode(32, INPUT); // GROVE(INPUT, OUTPUT, ANALOG)

  // 内部ピン初期化
  pinMode(12, OUTPUT_OPEN_DRAIN); // IR赤外線(LOWで出力)
  digitalWrite(12, HIGH);

  // LED(0固定)
  // M5.dis.drawpix(0, CRGB::Green);
  M5.dis.drawpix(0,  HSVHue::HUE_RED);
  //Setup 
  Serial.println("start setup");
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  display.clearDisplay();
  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  display.print(F("ZPE V"));
  display.println(F(VERSION));  
  display.println();  
  display.println(F("IN1 ="));
  display.println(F("IN2 ="));
  display.println(F("OUT1 ="));
  display.println(F("OUT2 ="));
  display.display();
} 
void loop() {
  M5.update();
  if (M5.Btn.wasPressed()) {
    Serial.println("Btn was pressed");
  }
  delay(1);
}
