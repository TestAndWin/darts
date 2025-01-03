#include "TFT_eSPI.h"
#include "Darts.h"

Darts::Darts(TFT_eSPI &tft)
  : tft(tft), currentScreen(0), nextScreen(SCREEN_START), buttonCount(0),
    numberPlayer(0), points(0), currentPlayer(0), currentPoints(0), dartFactor(1), throwNumber(0) {
}

void Darts::init() {
  nextScreen = SCREEN_START;
  numberPlayer = 0;
  currentPlayer = 0;
  currentPoints = 0;
  dartFactor = 1;
  throwNumber = 0;
  drawScreen();
}

void Darts::cleanupButtons() {
  for (int i = 0; i < buttonCount; i++) {
    delete buttons[i];
    buttons[i] = nullptr;
  }
  buttonCount = 0;
}

Button **Darts::drawScreen() {
  currentScreen = nextScreen;
  cleanupButtons();
  switch (currentScreen) {
    case SCREEN_START: return drawScreenStart();
    case SCREEN_PLAYER: return drawScreenPlayer();
    case SCREEN_POINTS: return drawScreenPoints();
    case SCREEN_GAME: return drawScreenGame();
    case SCREEN_DONE: return drawScreenDone();
    default: return nullptr;
  }
}

void Darts::drawScreenTitle(const char *title) {
  tft.fillScreen(TFT_WHITE);
  tft.setTextColor(TFT_GOLD);
  tft.setTextDatum(MC_DATUM);
  tft.drawString(title, tft.getViewportWidth() / 2, 14);
}

Button **Darts::drawScreenStart() {
  drawScreenTitle("Welcome");

  buttonCount = 0;
  buttons[buttonCount++] = new Button(tft, "Start", tft.getViewportWidth() / 2, tft.getViewportHeight() / 2);
  return buttons;
}

Button **Darts::drawScreenPlayer() {
  drawScreenTitle("Number of Players");

  buttonCount = 0;
  buttons[buttonCount++] = new Button(tft, "1 Player", 100, 100);
  buttons[buttonCount++] = new Button(tft, "2 Player", 100, 140);
  return buttons;
}

Button **Darts::drawScreenPoints() {
  drawScreenTitle("Points");

  buttonCount = 0;
  buttons[buttonCount++] = new Button(tft, "201", 100, 60);
  buttons[buttonCount++] = new Button(tft, "301", 100, 100);
  buttons[buttonCount++] = new Button(tft, "401", 100, 140);
  buttons[buttonCount++] = new Button(tft, "501", 100, 180);
  return buttons;
}

Button **Darts::drawScreenGame() {
  char str[20];
  sprintf(str, "Game - Goal %d", points);
  drawScreenTitle(str);
  tft.setTextColor(TFT_BLACK);
  tft.setTextDatum(ML_DATUM);

  for (int i = 0; i < numberPlayer; i++) {
    sprintf(str, "Player %d: %d", i + 1, playerPoints[i]);
    tft.drawString(str, 15, 40 + (i * 24));
    if (i == currentPlayer) {
      tft.drawString("*", 5, 40 + (i * 24));
      sprintf(str, "%d - %d (%d)", throwNumber, currentPoints, playerPoints[i]-currentPoints);
      tft.drawString(str, 180, 40 + (i * 24));
    }
  }

  buttonCount = 0;
  buttons[buttonCount++] = new Button(tft, "0", 20, 100);
  // The buttons 1-20 must in in index at place 1-20, or the handle function must be changed.
  for (int i = 1; i <= 20; i++) {
    char j[2];
    sprintf(j, "%d", i);
    int x = 20 + ((i - 1) % 8 * 40);
    int y = 136 + ((i - 1) / 8 * 36);
    buttons[buttonCount++] = new Button(tft, j, x, y);
  }
  buttons[buttonCount++] = new Button(tft, "25", 180, 208);

  buttons[buttonCount++] = new Button(tft, "Double", 120, 100);
  if (dartFactor == 2) {
    tft.drawString("*", 65, 100);
  }
  buttons[buttonCount++] = new Button(tft, "Triple", 240, 100);
  if (dartFactor == 3) {
    tft.drawString("*", 195, 100);
  }

  buttons[buttonCount++] = new Button(tft, "X", 300, 220);
  return buttons;
}

