#ifndef BUTTON_H
#define BUTTON_H

#include <TFT_eSPI.h>

/**
 * @brief Represents a Button
 */
class Button {
private:
  int16_t x1, y1, x2, y2;
  char *label;
  TFT_eSPI &tft;

public:
  /**
   * Creates a new button centered at the specified coordinates
   * @param tft Reference to the TFT display
   * @param label Text to display on the button
   * @param x Center x-coordinate for the button
   * @param y Center y-coordinate for the button
   */
  Button(TFT_eSPI &tft, char *label, int16_t x, int16_t y);

  /**
   * Renders the button on the TFT display
   * Draws a rounded rectangle with the label centered inside
   * @param x Center x-coordinate for the button
   * @param y Center y-coordinate for the button
   */
  void draw(int16_t x, int16_t y);

  /**
   * Checks if given coordinates are within button boundaries
   * @param x X-coordinate to test
   * @param y Y-coordinate to test
   * @return true if point is inside button, false otherwise
   */
  bool contains(int16_t x, int16_t y);

  /**
   * Returns the button's label text
   * @return Pointer to the button's label string
   */
  char *getLabel() {
    return label;
  }
};

#endif
