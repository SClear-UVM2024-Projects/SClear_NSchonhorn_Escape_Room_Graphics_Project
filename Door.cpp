//
// Created by Noah Schonhorn on 4/17/22.
//

#include "Door.hpp"

Door::Door(int xPos, int yPos) : GameObject(xPos, yPos)
{
    mXPos = xPos;
    mYPos = yPos;

    mDoor = Quad({.588f, .294f, 0.0f},
                 {xPos, yPos},
                 80,
                 180);
    mKnob = Quad({1.0f, 1.0f, .0f},
                 {xPos + 30, yPos + 20},
                 10,
                 10);
}

void Door::render()
{
    mDoor.draw();
    mKnob.draw();
}

void Door::move(int deltaX, int deltaY)
{
    mXPos += deltaX;
    mYPos += deltaY;
    mDoor.move(deltaX, deltaY);
    mKnob.move(deltaX, deltaY);
}

void Door::setPos(int newX, int newY)
{
    mXPos = newX;
    mYPos = newY;
    mDoor.setPos(newX, newY);
    mKnob.setPos(newX + 15, newY + 100);
}

bool Door::isColliding(int x, int y)
{
    return quadOverlap(mDoor, x, y);
}

unsigned Door::getWidth()
{
    return mDoor.getWidth();
}

unsigned Door::getHeight()
{
    return mDoor.getHeight();
}
