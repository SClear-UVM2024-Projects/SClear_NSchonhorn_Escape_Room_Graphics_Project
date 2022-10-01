//
// Created by Noah Schonhorn on 4/15/22.
//

#include "Hammer.hpp"

Hammer::Hammer(int xPos, int yPos) : GameObject(xPos, yPos)
{
    mXPos = xPos;
    mYPos = yPos;

    mHead = Quad({.502f, .502f, .502f},
                   {xPos, yPos},
                   30,
                   12);
    mHandle = Quad({.588f, .294f, 0.0f},
                  {xPos, yPos + 26},
                  8,
                  40);
}

void Hammer::render()
{
    mHead.draw();
    mHandle.draw();
}

void Hammer::move(int deltaX, int deltaY)
{
    mXPos += deltaX;
    mYPos += deltaY;
    mHead.move(deltaX, deltaY);
    mHandle.move(deltaX, deltaY);
}

bool Hammer::isColliding(int x, int y)
{
    // Creates a quad with a handle wider than usual, to make clicking easier
    Quad tempHandle = mHandle;
    tempHandle.resize(tempHandle.getWidth() * 3,
                      tempHandle.getHeight());
    return quadOverlap(mHead, x, y) or quadOverlap(tempHandle, x, y);
}

void Hammer::setPos(int newX, int newY)
{
    mXPos = newX;
    mYPos = newY;
    mHead.setPos(newX, newY);
    mHandle.setPos(newX, newY + 26);
}

unsigned Hammer::getWidth()
{
    return mHead.getWidth();
}

unsigned Hammer::getHeight()
{
    return mHead.getHeight()
            + mHandle.getHeight();
}
