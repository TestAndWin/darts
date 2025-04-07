#ifndef DARTS_H
#define DARTS_H

#include <TFT_eSPI.h>
#include "Button.h"

enum Screen {
  SCREEN_START = 1,
  SCREEN_PLAYER = 2,
  SCREEN_POINTS = 3,
  SCREEN_BEST_OF = 4,
  SCREEN_GAME = 5,
  SCREEN_DONE = 6
};
const uint8_t MAX_BUTTONS = 25;
const uint8_t MAX_PLAYERS = 4;

class Darts {
private:
  TFT_eSPI &tft;
  int currentScreen;
  int nextScreen;
  // To store all the buttons on the screen
  Button *buttons[MAX_BUTTONS];
  int buttonCount;
  int numberPlayer;
  // Best of how many games
  int bestOf;
  // Number of points to get
  int points;
  // Who is the current player
  int currentPlayer;
  // Number of throws (Aufnahme - 3 darts)
  int throwNumber;
  // To store the points of the current throw (Aufnahme - 3 darts)
  int currentPoints;
  // To store if a double or triple field had been hit
  int dartFactor;
  // To store the remaining points for each player
  int playerPoints[MAX_PLAYERS];
  // To store the number of won sets
  int playerSets[MAX_PLAYERS];
  // Stores the number of throws
  int totalPlayerThrows[MAX_PLAYERS];
  // Stores the total points
  int totalPlayerPoints[MAX_PLAYERS];


  Button **drawScreenStart();
  Button **drawScreenPlayer();
  Button **drawScreenBestOf();
  Button **drawScreenPoints();
  Button **drawScreenGame();
  Button **drawScreenDone();
  void cleanupButtons();
  void nextPlayer();
  void drawScreenTitle(const char *title);
  void handleStartScreen(Button *button);
  void handlePlayerScreen(int idx, Button *button);
  void handleBestOfScreen(Button *button);
  void handlePointsScreen(Button *button);
  void handleGameScreen(int idx, Button *button);
  void handleDoneScreen(Button *button);
  void processGameTurn();

public:
  /**
   * @brief Constructs a Darts object with a reference to a TFT_eSPI object.
   * @param tft Reference to a TFT_eSPI object for display operations.
   */
  Darts(TFT_eSPI &tft);

  /**
   * @brief Initializes the Darts game.
   */
  void init();

  /**
   * @brief Handles button press events.
   * @param idx Index of the button pressed.
   * @param button Pointer to the Button object that was pressed.
   */
  void handleButton(int idx, Button *button);

  /**
   * @brief Draws the current screen and returns the buttons.
   * @return Array of pointers to Button objects.
   */
  Button **drawScreen();

  /**
   * @brief Gets the current screen identifier.
   * @return The identifier of the current screen.
   */
  int getCurrentScreen() {
    return currentScreen;
  }

  /**
   * @brief Gets the next screen identifier.
   * @return The identifier of the next screen.
   */
  int getNextScreen() {
    return nextScreen;
  }

  /**
   * @brief Sets the next screen identifier.
   * @param screen The identifier of the next screen.
   */
  void setNextScreen(int screen) {
    nextScreen = screen;
  }

  /**
   * @brief Gets the count of buttons on the current screen.
   * @return The number of buttons on the current screen.
   */
  int getButtonCount() {
    return buttonCount;
  }

  /**
   * @brief Gets the array of buttons on the current screen.
   * @return Array of pointers to Button objects.
   */
  Button **getButtons() {
    return buttons;
  }
};

#endif