#include "webview.h"

/**
 * @brief Generates HTML for an ongoing game (live scoreboard)
 * @param game Pointer to the Darts game instance
 * @return HTML string with the current game state
 */
static String generateOngoingGameHTML(Darts* game) {
  String html = "";
  String tableRows = "";

  int numPlayers = game->getNumberOfPlayers();
  int currentPlayerIdx = game->getCurrentPlayer();
  int setsNeeded = game->getSetsNeeded();

  // Build table rows for all players
  for (int i = 0; i < numPlayers; i++) {
    String prefix = "";
    String throwStr = "-";
    String pointsStr = "-";
    int remainingPoints = 0;

    // Prefix for current player
    if (i == currentPlayerIdx) {
      prefix = "&gt;";
      throwStr = String(game->getThrowNumber());
      pointsStr = String(game->getCurrentPoints());
      remainingPoints = game->getPlayerPoints(i) - game->getCurrentPoints();
    } else {
      remainingPoints = game->getPlayerPoints(i);
    }

    // Build table row
    String row = "<tr";
    if (i == currentPlayerIdx) {
      row += " class='current'";
    }
    row += ">";
    row += "<td>" + prefix + " " + String(i + 1) + "</td>";
    row += "<td class='center'>" + throwStr + "</td>";
    row += "<td class='center'>" + pointsStr + "</td>";
    row += "<td class='right'>" + String(remainingPoints) + "</td>";
    row += "<td class='center'>" + String(game->getPlayerSets(i)) + "/" + String(setsNeeded) + "</td>";
    row += "</tr>";

    tableRows += row;
  }

  // Build complete HTML
  html += "<html>";
  html += "<head>";
  html += "<title>Darts</title>";
  html += "<meta http-equiv='refresh' content='2'>";
  html += "<style>";
  html += "body { font-family: Arial, sans-serif; margin: 40px; }";
  html += "h1 { color: #333; font-size: 36px; }";
  html += "table { border-collapse: collapse; width: 100%; max-width: 920px; margin: 20px 0; box-shadow: 0 2px 8px rgba(0,0,0,0.1); }";
  html += "th { background-color:rgb(24, 106, 161); color: white; padding: 16px; text-align: left; font-size: 28px; }";
  html += "td { padding: 16px; border-bottom: 1px solid #ddd; font-size: 44px; }";
  html += "tr:hover { background-color: #f5f5f5; }";
  html += "tr.current { background-color:rgb(192, 234, 245); font-weight: bold; }";
  html += "tr.current:hover { background-color:rgb(132, 182, 214); }";
  html += ".center { text-align: center; }";
  html += ".right { text-align: right; }";
  html += "</style>";
  html += "</head>";
  html += "<body>";
  html += "<h1>Darts Scoreboard</h1>";
  html += "<table>";
  html += "<thead>";
  html += "<tr>";
  html += "<th>Spieler</th>";
  html += "<th class='center'>Wurf</th>";
  html += "<th class='center'>Punkte</th>";
  html += "<th class='right'>Verbleibend</th>";
  html += "<th class='center'>Sets</th>";
  html += "</tr>";
  html += "</thead>";
  html += "<tbody>";
  html += tableRows;
  html += "</tbody>";
  html += "</table>";
  html += "</body>";
  html += "</html>";

  return html;
}

/**
 * @brief Generates HTML for a finished game (statistics)
 * @param game Pointer to the Darts game instance
 * @return HTML string with game statistics and winner
 */
static String generateFinishedGameHTML(Darts* game) {
  String html = "";
  String tableRows = "";

  int numPlayers = game->getNumberOfPlayers();
  int currentPlayerIdx = game->getCurrentPlayer();

  // Build statistics rows for all players
  for (int i = 0; i < numPlayers; i++) {
    int totalPoints = game->getTotalPlayerPoints(i);
    int totalThrows = game->getTotalPlayerThrows(i);
    int average = (totalThrows > 0) ? ((totalPoints * 3) / totalThrows) : 0;

    // Build statistics row
    String row = "<tr";
    if (i == currentPlayerIdx) {
      row += " class='winner'";
    }
    row += ">";
    row += "<td>" + String(i + 1) + "</td>";
    row += "<td class='center'>" + String(average) + "</td>";
    row += "<td class='center'>" + String(totalPoints) + "</td>";
    row += "<td class='center'>" + String(totalThrows) + "</td>";
    row += "</tr>";

    tableRows += row;
  }

  // Build complete HTML
  html += "<html>";
  html += "<head>";
  html += "<title>Darts - Spiel beendet</title>";
  html += "<meta http-equiv='refresh' content='5'>";
  html += "<style>";
  html += "body { font-family: Arial, sans-serif; margin: 40px; }";
  html += "h1 { color: #333; font-size: 36px; }";
  html += "table { border-collapse: collapse; width: 100%; max-width: 920px; margin: 20px 0; box-shadow: 0 2px 8px rgba(0,0,0,0.1); }";
  html += "th { background-color: rgb(24, 106, 161); color: white; padding: 16px; text-align: left; font-size: 28px; }";
  html += "td { padding: 16px; border-bottom: 1px solid #ddd; font-size: 44px; }";
  html += "tr:hover { background-color: #f5f5f5; }";
  html += "tr.winner { background-color: #FFD700; font-weight: bold; }";
  html += "tr.winner:hover { background-color: #FFC700; }";
  html += ".center { text-align: center; }";
  html += "</style>";
  html += "</head>";
  html += "<body>";
  html += "<h1>Spiel beendet! Gewinner: " + String(currentPlayerIdx + 1) + "</h1>";
  html += "<table>";
  html += "<thead>";
  html += "<tr>";
  html += "<th>Spieler</th>";
  html += "<th class='center'>Durchschnitt (3 Darts)</th>";
  html += "<th class='center'>Total Punkte</th>";
  html += "<th class='center'>Total Würfe</th>";
  html += "</tr>";
  html += "</thead>";
  html += "<tbody>";
  html += tableRows;
  html += "</tbody>";
  html += "</table>";
  html += "</body>";
  html += "</html>";

  return html;
}

String generateGameHTML(Darts* game) {
  // Check if game is finished
  if (game->getCurrentScreen() == SCREEN_DONE) {
    return generateFinishedGameHTML(game);
  } else {
    return generateOngoingGameHTML(game);
  }
}
