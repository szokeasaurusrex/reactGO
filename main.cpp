#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include "Game.h"
#include "HomeScreen.h"
#include "sdp_util.h"

int main() {
    LCD.Clear(FEHLCD::Black);
    LCD.SetFontColor(FEHLCD::White);

    // Create game object.
    Game game;

    // Initial best score (negative because game not played yet).
    int bestScore = -1;

    // Loop infinitely
    while (true) {
        // Loop through menus until break statement starts game
        while (true) {
            // Display each screen, if touch was a hold, break.
            if (HomeScreen::showPlayGame() == HOLD) {
                break;
            }

            if (HomeScreen::showInstructions() == HOLD) {
                break;
            }

            if (HomeScreen::showStats(bestScore) == HOLD) {
                break;
            }

            if (HomeScreen::showCredits() == HOLD) {
                break;
            }
        }

        // Play the game
        const int score = game.play();

        // Check if there is a new best score
        if (score >= 0 && (bestScore < 0 || score < bestScore)) {
            bestScore = score;
        }

        // Reset the game
        game.reset();
    }

    return 0;
}