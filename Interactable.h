#ifndef GRAPHICS_STARTER_BUTTON_H
#define GRAPHICS_STARTER_BUTTON_H

#include "Quad.h"
#include <string>

class Interactable : public Quad {
private:
    std::string label;
    color originalFill, hoverFill, pressFill;

public:
    Interactable(color fill, point center, unsigned int width, unsigned int height, std::string label);
    /* Uses OpenGL to draw the box with the label on top */
    virtual void draw(bool useAlpha = false) const override;

    void reinitializeCenter(int x, int y);

    /* Returns true if the coordinate is inside the box */
    bool isOverlapping(int x, int y) const;

    /* Change color of the Interactable when the user is hovering over it */
    void hover();

    /* Change color of the Interactable when the user is clicking on it */
    void pressDown();

    /* Change the color back when the user is not clicking/hovering */
    void release();


    };


#endif //GRAPHICS_STARTER_BUTTON_H
