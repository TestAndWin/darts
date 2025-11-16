#include <TFT_eTouch.h>
#include <TFT_eSPI.h>
#include <User_Setup.h>
#include <SPI.h>
#include <WiFi.h>
#include <FS.h>
using fs::FS;
#include <WebServer.h>
#include "Darts.h"
#include "webview.h"
#include "wifi_config.h"

#define ETOUCH_MOSI 32
#define ETOUCH_MISO 39
#define ETOUCH_SCK 25
#define ETOUCH_CS 33
#define ETOUCH_IRQ 0xff
#define TFT_BL 21

WebServer server(80);

SPIClass hSPI(HSPI);
TFT_eSPI tft;
TFT_eTouch<TFT_eSPI> touch(tft, ETOUCH_CS, ETOUCH_IRQ, hSPI);
Darts* game;

void setup() {
  Serial.begin(115200);
  Serial.println("Start");

  // Connect to WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi. IP address: ");
  Serial.println(WiFi.localIP());
  
  // Setup web server
  server.on("/", handleRoot);
  server.begin();
  
  Serial.println("Start Touch");
  hSPI.begin(ETOUCH_SCK, ETOUCH_MISO, ETOUCH_MOSI, ETOUCH_CS);
  tft.begin();
  touch.init();
  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH);

  // Calibration values from calibrate.ino example, from https://github.com/achillhasler/TFT_eTouch
  TFT_eTouchBase::Calibation calibation = { 233, 3785, 3731, 120, 2 };
  touch.setCalibration(calibation);
  tft.setRotation(1);
  // 16px - see user_setup.h
  tft.setTextFont(4);

  Serial.println("Start game");
  game = new Darts(tft);
  game->init();
}

void loop() {
  // Handle web server client requests
  server.handleClient();
  
  static uint32_t last_update = 0;
  if (last_update + touch.getMeasureWait() > millis())
    return;
  last_update = millis();

  static bool is_touched = false;
  int16_t x, y;

  if (touch.getXY(x, y)) {
    if (!is_touched) {
      Serial.printf("X=%d, Y=%d\n", x, y);
      is_touched = true;

      for (int i = 0; i < game->getButtonCount(); i++) {
        Button** buttons = game->getButtons();
        if (buttons[i]->contains(x, y)) {
          game->handleButton(i, buttons[i]);
        }
      }
    }
  } else {
    if (is_touched) {
      is_touched = false;
      touch.reset();
    }
  }

  if (game->getCurrentScreen() != game->getNextScreen()) {
    game->drawScreen();
  }
}

void handleRoot() {
  String html = generateGameHTML(game);
  server.send(200, "text/html", html);
}
