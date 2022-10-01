//
// Created by Noah Schonhorn on 4/14/22.
//

#include "Painting.hpp"

Painting::Painting(int xPos, int yPos) : GameObject(xPos, yPos)
{
    mXPos = xPos;
    mYPos = yPos;

    isBurned = false;

    mFrame = Quad({.588f, .294f, 0.0f},
                  {xPos, yPos},
                  60,
                  60);
    mImage = Quad({.156f, .545f, .659f},
                  {xPos, yPos},
                  50,
                  50);
    mAsh = Quad({.573f, .573f, .573f},
                  {xPos, yPos},
                  50,
                  50);
    mBurn = Quad({.0f, .0f, .0f},
                  {xPos, yPos},
                  45,
                  45);
}

void Painting::render()
{
    mFrame.draw();
    mImage.draw();

    if (isBurned)
    {
        mAsh.draw();
        mBurn.draw();
    }
}

void Painting::move(int deltaX, int deltaY)
{
    mXPos += deltaX;
    mYPos += deltaY;

    mFrame.move(deltaX, deltaY);
    mImage.move(deltaX, deltaY);
    mAsh.move(deltaX, deltaY);
    mBurn.move(deltaX, deltaY);
}

bool Painting::isColliding(int x, int y)
{
    return quadOverlap(mFrame, x, y);
}

void Painting::setPos(int newX, int newY)
{
    mXPos = newX;
    mYPos = newY;

    mFrame.setPos(newX, newY);
    mImage.setPos(newX, newY);
    mAsh.setPos(newX, newY);
    mBurn.setPos(newX, newY);
}

void Painting::burn()
{
    isBurned = true;
}

unsigned Painting::getWidth()
{
    return mFrame.getWidth();
}

unsigned Painting::getHeight()
{
    return mFrame.getHeight();
}
