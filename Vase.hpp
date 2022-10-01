//
// Created by Noah Schonhorn on 4/17/22.
//

#ifndef M4OEP_LARGE_SCLEAR_NSCHONHORN_VASE_HPP
#define M4OEP_LARGE_SCLEAR_NSCHONHORN_VASE_HPP

#include "GameObject.hpp"

class Vase : public GameObject
{
private:
    Quad mMain;
    Quad mNeck;
    Quad mLip;

public:
    Vase(int xPos, int yPos);
    void render() override;
    void move(int deltaX, int deltaY) override;
    void setPos(int newX, int newY) override;
    bool isColliding(int x, int y) override;
    unsigned getWidth() override;
    unsigned getHeight() override;
};


#endif //M4OEP_LARGE_SCLEAR_NSCHONHORN_VASE_HPP
