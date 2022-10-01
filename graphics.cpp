/*
 * Module 4 Large Project: The "Locked Cabin" Escape Game
 * Contributers: Samuel Clear and Noah Schonhorn
 * CS 120: Advanced C++ Programming
 * Professor Dion
 * 04/19/2022
 *
 * This file contains the major implementations of the graphics functionality for the game.
 * First, each of the game's sprites which were created with OpenGL "Quad" objects were
 * initialized before the code, along with conditional statements which change their
 * location and presence on the screen based on which screen or wall the user is currently
 * viewing, as well as the position of each item on the screen! Secondly, a series of
 * Boolean statements record whether certain items have been interacted with or certain
 * events have occurred. This allows the programmer to clearly identify which events are
 * occurring at any time in the program, along with improve readability and event management
 * in the program. Thirdly, the display function contains implementations of each screen
 * and wall the player is on over the course of the game, which functions as a series of
 * stages the player travels through in the game. The user can click on the start button to
 * start the game, as well as click on items such as the Hammer, Candle, and Lighter to
 * pick up the items and click on them in the user's inventory bar to utilize them to
 * interact with other background items such as the vase, table, and safe. Fourthly,
 * the file takes in user inputs to control which wall the user is looking at
 * ("a" and "d"), and the exit function to quit the game ("q" or ESC). Fifth, The mouse
 * accepts inputs based on which object is being hovered over. These mouse inputs are
 * interpreted differently based on which events have happened previously, which is
 * recorded in the documentation below and in global boolean variables recorded in the
 * first section of this code. Specifically, mouse inputs are taken in to determine which
 * item is being selected or used, as well as which item is currently being used to
 * interact with another item or background object. Sixth, the glut timer functions
 * are used to record the remaining game time, the time between each light flicker in
 * the game, and the overall decreasing light during the game. Seventh and finally,
 * the main function and timer function, along with other vital functions for the
 * game are initialized and the game is run! Ultimately, the different item
 * interactions programmed into the display function, the timer functions, the
 * keyboard function, and the mouse function implementations by our project members
 * allow for the game to effectively view and interact with the different items and
 * background images for the game, as well as control what scene the player is viewing
 * in the game with the different walls, and finally control the different events around
 * the moving world in the cabin.
 *
 * To summarize...
 * Keyboard Inputs: Changing which wall the user is facing, exiting the game
 * Mouse Inputs: Picking up any of the 9 interactable items, as well as
 *               equipping the items from inventory and interacting with background objects
 *               based on the objects equipt.
 * Timer Functions: Controlling the global time of the game, the light level at different
 *                  stages of the game, the changes in light level when the candlelight "flickers", and
 *                  timing the emphatic pause if the user loses the game.
 */

#include "graphics.h"
#include "Interactable.h"
#include "objects/Painting.hpp"
#include "objects/Hammer.hpp"
#include "objects/Door.hpp"
#include "objects/Vase.hpp"
#include <cmath>
#include <vector>
using namespace std;

// Required functions for OpenGL and Glut implementations
GLdouble width, height;
int wd;

// Timer Global Variables to manage the current light level,
// initial flickering status, and current timer accumulators
float lightLevel = 1.0;
bool flickering = false;
const int TIME_LIMIT = 100;
const float LIGHT_LEVEL_CHANGE = 0.8;
int stopTimer;
int stopTimerEnd;
bool endTimerContinue;
string timeRemaining;

// Initial start button presented to the user
Interactable startButton({1, 1, 1}, {250, 290}, 100, 25, "START");

// Custom Sprites
Interactable shading({0.0f, 0.0f, 0.0f}, {250, 250}, 500, 500, "");
Painting painting(250, 250);
Hammer hammer(300, 100);
Door door(50, 200);
Vase vase(400, 400);
Interactable selectedItem({0.6f, 0.6f, 0.0f}, {600, 600}, 20, 40, "");

Quad floorCabin({71.0/255.0,41.0/255.0,4.0/255.0}, {250, 440}, 500, 300);

Interactable candleBottom{{230.0 / 255.0, 244.0 / 255.0, 214.0 / 255.0}, {250, 230}, 6, 20, ""};
Interactable candleWick{{0.2, 0.2, 0.2}, {250, 216}, 2, 8, ""};
Interactable candleLightTop{{1, 1, 0}, {250, 209}, 6, 6, ""};
Interactable candleLightFlare{{1, 0.6, 0}, {250, 205}, 2, 2, ""};

Interactable candleExtraBody{{230.0 / 255.0, 244.0 / 255.0, 214.0 / 255.0}, {170, 206}, 6, 20, ""};
Interactable candleExtraWick{{0.2, 0.2, 0.2}, {170, 192}, 2, 8, ""};
Interactable candleExtraLightTop{{1, 1, 0}, {170, 185}, 6, 6, ""};
Interactable candleExtraLightFlare{{1, 0.6, 0}, {170, 181}, 2, 2, ""};

Interactable lighterBody{{50.0 / 255.0, 205.0 / 255.0, 50.0 / 255.0}, {120, 242}, 12, 16, ""};
Interactable lighterTrigger{{0.7, 0.0, 0.0}, {122, 230}, 8, 4, ""};
Interactable lighterTriggerStick{{0.6, 0.1, 0.1}, {122, 232}, 2, 6, ""};
Interactable lighterFlameGuard{{202.0 / 255.0, 204.0 / 255.0, 206.0 / 255.0}, {116, 230}, 4, 8, ""};

Interactable tableBody{{107.0 / 255.0, 67.0 / 255.0, 30.0 / 255.0}, {200, 224}, 100, 16, ""};
Interactable tableLeftLeg{{107.0 / 255.0, 67.0 / 255.0, 30.0 / 255.0}, {154, 260}, 8, 60, ""};
Interactable tableRightLeg{{107.0 / 255.0, 67.0 / 255.0, 30.0 / 255.0}, {246, 260}, 8, 60, ""};
Interactable tableCubbord{{0.0 / 255.0, 0.0 / 255.0, 0.0 / 255.0}, {200, 225}, 20, 8, ""};

