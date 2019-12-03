#ifndef SDP_GAME_H
#define SDP_GAME_H

class Game {
private:
    // Game constants
    static const int RED_SCREENS = 2;
    static const int GREEN_SCREENS = 4;
    static const int BLUE_SCREENS = 2;
    static const int TOTAL_SCREENS = RED_SCREENS + GREEN_SCREENS + BLUE_SCREENS;
    static const unsigned int MIN_DELAY_BETWEEN_SCREENS = 500;
    static const unsigned int MAX_DELAY_BETWEEN_SCREENS = 8000;
    static const unsigned int MIN_BLUE_SCREEN_SECONDS = 2;
    static const unsigned int MAX_BLUE_SCREEN_SECONDS = 8;
    static const unsigned int RED_SCREEN_TIME = 600;
    static const unsigned int GREEN_SCREEN_TIME = 2000;
    static const int MAX_BLUE_SCREEN_SCORE = 3000;

    // Enum class for screen types
    enum ScreenType {RED_SCREEN, GREEN_SCREEN, BLUE_SCREEN};

    // Array of game screens, defines order to perform actions
    enum ScreenType *screens;

    // Score (score < 0 indicates game over)
    int score;

    /**
     * Excecutes Red screen.
     * @return The amount score should increase,
     *      or a negative number if game over (as of 
     *      current game rules, should never return
     *      a positive number).
     */
    static int excecuteRedScreen();

    /**
     * Excecutes Green screen.
     * @return The amount score should increase,
     *      or a negative number if game over (as of current
     *      game rules, should never return negative number).
     */
    static int excecuteGreenScreen();

    /**
     * Excecutes Blue screen.
     * @return The amount score should increase,
     *      or a negative number if game over. (as of current
     *      game rules, should never return negative number).
     */
    static int excecuteBlueScreen();

    /**
     * Waits random amount of time on black screen, displaying score.
     * @param score The score to display.
     * @return The amount score should increase,
     *      or a negative number if game over. As of current game rules,
     *      this method should never return a positive number).
     */
    static int waitOnBlackScreen(int score);

    /**
     * Waits on black screen for random amount of time,
     * then ececutes screens[i].
     * Updates score to appropriate amount.
     * @param screenIdx Index of screen to execute in screens array.
     */
    void excecuteScreen(int screenIdx);

public:
    /**
     * Prints a score to the screen, or displays game over
     * message if the score is negative. Waits until user
     * touches screen before returning execution to calling code.
     * @param score The score to print.
     */
    static void printScore(int score);

    // Constructor and deconstructor
    Game();
    ~Game();

    /**
     * Plays the game.
     * @return The score, or a negative value if game over.
     */
    int play();

    /**
     * Resets score to 0, and screens array to random order.
     */
    void reset();
};

#endif
