#ifndef M4OEP_LARGE_SCLEAR_NSCHONHORN_HAMMER_HPP
#define M4OEP_LARGE_SCLEAR_NSCHONHORN_HAMMER_HPP

#include "GameObject.hpp"

class Hammer : public GameObject
{
private:
    Quad mHead;
    Quad mHandle;

public:
    Hammer(int xPos, int yPos);
    void render() override;
    void move(int deltaX, int deltaY) override;
    void setPos(int newX, int newY) override;
    bool isColliding(int x, int y) override;
    unsigned getWidth() override;
    unsigned getHeight() override;

};


#endif //M4OEP_LARGE_SCLEAR_NSCHONHORN_HAMMER_HPP
