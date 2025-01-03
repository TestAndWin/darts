#include "Button.h"

Button::Button(TFT_eSPI &tft, char *label, int16_t x, int16_t y)
  : tft(tft), label(label) {
  draw(x, y);
}

void Button::draw(int16_t x, int16_t y) {
  int16_t w = tft.textWidth(label) + 10;
  int16_t h = tft.fontHeight() + 6;
  x1 = x - (w / 2);
  y1 = y - (h / 2);
  x2 = x1 + w;
  y2 = y1 + h;
  tft.drawRoundRect(x1, y1, w, h, 1, TFT_BLACK);
  tft.fillRoundRect(x1 + 1, y1 + 1, w - 2, h - 2, 1, TFT_LIGHTGREY);
  tft.setTextColor(TFT_BLACK);
  tft.setTextDatum(MC_DATUM);
  tft.drawString(label, x, y, 4);
}

bool Button::contains(int16_t x, int16_t y) {
  return (x >= x1 && x <= x2 && y >= y1 && y <= y2);
}
