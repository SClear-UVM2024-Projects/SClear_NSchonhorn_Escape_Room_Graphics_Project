#include "Interactable.h"
#include "graphics.h"
using namespace std;

Interactable::Interactable(color fill, point center, unsigned int width, unsigned int height, std::string label) : Quad(fill, center, width, height) {
    this->label = label;
    originalFill = fill;
    hoverFill = {fill.red + 0.5, fill.green + 0.5, fill.blue + 0.5};
    pressFill = {fill.red - 0.5, fill.green - 0.5, fill.blue - 0.5};
}

void Interactable::draw(bool useAlpha) const {
    Quad::draw(useAlpha);
    glColor3f(0, 0, 0);
    glRasterPos2i(center.x - (4 * label.length()), center.y + 7);
    for (const char &letter : label) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
    }
}

void Interactable::reinitializeCenter(int x, int y) {
    center.x = x;
    center.y = y;
}

/* Returns true if the coordinate is inside the box */
bool Interactable::isOverlapping(int x, int y) const {
    // set booleans to determine both x and y
    bool withinX = false;
    bool withinY = false;

    // determine each side

    // determine if coordinate is between left and right sides
    if(x >= this->getLeftX() && x <= this->getRightX()) {
        withinX = true;
    }
    // determine if coordinate is between top and bottom sides
    if(y >= this->getTopY() && y <= this->getBottomY()) {
        withinY = true;
    }

    // combine and make final determination

    // if it is within the top, bottom, left, and right sides, it's overlapping
    if(withinX && withinY){
        return true;
    }
    // otherwise, it's not overlapping
    return false;
}

/* Change color of the box when the user is hovering over it */
void Interactable::hover() {
    setColor(hoverFill);
}

/* Change color of the box when the user is clicking on it */
void Interactable::pressDown() {
    setColor(pressFill);
}

/* Change the color back when the user is not clicking/hovering */
void Interactable::release() {
    setColor(originalFill);
}