Interactable envelopeBody{{225.0 / 255.0, 198.0 / 255.0, 153.0 / 255.0}, {300, 100}, 60, 40, ""};
Interactable envelopeFlapLine{{249.0 / 255.0, 228.0 / 255.0, 183.0 / 255.0}, {300, 95}, 50, 30, ""};
Interactable envelopeSeal{{194.0 / 255.0, 24.0 / 255.0, 7.0 / 255.0}, {300, 110}, 8, 6, ""};

Interactable safeBody{{20.0 / 255.0, 20.0 / 255.0, 20.0 / 255.0}, {250, 290}, 100, 100, ""};
Interactable safeKeypad{{33.0 / 255.0, 33.0 / 255.0, 33.0 / 255.0}, {270, 290}, 40, 40, ""};
Interactable safeKeypadScreen{{0.0 / 255.0, 32.0 / 255.0, 32.0 / 255.0}, {270, 280}, 34, 10, ""};
Interactable safeKeypadButton1{{50.0 / 255.0, 16.0 / 255.0, 0.0 / 255.0}, {258, 292}, 6, 6, ""};
Interactable safeKeypadButton2{{50.0 / 255.0, 16.0 / 255.0, 0.0 / 255.0}, {270, 292}, 6, 6, ""};
Interactable safeKeypadButton3{{50.0 / 255.0, 16.0 / 255.0, 0.0 / 255.0}, {282, 292}, 6, 6, ""};
Interactable safeKeypadButton4{{50.0 / 255.0, 16.0 / 255.0, 0.0 / 255.0}, {258, 302}, 6, 6, ""};
Interactable safeKeypadButton5{{50.0 / 255.0, 16.0 / 255.0, 0.0 / 255.0}, {270, 302}, 6, 6, ""};
Interactable safeKeypadButton6{{50.0 / 255.0, 16.0 / 255.0, 0.0 / 255.0}, {282, 302}, 6, 6, ""};

Interactable tumblerBody{{74.0 / 255.0, 71.0 / 255.0, 72.0 / 255.0}, {300, 100}, 4, 36, ""};
Interactable tumblerEdgeMiddle{{74.0 / 255.0, 71.0 / 255.0, 72.0 / 255.0}, {297, 88}, 2, 4, ""};
Interactable tumblerEdgeBottom{{74.0 / 255.0, 71.0 / 255.0, 72.0 / 255.0}, {296, 96}, 4, 6, ""};

Interactable lockpickBody{{104.0 / 255.0, 101.0 / 255.0, 102.0 / 255.0}, {200, 300}, 4, 28, ""};
Interactable lockpickHead{{104.0 / 255.0, 101.0 / 255.0, 102.0 / 255.0}, {196, 287}, 10, 2, ""};
Interactable lockpickTooth{{104.0 / 255.0, 101.0 / 255.0, 102.0 / 255.0}, {192, 289}, 2, 4, ""};

Interactable leatherStrap{{78.0 / 255.0, 16.0 / 255.0, 10.0 / 255.0}, {10, 250}, 24, 10, ""};
Interactable chainLock{{204.0 / 255.0, 201.0 / 255.0, 202.0 / 255.0}, {90, 150}, 24, 4, ""};

Interactable padLock1Body{{64.0 / 255.0, 61.0 / 255.0, 62.0 / 255.0}, {11, 150}, 14, 14, ""};
Interactable padLock1TopHole{{14.0 / 255.0, 11.0 / 255.0, 12.0 / 255.0}, {11, 148}, 4, 4, ""};
Interactable padLock1BottomHole{{14.0 / 255.0, 11.0 / 255.0, 12.0 / 255.0}, {11, 152}, 2, 6, ""};
Interactable padLock1LeftNeck{{104.0 / 255.0, 101.0 / 255.0, 102.0 / 255.0}, {7, 141}, 4, 8, ""};
Interactable padLock1RightNeck{{104.0 / 255.0, 101.0 / 255.0, 102.0 / 255.0}, {15, 141}, 4, 8, ""};
Interactable padLock1TopNeck{{104.0 / 255.0, 101.0 / 255.0, 102.0 / 255.0}, {11, 139}, 8, 4, ""};

Interactable padLock2Body{{64.0 / 255.0, 61.0 / 255.0, 62.0 / 255.0}, {90, 250}, 14, 14, ""};
Interactable padLock2TopHole{{14.0 / 255.0, 11.0 / 255.0, 12.0 / 255.0}, {90, 248}, 4, 4, ""};
Interactable padLock2BottomHole{{14.0 / 255.0, 11.0 / 255.0, 12.0 / 255.0}, {90, 252}, 2, 6, ""};
Interactable padLock2LeftNeck{{104.0 / 255.0, 101.0 / 255.0, 102.0 / 255.0}, {86, 241}, 4, 8, ""};
Interactable padLock2RightNeck{{104.0 / 255.0, 101.0 / 255.0, 102.0 / 255.0}, {94, 241}, 4, 8, ""};
Interactable padLock2TopNeck{{104.0 / 255.0, 101.0 / 255.0, 102.0 / 255.0}, {90, 239}, 8, 4, ""};

Interactable keyHead{{205.0 / 255.0, 127.0 / 255.0, 50.0 / 255.0}, {250, 290}, 10, 10, ""};
Interactable keyBody{{205.0 / 255.0, 127.0 / 255.0, 50.0 / 255.0}, {250, 282}, 4, 16, ""};
Interactable keyToothTop{{205.0 / 255.0, 127.0 / 255.0, 50.0 / 255.0}, {248, 276}, 8, 4, ""};
Interactable keyToothMiddle{{205.0 / 255.0, 127.0 / 255.0, 50.0 / 255.0}, {248, 279}, 6, 2, ""};
Interactable keyToothBottom{{205.0 / 255.0, 127.0 / 255.0, 50.0 / 255.0}, {250, 290}, 10, 6, ""};

