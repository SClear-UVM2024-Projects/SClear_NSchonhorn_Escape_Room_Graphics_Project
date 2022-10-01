//
// Created by Noah Schonhorn on 4/17/22.
//

#include "Vase.hpp"

Vase::Vase(int xPos, int yPos) : GameObject(xPos, yPos)
{
    mXPos = xPos;
    mYPos = yPos;

    mMain = Quad({0.0f, .588f, 1.0f},
                 {xPos, yPos},
                 25,
                 40);
    mNeck = Quad({0.0f, .588f, 1.0f},
                 {xPos, yPos - 20},
                 10,
                 6);
    mLip = Quad({0.0f, .588f, 1.0f},
                 {xPos, yPos - 26},
                 18,
                 6);
}

void Vase::render()
{
    mMain.draw();
    mNeck.draw();
    mLip.draw();
}

void Vase::move(int deltaX, int deltaY)
{
    mXPos += deltaX;
    mYPos += deltaY;

    mMain.move(deltaX, deltaY);
    mNeck.move(deltaX, deltaY);
    mLip.move(deltaX, deltaY);
}

void Vase::setPos(int newX, int newY)
{
    mXPos = newX;
    mYPos = newY;

    mMain.setPos(newX, newY);
    mNeck.setPos(newX, newY - 20);
    mLip.setPos(newX, newY - 26);
}

bool Vase::isColliding(int x, int y)
{
    return quadOverlap(mMain, x, y) or quadOverlap(mNeck, x, y) or quadOverlap(mLip, x, y);
}

unsigned Vase::getWidth()
{
   return mMain.getWidth();
}

unsigned Vase::getHeight()
{
    return mMain.getHeight()
            + mNeck.getHeight()
            + mLip.getHeight();
}
