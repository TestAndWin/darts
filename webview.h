#ifndef WEBVIEW_H
#define WEBVIEW_H

#include <Arduino.h>
#include "Darts.h"

/**
 * @brief Generates the complete HTML page for the web interface
 * @param game Pointer to the Darts game instance
 * @return HTML string to be sent to the web client
 */
String generateGameHTML(Darts* game);

#endif