Interactable bombBody{{24.0 / 255.0, 21.0 / 255.0, 22.0 / 255.0}, {400, 400}, 16, 16, ""};
Interactable bombNeck{{24.0 / 255.0, 21.0 / 255.0, 22.0 / 255.0}, {400, 392}, 12, 6, ""};
Interactable bombFuse{{248.0 / 255.0, 223.0 / 255.0, 161.0 / 255.0}, {400, 386}, 4, 10, ""};

Interactable knifeHandle{{102.0 / 255.0, 51.0 / 255.0, 0.0 / 255.0}, {350, 62}, 4, 10, ""};
Interactable knifeBladeBack{{114.0 / 255.0, 111.0 / 255.0, 112.0 / 255.0}, {349, 46}, 6, 22, ""};
Interactable knifeBladeEdge{{202.0 / 255.0, 204.0 / 255.0, 206.0 / 255.0}, {345, 49}, 2, 16, ""};
Interactable knifeBladeTopEdge{{202.0 / 255.0, 204.0 / 255.0, 206.0 / 255.0}, {350, 34}, 4, 2, ""};
Interactable knifeUpperFarEdge{{202.0 / 255.0, 204.0 / 255.0, 206.0 / 255.0}, {345, 53}, 4, 8, ""};

Interactable ironRodBody{{114.0 / 255.0, 111.0 / 255.0, 112.0 / 255.0}, {246, 260}, 8, 44, ""};
Interactable ironRodTop{{0.0 / 255.0, 0.0 / 255.0, 0.0 / 255.0}, {246, 272}, 4, 4, ""};

// Enumerated datatypes to determine clearly which stage of the game the player is in
enum screenEnum{startScreen, gameScreen, endScreen};
enum walls{frontWall, leftWall, backWall, rightWall};

// Initial starting screen and wall ("stage" of the game) the player starts in
screenEnum currentScreen = startScreen;
walls currentWall = frontWall;

// Boolean variable, which keep track of if start button has been pressed
bool startPressed = false;

// Boolean variable checking if the user has escaped the cabin!
bool escaped = false;

// Booleans for each object, indicating whether the player has picked them up yet or not
bool candlePressed = false;
bool knifePressed = false;
bool lighterPressed = false;
bool rodPressed = false;
bool hammerPressed = false;
bool bombPressed = false;
bool tumblerPressed = false;
bool lockpickPressed = false;
bool keyPressed = false;

// Booleans for each object, indicating whether the user has an item currently equipt
bool candleEquipt = false;
bool knifeEquipt = false;
bool lighterEquipt = false;
bool rodEquipt = false;
bool hammerEquipt = false;
bool bombEquipt = false;
bool tumblerEquipt = false;
bool lockpickEquipt = false;
bool keyEquipt = false;

// Booleans indicating whether events have occurred in during the game
bool paintingBurnt = false;
bool vaseBroken = false;
bool safeBroken = false;
bool legCutOff = false;
bool cubbordSearched = false;
bool envelopeOpened = false;
bool candleLit = false;
bool rodPlacedInChain = false;
bool tumblerSet = false;
bool leatherStrapBurned = false;
bool chainSnapped = false;
bool topLeftLockUnlocked = false;
bool bottomRightLockUnlocked = false;

/*
 * intToColor Function
 * Input: Integer indicating the given color value for either red, green, or blue
 * Output: The given color, converted into the RGB Ratio
 */
float intToColor(unsigned int intColor)
{
    float conv = static_cast<float>(intColor) / 255.0f;

    if (conv > 1.0f)
    {
        conv = 1.0f;
    }
    else if (conv < 0.0f)
    {
        conv = 0.0f;
    }

    return conv;
}

// Colors of each wall
color frontColor = {intToColor(145), intToColor(145), intToColor(145)};
color leftColor = {intToColor(66), intToColor(18), intToColor(40)};
color backColor = {intToColor(54), intToColor(33), intToColor(11)};
color rightColor = {intToColor(0x57), intToColor(0x67), intToColor(0x77)};

// Init function, initializing the first variables in the program
void init() {
    width = 500;
    height = 500;
    srand(time(0));
    painting.move(100, -200);
    shading.setAlpha(0.0f);
}

/* Initialize OpenGL Graphics */
void initGL() {
    // Set "clearing" or background color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black and opaque
}

