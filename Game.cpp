#include "Game.h"

#include <FEHUtility.h>
#include <FEHLCD.h>
#include "sdp_util.h"

int Game::excecuteRedScreen() {
    // Draw red screen
    LCD.Clear(FEHLCD::Red);

    // Wait, if touch detected game over, return -1
    const unsigned int timeToStopWait = millis() + RED_SCREEN_TIME;
    while (millis() < timeToStopWait) {
        if (touchDetected()) {
            return -1;
        }
    }

    // No touch detected, return 0
    return 0;
}

int Game::excecuteGreenScreen() {
    // Draw green scren
    LCD.Clear(FEHLCD::Green);
    
    // Get start time and latest end time
    const unsigned int startTime = millis();
    const unsigned int endTime = startTime + GREEN_SCREEN_TIME;

    // Wait until touch detected or end time reached
    while (!touchDetected() && millis() < endTime);

    // Record amount of time it took for user to press screen
    const unsigned int delay = millis() - startTime;

    // Wait until user lets go of screen before returning delay
    while (touchDetected());
    return delay;
}

int Game::excecuteBlueScreen() {
    // Get random time to be on blue screen
    const int blueScreenSeconds = randBetween(MIN_BLUE_SCREEN_SECONDS,
        MAX_BLUE_SCREEN_SECONDS);
    const unsigned int blueScreenMs = blueScreenSeconds * 1000;

    // Draw blue screen, and write how much time to hold for
    LCD.Clear(FEHLCD::Blue);
    LCD.Write("Hold for ");
    LCD.Write(blueScreenSeconds);
    LCD.Write(" seconds.");

    // Get start and end times
    const unsigned int startTime = millis();
    const unsigned int endTime = startTime + blueScreenMs;

    // Wait until touch detected or endTime reached, record time touch detected
    while (!touchDetected() && millis() < endTime);
    const unsigned int touchBeginTime = millis();

    // Wait until touch released or endTime reached
    while (touchDetected() && millis() < endTime);

    // Score increase proportional to blue screen time, minus touch duration.
    const unsigned int rawScore =  blueScreenMs - (millis() - touchBeginTime);

    // Scale score to MAX_BLUE_SCREEN_SCORE
    return (int) rawScore * ((float) MAX_BLUE_SCREEN_SCORE / blueScreenMs);
}

void Game::excecuteScreen(int screenIdx) {
    // First, wait on black screen
    int scoreChange = waitOnBlackScreen(score);

    // If scoreChange was not negative (no game over), excecute the screen
    if (scoreChange >= 0) {
        // Store scoreChange from excecuting screen.
        scoreChange = 0;

        // Determine which screen to excecute
        switch(screens[screenIdx]) {
            case RED_SCREEN:
                scoreChange = excecuteRedScreen();
                break;
            case GREEN_SCREEN:
                scoreChange = excecuteGreenScreen();
                break;
            case BLUE_SCREEN:
                scoreChange = excecuteBlueScreen();
                break;
        }
    }

    // If scoreChange < 0, set score to scoreChange (game over)
    // Otherwise, increment score by scoreChange.
    if (scoreChange < 0) {
        score = scoreChange;
    } else {
        score += scoreChange;
    }
}

int Game::waitOnBlackScreen(int score) {
    // Generate time to wait
    const int timeToWait = randBetween(MIN_DELAY_BETWEEN_SCREENS,
        MAX_DELAY_BETWEEN_SCREENS);
    
    // Generate time to stop waiting
    const unsigned int timeToStopWait = timeToWait + millis();

    // Draw black screen
    LCD.Clear(FEHLCD::Black);

    // Write score to screen
    LCD.Write("Score: ");
    LCD.Write(score);

    // Loop until timeToStopWait
    while (millis() < timeToStopWait) {
        // If touch detected, return -1 after waiting for touch release
        if (touchDetected()) {
            while (touchDetected());
            return -1;
        }
    }

    // No touch detected, return 0
    return 0;
}

void Game::printScore(int score) {
    LCD.Clear(FEHLCD::Black);

    // If score is negative, print game over, otherwise print score
    if (score < 0) {
        LCD.WriteLine("Game over!");
    } else {
        LCD.Write("Your score was ");
        LCD.WriteLine(score);
    }

    LCD.Write("Press the screen to continue.");
    waitForTouch();
}

Game::Game() {
    screens = new ScreenType[TOTAL_SCREENS];
    reset();
}

Game::~Game() {
    delete screens;
}

void Game::reset() {
    // Reset score
    score = 0;

    // Fill screens array
    int redRemaining = RED_SCREENS;
    int greenRemaining = GREEN_SCREENS;
    int blueRemaining = BLUE_SCREENS;
    for (int i = 0; i < TOTAL_SCREENS; i++) {
        // Generate random number to figure out which screen to use
        const int randNum = randBetween(0, TOTAL_SCREENS - i);

        // Assign screens[i] based on random number
        if (randNum < redRemaining) {
            screens[i] = RED_SCREEN;
            redRemaining -= 1;
        } else if (randNum < redRemaining + greenRemaining) {
            screens[i] = GREEN_SCREEN;
            greenRemaining -= 1;
        } else {
            screens[i] = BLUE_SCREEN;
            blueRemaining -= 1;
        }
    }
}

int Game::play() {
    // Excecute all of the screens, ending if score goes below 0 (game over)
    for (int i = 0; i < TOTAL_SCREENS && score >= 0; i++) {
        excecuteScreen(i);
    }

    // Print the score
    printScore(score);

    // Return the score
    return score;
}
