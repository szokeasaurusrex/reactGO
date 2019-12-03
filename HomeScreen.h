#ifndef HOME_SCREEN
#define HOME_SCREEN

#include "sdp_util.h"

/**
 * Functions relating to game's home screen.
 * All functions print some kind of info, and
 * wait for touch, returning type of touch detected.
 */
namespace HomeScreen {
    /**
     * Displays screen telling user how to start gameplay.
     * @return Type of touch detected.
     */
    enum TouchType showPlayGame();

    /**
     * Displays the instructions for playing game.
     * @return Type of touch detected.
     */
    enum TouchType showInstructions();

    /**
     * Shows the game stats (i.e. current best score).
     * @param bestScore The current best score. A negative
     *      value indicates that no best score exists.
     * @return Type of touch detected.
     */
    enum TouchType showStats(int bestScore);

    /**
     * Shows game credits.
     * @return Type of touch detected.
     */
    enum TouchType showCredits();
}

#endif