// Display function, which controls which stage the player is at in the game.
void display() {

    // Initialize OpenGL Viewpoint to the center of the screen
    glViewport(0, 0, width, height);

    // do an orthographic parallel projection with the coordinate
    // system set to first quadrant, limited by screen/window size
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, width, height, 0.0, -1.f, 1.f);

    glClear(GL_COLOR_BUFFER_BIT);   // Clear the color buffer with current clearing color

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // String variable which prints to the user how much time is remaining in the game
    timeRemaining = to_string(100 - stopTimer);

    /*
     * This switch statement, which contains an additional switch statement in the "gameScreen" case,
     * controls which stage of the game the user is currently in. Dependent on which "screen" the
     * player is currently at, or which "wall" the user is currently facing, there is multiple
     * possible events the user can interact with. For example, when the user is facing the front
     * wall, the user can interact with the painting if they have the lighter equipt. The user can
     * only interact with the painting if they are at the front wall, and they can only pick up the
     * lighter if they are facing the lighter. For objects that are accessible on whichever wall
     * the user is facing, such as the shading of each room and whichever items the player has in
     * their inventory, these items are displayed below the switch statements below.
     */
    switch(currentScreen) {

        // Initial screen the user begins in
        case startScreen:

            // Draw spawn button
            startButton.draw();

            // Prompt the user with the controls, and to press the start button
            glColor3f(1, 1, 1);
            glRasterPos2i(105, 170);
            for (const char &letter: "A Locked Cabin") {
                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
            }
            glColor3f(1, 1, 1);
            glRasterPos2i(105, 190);
            for (const char &letter: "Controls:") {
                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
            }
            glColor3f(1, 1, 1);
            glRasterPos2i(105, 200);
            for (const char &letter: "Press \"a\" to turn left") {
                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
            }
            glColor3f(1, 1, 1);
            glRasterPos2i(105, 210);
            for (const char &letter: "Press \"d\" to turn left") {
                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
            }
            glColor3f(1, 1, 1);
            glRasterPos2i(105, 220);
            for (const char &letter: "LEFT CLICK to interact, or ") {
                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
            }
            glColor3f(1, 1, 1);
            glRasterPos2i(105, 230);
            for (const char &letter: "equip an item in your inventory bar") {
                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
            }
            glColor3f(1, 1, 1);
            glRasterPos2i(105, 240);
            for (const char &letter: "ESC or q to quit the game") {
                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
            }
            glColor3f(1, 1, 1);
            glRasterPos2i(105, 260);
            for (const char &letter: "Click the START Interactable to Start!") {
                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
            }

            // If the start button is clicked, then the player is moved to the "gameScreen" stage
            if (startPressed) {
                currentScreen = gameScreen;
            }
            break;

        // Next, the user is brought into the main game which includes of different events,
        // that are interactable dependent on which wall the user is on!
        case gameScreen:

            // No matter which wall the user is on, the highlighted object (if any item is equipt)
            // and the floor of the cabin is always spawned.
            selectedItem.draw();
            floorCabin.draw();

            // If at the front wall, the user can interact with the knife, painting, lighter,
            // and multiple different background objects. Objects such as the painting and the different door locks
            // require for an event to have occurred to change the appearance of the objects, such as placing an iron
            // rod in the door chain, or burning the painting with the lighter. Along with this, the knife cannot be
            // picked up unless the painting has been burnt away, simulating the player having to get past
            // the painting to access the knife.
            if (currentWall == frontWall) {
                glClearColor(frontColor.red, frontColor.green, frontColor.blue, 1.0f);

                // Objects are automatically displayed
                painting.render();
                door.render();

                // If the painting has been burnt, display the knife over the painting
                if (paintingBurnt) {
                    knifeHandle.draw();
                    knifeUpperFarEdge.draw();
                    knifeBladeBack.draw();
                    knifeBladeTopEdge.draw();
                }

                // Lighter is Drawn
                lighterTriggerStick.draw();
                lighterBody.draw();
                lighterTrigger.draw();
                lighterFlameGuard.draw();

                // If the Top-Left padlock is not unlocked, then display the lock
                if (!topLeftLockUnlocked) {
                    padLock1Body.draw();
                    padLock1BottomHole.draw();
                    padLock1TopHole.draw();
                    padLock1TopNeck.draw();
                    padLock1LeftNeck.draw();
                    padLock1RightNeck.draw();
                }

                // If the tumbler has been set by the user (event!) and the lock hasn't been
                // unlocked, then the tumbler is placed into the lock
                if (tumblerSet && !topLeftLockUnlocked) {
                    tumblerBody.reinitializeCenter(11, 130);
                    tumblerEdgeMiddle.reinitializeCenter(8, 118);
                    tumblerEdgeBottom.reinitializeCenter(7, 126);
                    tumblerBody.draw();
                    tumblerEdgeMiddle.draw();
                    tumblerEdgeBottom.draw();
                }

                // If the Bottom-right padlock is not unlocked, then display the lock
                if (!bottomRightLockUnlocked) {
                    padLock2Body.draw();
                    padLock2BottomHole.draw();
                    padLock2TopHole.draw();
                    padLock2TopNeck.draw();
                    padLock2LeftNeck.draw();
                    padLock2RightNeck.draw();
                }

                // If the leather strap on the door hasn't been burned, the display the leather strap
                if (!leatherStrapBurned) {
                    leatherStrap.draw();
                }

                // If the iron rod was placed in the chain and the chain hasn't been snapped,
                // then the rod is displayed behind the chain
                if (rodPlacedInChain && !chainSnapped) {
                    ironRodBody.reinitializeCenter(90, 148);
                    ironRodTop.reinitializeCenter(90, 132);
                    ironRodBody.draw();
                    ironRodTop.draw();
                }

                // If the chain hasn't been snapped, then the chain is displayed on the door
                if (!chainSnapped) {
                    chainLock.draw();
                }

            }

            else if (currentWall == rightWall) {
                glClearColor(rightColor.red, rightColor.green, rightColor.blue, 1.0f);
                bombBody.draw();
                bombFuse.draw();
                bombNeck.draw();

                // Vase is drawn in the area, if the vase has not been broken.
                if (!vaseBroken) {
                    vase.render();
                }

                hammer.render();
            }

            else if (currentWall == backWall) {
                glClearColor(backColor.red, backColor.green, backColor.blue, 1.0f);
                // Candle Draws
                candleBottom.draw();
                candleWick.draw();
                candleLightTop.draw();
                candleLightFlare.draw();

                if (!envelopeOpened) {
                    envelopeBody.draw();
                    envelopeFlapLine.draw();
                    envelopeSeal.draw();
                }

                else if (envelopeOpened && !tumblerSet && !topLeftLockUnlocked) {
                    tumblerBody.draw();
                    tumblerEdgeBottom.draw();
                    tumblerEdgeMiddle.draw();
                }

                if (!safeBroken) {
                    safeBody.draw();
                    safeKeypad.draw();
                    safeKeypadScreen.draw();
                    safeKeypadButton1.draw();
                    safeKeypadButton2.draw();
                    safeKeypadButton3.draw();
                    safeKeypadButton4.draw();
                    safeKeypadButton5.draw();
                    safeKeypadButton6.draw();
                }

                else if (safeBroken) {
                    keyBody.draw();
                    keyHead.draw();
                    keyToothBottom.draw();
                    keyToothMiddle.draw();
                    keyToothTop.draw();
                }
            }

            else if (currentWall == leftWall) {
                glClearColor(leftColor.red, leftColor.green, leftColor.blue, 1.0f);
                // Iron Rod Draws

                tableBody.draw();
                tableLeftLeg.draw();
                tableCubbord.draw();

                candleExtraBody.draw();
                candleExtraWick.draw();

                if (candleLit) {
                    candleExtraLightTop.draw();
                    candleExtraLightFlare.draw();
                }

                if (legCutOff && !chainSnapped) {
                    ironRodBody.draw();
                    ironRodTop.draw();
                }

                else if (!legCutOff) {
                    tableRightLeg.draw();
                }

                if (cubbordSearched) {
                    lockpickBody.draw();
                    lockpickHead.draw();
                    lockpickTooth.draw();
                }
            }

            if (candlePressed) {

                if (candleEquipt) {
                    selectedItem.reinitializeCenter(candleExtraBody.getCenterX(),
                                                    candleExtraBody.getCenterY() - 2);
                    selectedItem.resize(candleExtraBody.getWidth() * 3.4,
                                        candleExtraBody.getHeight() * 2);
                    selectedItem.draw();
                }
                candleExtraBody.reinitializeCenter(20, 440);
                candleExtraWick.reinitializeCenter(20, 426);
                candleExtraLightTop.reinitializeCenter(20, 419);
                candleExtraLightFlare.reinitializeCenter(20, 415);
                candleExtraBody.draw();
                candleExtraWick.draw();

                if (candleLit) {
                    candleExtraLightTop.draw();
                    candleExtraLightFlare.draw();
                }
            }

            if (knifePressed) {
                if (knifeEquipt) {
                    selectedItem.reinitializeCenter(knifeBladeBack.getCenterX() - 1,
                                                    knifeBladeBack.getCenterY() + 4);
                    selectedItem.resize(knifeBladeBack.getWidth() * 3.4,
                                        knifeBladeBack.getHeight() * 2.2);
                    selectedItem.draw();
                }
                knifeHandle.reinitializeCenter(40, 445);
                knifeBladeBack.reinitializeCenter(39, 429);
                knifeBladeEdge.reinitializeCenter(35, 432);
                knifeBladeTopEdge.reinitializeCenter(40, 417);
                knifeUpperFarEdge.reinitializeCenter(33, 436);
                knifeHandle.draw();
                knifeBladeBack.draw();
                knifeBladeEdge.draw();
                knifeBladeTopEdge.draw();
                knifeUpperFarEdge.draw();
            }

            if (lighterPressed) {
                if (lighterEquipt) {
                    selectedItem.reinitializeCenter(lighterBody.getCenterX(),
                                                    lighterBody.getCenterY() - 4);
                    selectedItem.resize(lighterBody.getWidth() * 2.6,
                                        lighterBody.getHeight() * 2.4);
                    selectedItem.draw();
                }
                lighterBody.reinitializeCenter(60, 442);
                lighterTrigger.reinitializeCenter(62, 430);
                lighterTriggerStick.reinitializeCenter(62, 432);
                lighterFlameGuard.reinitializeCenter(56, 430);
                lighterTriggerStick.draw();
                lighterBody.draw();
                lighterTrigger.draw();
                lighterFlameGuard.draw();
            }

            if (rodPressed && !rodPlacedInChain && !chainSnapped) {
                if (rodEquipt) {
                    selectedItem.reinitializeCenter(ironRodBody.getCenterX(),
                                                    ironRodBody.getCenterY());
                    selectedItem.resize(ironRodBody.getWidth() * 3.2,
                                        ironRodBody.getHeight() * 1.4);
                    selectedItem.draw();
                }
                ironRodBody.reinitializeCenter(205, 448);
                ironRodTop.reinitializeCenter(205, 432);
                ironRodBody.draw();
                ironRodTop.draw();
            }

            if (hammerPressed) {
                hammer.setPos(100, 450);
                if (hammerEquipt) {
                    selectedItem.reinitializeCenter(hammer.getXPos(),
                                                    hammer.getYPos() + 20);
                    selectedItem.resize(hammer.getWidth() * 1.6,
                                        hammer.getHeight() * 1.3);
                    selectedItem.draw();
                }
                hammer.render();
            }

            if (bombPressed) {
                if (bombEquipt) {
                    selectedItem.reinitializeCenter(bombBody.getCenterX(),
                                                    bombBody.getCenterY() - 6);
                    selectedItem.resize(bombBody.getWidth() * 1.6,
                                        bombBody.getHeight() * 2.6);
                    selectedItem.draw();
                }
                bombBody.reinitializeCenter(140, 450);
                bombNeck.reinitializeCenter(140, 442);
                bombFuse.reinitializeCenter(140, 437);
                bombBody.draw();
                bombFuse.draw();
                bombNeck.draw();
            }

            if (tumblerPressed && !tumblerSet) {
                if (tumblerEquipt) {
                    selectedItem.reinitializeCenter(tumblerBody.getCenterX() - 1,
                                                    tumblerBody.getCenterY() - 1);
                    selectedItem.resize(tumblerBody.getWidth() * 4.0,
                                        tumblerBody.getHeight() * 1.5);
                    selectedItem.draw();
                }
                tumblerBody.reinitializeCenter(240, 450);
                tumblerEdgeMiddle.reinitializeCenter(237, 438);
                tumblerEdgeBottom.reinitializeCenter(236, 446);
                tumblerBody.draw();
                tumblerEdgeMiddle.draw();
                tumblerEdgeBottom.draw();
            }

            if (lockpickPressed) {
                if (lockpickEquipt) {
                    selectedItem.reinitializeCenter(lockpickBody.getCenterX() - 3,
                                                    lockpickBody.getCenterY());
                    selectedItem.resize(lockpickBody.getWidth() * 5.2,
                                        lockpickBody.getHeight() * 1.5);
                    selectedItem.draw();
                }
                lockpickBody.reinitializeCenter(160, 450);
                lockpickHead.reinitializeCenter(156, 437);
                lockpickTooth.reinitializeCenter(152, 439);
                lockpickBody.draw();
                lockpickHead.draw();
                lockpickTooth.draw();
            }

            if (keyPressed) {
                if (keyEquipt) {
                    selectedItem.reinitializeCenter(keyBody.getCenterX() - 1,
                                                    keyBody.getCenterY() + 1);
                    selectedItem.resize(keyBody.getWidth() * 6.2,
                                        keyBody.getHeight() * 2.2);
                    selectedItem.draw();
                }
                keyHead.reinitializeCenter(180, 450);
                keyBody.reinitializeCenter(180, 442);
                keyToothTop.reinitializeCenter(178, 436);
                keyToothMiddle.reinitializeCenter(178, 439);
                keyToothBottom.reinitializeCenter(180, 450);
                keyHead.draw();
                keyBody.draw();
                keyToothTop.draw();
                keyToothMiddle.draw();
                keyToothBottom.draw();
            }

            if (topLeftLockUnlocked && chainSnapped && leatherStrapBurned && bottomRightLockUnlocked) {
                escaped = true;
                currentScreen = endScreen;
                glClearColor(0.0, 0.0, 0.0, 1.0f);
            }

            // Testing box draws
//            if (!boxPressed) {
                shading.draw(true);
//            }

            glColor3f(1, 1, 1);
            glRasterPos2i(475, 490);
            for (const char &letter: timeRemaining) {
                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
            }

            break;

        case endScreen:
            // Print completion message
            glClearColor(0.0, 0.0, 0.0, 1.0f);
            if (escaped) {
                glColor3f(0, 1, 0);
                glRasterPos2i(135, 260);
                for (const char &letter: "But where to go after this...") {
                    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
                }

                glColor3f(0, 1, 0);
                glRasterPos2i(135, 240);
                for (const char &letter: "You escaped into the woods!!!") {
                    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
                }
            } else if (!endTimerContinue) {
                glColor3f(1, 0, 0);
                glRasterPos2i(135, 250);
                for (const char &letter: "All is lost in darkness...") {
                    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
                }
            }
            break;
    }

    glFlush();  // Render now
}
// http://www.theasciicode.com.ar/ascii-control-characters/escape-ascii-code-27.html
/*
 * A method to capture key presses and update the
 * game depending on what's been pressed.
 * The main functionality here are the presses
 * of the A and D keys to switch between which
 * wall you're currently facing (A moves counterclockwise,
 * D clockwise), as well as the presses of either
 * Q or Escape to simply exit the game.
 */
