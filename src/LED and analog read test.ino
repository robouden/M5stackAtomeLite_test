#include <M5Atom.h>   //Atomのヘッダファイルを準備

//From https://logikara.blog/prog_atom_led_ctrl/
// FastLEDライブラリの設定（CRGB構造体）
CRGB dispColor(uint8_t r, uint8_t g, uint8_t b) {
  return (CRGB)((r << 8) | (g << 16) | b);
}
// 変数宣言
float an_val;       //アナログ換算値（0～4095）格納用
float an_volt;      //アナログ電圧（0～3.3V）格納用
float r,g,b;        //LED明るさ指定用（赤、緑、青）
int cnt = 0;        //シリアル表示周期カウント用

// 初期設定 -----------------------------------------------
void setup() {
  M5.begin(true, false, true);  //Serial,POWER,LED
  Serial.begin(115200);           //標準のシリアル通信設定
  pinMode(33, ANALOG);          //アナログ入力端子設定
}
// メイン -------------------------------------------------
void loop() {
  r = 255;  //LED赤色0リセット
  g = 255;  //LED緑色0リセット
  b = 255;  //LED青色0リセット

  // アナログ入力処理
  an_val = analogRead(33);          //アナログ換算値（0～4095）取得
  an_volt = (3.3 / 4095) * an_val;  //アナログ電圧（0～3.3V）換算

  M5.dis.drawpix(0, dispColor((int)r, (int)g, (int)b)); //LED点灯

  //シリアル出力周期（10ms × 100 = 1000ms）
  if(cnt == 100) {                //周期カウント100でシリアル出力
    // AN:アナログ値　VOLT：アナログ電圧換算値　LED色指定値（R,G,B）
    Serial.printf("AN = %d  VOLT = %1.2fV  R,G,B = %d, %d, %d\n",
                  (int)an_val, an_volt, (int)r, (int)g, (int)b);
    cnt = 0;  //周期カウント0リセット
  }
  cnt++;      //周期カウント+1
  delay(10);  //10ms待機
}