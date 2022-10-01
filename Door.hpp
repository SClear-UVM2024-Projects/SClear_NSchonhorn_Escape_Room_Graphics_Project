//
// Created by Noah Schonhorn on 4/17/22.
//

#ifndef M4OEP_LARGE_SCLEAR_NSCHONHORN_DOOR_HPP
#define M4OEP_LARGE_SCLEAR_NSCHONHORN_DOOR_HPP

#include "GameObject.hpp"

class Door : public GameObject
{
private:
    Quad mDoor;
    Quad mKnob;

public:
    Door(int xPos, int yPos);
    void render() override;
    void move(int deltaX, int deltaY) override;
    void setPos(int newX, int newY) override;
    bool isColliding(int x, int y) override;
    unsigned getWidth() override;
    unsigned getHeight() override;

};


#endif //M4OEP_LARGE_SCLEAR_NSCHONHORN_DOOR_HPP