void kbd(unsigned char key, int x, int y) {
    // escape
    if (key == 27 or key == 'q') {
        glutDestroyWindow(wd);
        exit(0);
    }

    // Left-turning key "a", rotating the user to the wall on their left
    if (key == 97) {
        if (currentWall == frontWall) {
            currentWall = leftWall;
        }
        else if (currentWall == leftWall) {
            currentWall = backWall;
        }
        else if (currentWall == backWall) {
            currentWall = rightWall;
        }
        else if (currentWall == rightWall) {
            currentWall = frontWall;
        }
    }

    // Right-turning key "d", rotating the user to the wall on their right
    if (key == 100) {
        if (currentWall == frontWall) {
            currentWall = rightWall;
        }
        else if (currentWall == rightWall) {
            currentWall = backWall;
        }
        else if (currentWall == backWall) {
            currentWall = leftWall;
        }
        else if (currentWall == leftWall) {
            currentWall = frontWall;
        }
    }

    glutPostRedisplay();
}

// Original Keyboard Implementation
void kbdS(int key, int x, int y) {
    // so that the button doesn't move before the confetti screen

    glutPostRedisplay();
}

void cursor(int x, int y) {
    // If the Interactable is overlapping with the (x, y) coordinate passed in, call the hover method. Otherwise, call the release method.
    if (startButton.isOverlapping(x,y))
        startButton.hover();
    else
        startButton.release();
    glutPostRedisplay();
}

