#include "HomeScreen.h"

#include <FEHLCD.h>

enum TouchType HomeScreen::showPlayGame() {
    LCD.Clear(FEHLCD::Black);

    LCD.WriteLine("\"React Go!\"(TM)");
    LCD.WriteLine("Press and hold to play.");
    LCD.WriteLine("Tap to view instructions.");

    return waitForTouch();
}

enum TouchType HomeScreen::showInstructions() {
    LCD.Clear(FEHLCD::Black);

    LCD.WriteLine("Instructions (summary): ");
    LCD.WriteLine("When a colored screen");
    LCD.WriteLine("appears, do this:");
    LCD.WriteLine("- Green: Tap screen.");
    LCD.WriteLine("  Quicker is better");
    LCD.WriteLine("- Blue: Press and hold");
    LCD.WriteLine("  for displayed seconds.");
    LCD.WriteLine("  Hold longer = game over");
    LCD.WriteLine("- Red: Do nothing.");
    LCD.WriteLine("  Touch = game over.");
    LCD.WriteLine("Press and hold to play,");
    LCD.WriteLine("  or tap to view stats.");

    return waitForTouch();
}

enum TouchType HomeScreen::showStats(int bestScore) {
    LCD.Clear(FEHLCD::Black);

    // Check if best score is negative (no best score)
    if (bestScore < 0) {
        LCD.WriteLine("No stats available.");
    } else {
        LCD.Write("Best score: ");
        LCD.WriteLine(bestScore);
    }

    LCD.WriteLine("Press and hold to play,");
    LCD.WriteLine("  or tap to view credits.");

    return waitForTouch();
}

enum TouchType HomeScreen::showCredits() {
    LCD.Clear(FEHLCD::Black);

    LCD.WriteLine("\"React Go!\"(TM) created by");
    LCD.WriteLine("Chan Yuh and Daniel Szoke.");
    LCD.WriteLine("Press and hold to play,");
    LCD.WriteLine("  or tap to view main screen.");

    return waitForTouch();
}