Button **Darts::drawScreenDone() {
  drawScreenTitle("Winner");

  char str[10];
  sprintf(str, "Player %d", currentPlayer + 1);
  tft.drawString(str, 50, 50);

  buttonCount = 0;
  buttons[buttonCount++] = new Button(tft, "Next Round", tft.getViewportWidth() / 2, tft.getViewportHeight() / 2);
  return buttons;
}

void Darts::handleButton(int idx, Button *button) {
  switch (currentScreen) {
    case SCREEN_START: handleStartScreen(button); break;
    case SCREEN_PLAYER: handlePlayerScreen(button); break;
    case SCREEN_POINTS: handlePointsScreen(button); break;
    case SCREEN_GAME: handleGameScreen(idx, button); break;
    case SCREEN_DONE: handleDoneScreen(button); break;
  }
}

void Darts::handleStartScreen(Button *button) {
  nextScreen = SCREEN_PLAYER;
}

void Darts::handlePlayerScreen(Button *button) {
  if (strcmp(button->getLabel(), "1 Player") == 0) {
    numberPlayer = 1;
  } else if (strcmp(button->getLabel(), "2 Player") == 0) {
    numberPlayer = 2;
  }
  nextScreen = SCREEN_POINTS;
}

void Darts::handlePointsScreen(Button *button) {
  points = (int)strtol(button->getLabel(), (char **)NULL, 10);
  for (int i = 0; i < MAX_PLAYERS; i++) {
    playerPoints[i] = points;
  }
  nextScreen = SCREEN_GAME;
}

// TODO Anzahl der Würfe zählen, und Avg Scores anzeigen
void Darts::handleGameScreen(int idx, Button *button) {
  if (strcmp(button->getLabel(), "X") == 0) {
    nextScreen = SCREEN_START;
  } else if (strcmp(button->getLabel(), "Delete") == 0) {
    currentPoints = 0;
    dartFactor = 1;
    throwNumber = 0;
  } else if (strcmp(button->getLabel(), "Double") == 0) {
    dartFactor = 2;
  } else if (strcmp(button->getLabel(), "Triple") == 0) {
    dartFactor = 3;
  } else if (strcmp(button->getLabel(), "0") == 0) {
    dartFactor = 1;
    throwNumber++;
  } else if (strcmp(button->getLabel(), "25") == 0) {
    if (dartFactor == 3) dartFactor = 2;  // there is no triple 25
    currentPoints = currentPoints + (25 * dartFactor);
    dartFactor = 1;
    throwNumber++;
  }
  if (idx > 0 && idx < 21) {
    currentPoints = currentPoints + (idx * dartFactor);
    dartFactor = 1;
    throwNumber++;
  }
  Serial.println(idx);
  Serial.println(throwNumber);
  Serial.println(dartFactor);
  Serial.println(currentPoints);

  if (playerPoints[currentPlayer] - currentPoints == 0) {
    playerPoints[currentPlayer] = 0;
    nextScreen = SCREEN_DONE;
    return;
  }
  if (playerPoints[currentPlayer] - currentPoints < 0) {
    nextPlayer();
  }

  if (throwNumber == 3) {
    playerPoints[currentPlayer] = playerPoints[currentPlayer] - currentPoints;
    nextPlayer();
  }
  drawScreen();
}

void Darts::nextPlayer() {
  currentPoints = 0;
  dartFactor = 1;
  throwNumber = 0;
  currentPlayer++;
  if (currentPlayer > (numberPlayer - 1)) {
    currentPlayer = 0;
  }
}

void Darts::handleDoneScreen(Button *button) {
  init();
}