// button will be GLUT_LEFT_BUTTON or GLUT_RIGHT_BUTTON
// state will be GLUT_UP or GLUT_DOWN
/*
 * A method to capture mouse presses and the
 * current coordinates of the mouse to interact
 * with the game.
 * This is a series of checks that make
 * up the main gameplay logic.
 * A number of booleans control which item
 * is currently selected, and another set of
 * booleans to check if an items been clicked on.
 * This lets us control when things can be interacted
 * with. For instance, the iron rod can be retrieved
 * from the right leg of the table only when you
 * have found the knife and have it equipped.
 */
void mouse(int button, int state, int x, int y) {
    // If the left button is down and the cursor is overlapping with the Interactable, call the pressDown method. Otherwise, call the release method.
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && startButton.isOverlapping(x, y)) {
        startButton.pressDown();
        startPressed = true;
    } else {
        startButton.release();
    }

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && (lighterFlameGuard.isOverlapping(x, y) ||
                                                             lighterTriggerStick.isOverlapping(x, y) ||
                                                             lighterTrigger.isOverlapping(x, y) ||
                                                             lighterBody.isOverlapping(x, y))) {
        if (lighterPressed) {
            lighterEquipt = true;
            candleEquipt = false;
            knifeEquipt = false;
            rodEquipt = false;
            hammerEquipt = false;
            bombEquipt = false;
            tumblerEquipt = false;
            lockpickEquipt = false;
            keyEquipt = false;
        }
        if (currentWall == frontWall) {
            lighterPressed = true;
        }
    }

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN &&
        (knifeHandle.isOverlapping(x, y) || knifeBladeEdge.isOverlapping(x, y) ||
         knifeBladeBack.isOverlapping(x, y) || knifeBladeTopEdge.isOverlapping(x, y)
         || knifeUpperFarEdge.isOverlapping(x, y))) {
        if (knifePressed) {
            knifeEquipt = true;
            candleEquipt = false;
            lighterEquipt = false;
            rodEquipt = false;
            hammerEquipt = false;
            bombEquipt = false;
            tumblerEquipt = false;
            lockpickEquipt = false;
            keyEquipt = false;
        }

        if (currentWall == frontWall && paintingBurnt) {
            knifePressed = true;
        }
    }

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN &&
        (candleExtraLightFlare.isOverlapping(x, y) || candleExtraBody.isOverlapping(x, y) ||
         candleExtraWick.isOverlapping(x, y) || candleExtraLightTop.isOverlapping(x, y))) {
        if (candlePressed) {
            candleEquipt = true;
            knifeEquipt = false;
            lighterEquipt = false;
            rodEquipt = false;
            hammerEquipt = false;
            bombEquipt = false;
            tumblerEquipt = false;
            lockpickEquipt = false;
            keyEquipt = false;
        }

        if (currentWall == leftWall) {
            candlePressed = true;
        }
    }

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN &&
        (ironRodBody.isOverlapping(x, y) || ironRodTop.isOverlapping(x, y))) {
        if (rodPressed && !rodPlacedInChain) {
            rodEquipt = true;
            candleEquipt = false;
            knifeEquipt = false;
            lighterEquipt = false;
            hammerEquipt = false;
            bombEquipt = false;
            tumblerEquipt = false;
            lockpickEquipt = false;
            keyEquipt = false;
        }
        if (currentWall == leftWall && legCutOff) {
            rodPressed = true;
        }
    }

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && (bombBody.isOverlapping(x, y) ||
                                                             bombFuse.isOverlapping(x, y) ||
                                                             bombNeck.isOverlapping(x, y))) {
        if (bombPressed) {
            candleEquipt = false;
            knifeEquipt = false;
            lighterEquipt = false;
            rodEquipt = false;
            hammerEquipt = false;
            bombEquipt = true;
            tumblerEquipt = false;
            lockpickEquipt = false;
            keyEquipt = false;
        }
        if (currentWall == rightWall && vaseBroken) {
            bombPressed = true;
        }
    }

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN &&
        (tumblerBody.isOverlapping(x, y) || tumblerEdgeMiddle.isOverlapping(x, y) ||
                tumblerEdgeBottom.isOverlapping(x, y))) {
        if (tumblerPressed) {
            candleEquipt = false;
            knifeEquipt = false;
            lighterEquipt = false;
            rodEquipt = false;
            hammerEquipt = false;
            bombEquipt = false;
            tumblerEquipt = true;
            lockpickEquipt = false;
            keyEquipt = false;
        }
        if (currentWall == backWall && envelopeOpened) {
            tumblerPressed = true;
        }
    }

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && (lockpickBody.isOverlapping(x, y) ||
                                                             lockpickHead.isOverlapping(x, y) ||
                                                             lockpickTooth.isOverlapping(x, y))) {
        if (lockpickPressed) {
            candleEquipt = false;
            knifeEquipt = false;
            lighterEquipt = false;
            rodEquipt = false;
            hammerEquipt = false;
            bombEquipt = false;
            tumblerEquipt = false;
            lockpickEquipt = true;
            keyEquipt = false;
        }
        if (currentWall == leftWall && cubbordSearched) {
            lockpickPressed = true;
        }
    }

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && (keyBody.isOverlapping(x, y) ||
                                                             keyHead.isOverlapping(x, y) ||
                                                             keyToothBottom.isOverlapping(x, y) ||
                                                             keyToothMiddle.isOverlapping(x, y) ||
                                                             keyToothTop.isOverlapping(x, y))) {
        if (keyPressed) {
            candleEquipt = false;
            knifeEquipt = false;
            lighterEquipt = false;
            rodEquipt = false;
            hammerEquipt = false;
            bombEquipt = false;
            tumblerEquipt = false;
            lockpickEquipt = false;
            keyEquipt = true;
        }
        if (currentWall == backWall && safeBroken) {
            keyPressed = true;
        }
    }

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && (envelopeSeal.isOverlapping(x, y) ||
    envelopeFlapLine.isOverlapping(x, y) || envelopeBody.isOverlapping(x, y)) && knifeEquipt) {
        envelopeOpened = true;
    }

    if (button == GLUT_LEFT_BUTTON and state == GLUT_DOWN && hammer.isColliding(x, y)) {
        if (hammerPressed) {
            hammerEquipt = true;
            candleEquipt = false;
            knifeEquipt = false;
            lighterEquipt = false;
            rodEquipt = false;
            bombEquipt = false;
            tumblerEquipt = false;
            lockpickEquipt = false;
        } else if (currentWall == rightWall) {
            hammerPressed = true;
        }
    }

    if (button == GLUT_LEFT_BUTTON and state == GLUT_DOWN && painting.isColliding(x, y) && lighterEquipt) {
        paintingBurnt = true;
        painting.burn();
    }

    if (button == GLUT_LEFT_BUTTON and state == GLUT_DOWN && vase.isColliding(x, y) && hammerEquipt) {
        vase.setPos(600, 600);
        vaseBroken = true;
    }

    if (button == GLUT_LEFT_BUTTON and state == GLUT_DOWN && (safeKeypadScreen.isOverlapping(x, y) ||
    safeKeypad.isOverlapping(x, y) || safeBody.isOverlapping(x, y) || safeKeypadButton1.isOverlapping(x, y) ||
    safeKeypadButton2.isOverlapping(x, y) || safeKeypadButton3.isOverlapping(x, y) ||
    safeKeypadButton4.isOverlapping(x, y) || safeKeypadButton5.isOverlapping(x, y) ||
    safeKeypadButton6.isOverlapping(x, y)) && bombEquipt) {
        safeBroken = true;
    }

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && (tableCubbord.isOverlapping(x, y))) {
        cubbordSearched = true;
    }

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && (tableRightLeg.isOverlapping(x, y)) && knifeEquipt) {
        legCutOff = true;
    }

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && (candleBottom.isOverlapping(x, y) ||
    candleLightFlare.isOverlapping(x, y) || candleLightTop.isOverlapping(x, y) ||
    candleWick.isOverlapping(x, y) || lighterBody.isOverlapping(x, y) ||
    lighterTrigger.isOverlapping(x, y) || lighterTriggerStick.isOverlapping(x, y) ||
    lighterFlameGuard.isOverlapping(x, y)) && candleEquipt) {
        candleLit = true;
    }

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && chainLock.isOverlapping(x, y) && rodEquipt) {
        rodPlacedInChain = true;
    }

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && (chainLock.isOverlapping(x, y) || ironRodTop.isOverlapping(x, y) || ironRodBody.isOverlapping(x, y)) && rodPlacedInChain && hammerEquipt) {
        chainSnapped = true;
    }

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && leatherStrap.isOverlapping(x, y) && candleLit && candleEquipt) {
        leatherStrapBurned = true;
    }

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && (padLock2RightNeck.isOverlapping(x, y) ||
                                                             padLock2LeftNeck.isOverlapping(x, y) || padLock2TopNeck.isOverlapping(x, y) || padLock2TopHole.isOverlapping(x, y)
                                                             || padLock2BottomHole.isOverlapping(x, y) || padLock2Body.isOverlapping(x, y)) && keyEquipt) {
        bottomRightLockUnlocked = true;
    }

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && (padLock1RightNeck.isOverlapping(x, y) ||
    padLock1LeftNeck.isOverlapping(x, y) || padLock1TopNeck.isOverlapping(x, y) || padLock1TopHole.isOverlapping(x, y)
    || padLock1BottomHole.isOverlapping(x, y) || padLock1Body.isOverlapping(x, y)) && tumblerEquipt) {
        tumblerSet = true;
    }

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && (padLock1RightNeck.isOverlapping(x, y) ||
                                                             padLock1LeftNeck.isOverlapping(x, y) || padLock1TopNeck.isOverlapping(x, y) || padLock1TopHole.isOverlapping(x, y)
                                                             || padLock1BottomHole.isOverlapping(x, y) || padLock1Body.isOverlapping(x, y)) && tumblerSet && lockpickEquipt) {
        topLeftLockUnlocked = true;
    }

        glutPostRedisplay();
}

/*
 * Main timer function.
 * Just increments the counter
 * for the time limit
 */
void timerGlobal(int dummy) {
    if (currentScreen == gameScreen) {
        stopTimer++;
    }
    glutTimerFunc(1000, timerGlobal, dummy);
    glutPostRedisplay();
}

// Timer which changes the color of the objects according to the light of the candle
/*
 *  Applies a small amount of variance to the
 *  alpha level to
 */
void timerFlicker(int dummy) {
    if (stopTimer < TIME_LIMIT) {
        glutTimerFunc(1000 + (rand() % 2501), timerFlicker, dummy);
    }

    // Utilized a temporary integer variable, the color values of the object are increased by a factor
    // of a fifth, slightly increasing the light of the object
    if (currentScreen == gameScreen) {
        if (!flickering) {
            shading.setAlpha(shading.getAlpha() / LIGHT_LEVEL_CHANGE);

        }
            // Utilized a temporary integer variable, the color values of the object are decreased by a factor
            // of a fifth, slightly increasing the light of the object
        else if (flickering) {
            shading.setAlpha(shading.getAlpha() * LIGHT_LEVEL_CHANGE);
        }
        flickering = !flickering;
    }

    glutPostRedisplay();
}

// Timer which changes the color of the objects according to the end game timer
void timerLightAndEnd(int dummy) {
    if (currentScreen == gameScreen) {
        if (stopTimer < 20) {
            lightLevel = 1.0;
        }
        else if (stopTimer < 40) {
            lightLevel = 0.8;

            shading.setColor(0.0f, 0.0f, 0.0f, shading.getAlphaInitial()
                                               * 1 - (flickering ? LIGHT_LEVEL_CHANGE : lightLevel));
        }

        else if (stopTimer < 60) {
            lightLevel = 0.6;

            shading.setColor(0.0f, 0.0f, 0.0f, shading.getAlphaInitial()
                                               * 1 - (flickering ? LIGHT_LEVEL_CHANGE : lightLevel));
        }

        else if (stopTimer < 80) {
            lightLevel = 0.4;

            shading.setColor(0.0f, 0.0f, 0.0f, shading.getAlphaInitial()
                                               * 1 - (flickering ? LIGHT_LEVEL_CHANGE : lightLevel));
        }

        else if (stopTimer < TIME_LIMIT) {
            lightLevel = 0.2;

            shading.setColor(0.0f, 0.0f, 0.0f, shading.getAlphaInitial()
                                               * 1 - (flickering ? LIGHT_LEVEL_CHANGE : lightLevel));
        }

        else if (stopTimer == TIME_LIMIT) {
            lightLevel = 0.0;
            shading.setColor(shading.getRedInitial() * lightLevel,
                             shading.getGreenInitial() * lightLevel,
                             shading.getBlueInitial() * lightLevel);
            currentScreen = endScreen;
        }
    }

    if (currentScreen == endScreen) {
        stopTimerEnd++;
        endTimerContinue = true;
        if (stopTimerEnd > 5) {
            endTimerContinue = false;
        }
    }
    glutTimerFunc(1000, timerLightAndEnd, dummy);
    glutPostRedisplay();
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
    init();

    glutInit(&argc, argv);          // Initialize GLUT

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);

    glutInitWindowSize((int) width, (int) height);
    glutInitWindowPosition(100, 200); // Position the window's initial top-left corner
    /* create the window and store the handle to it */
    wd = glutCreateWindow("A Locked Cabin" /* title */ );

    // Using transparency
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Register callback handler for window re-paint event
    glutDisplayFunc(display);

    // Our own OpenGL initialization
    initGL();

    // register keyboard press event processing function
    // works for numbers, letters, spacebar, etc.
    glutKeyboardFunc(kbd);

    // register special event: function keys, arrows, etc.
    glutSpecialFunc(kbdS);

    // handles mouse movement
    glutPassiveMotionFunc(cursor);

    // handles mouse click
    glutMouseFunc(mouse);

    // handles timer
    timerGlobal(0);
    timerFlicker(0);
    timerLightAndEnd(0);

    // Enter the event-processing loop
    glutMainLoop();
    return 0;
}