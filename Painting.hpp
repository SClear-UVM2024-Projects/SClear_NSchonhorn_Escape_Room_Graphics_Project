#ifndef M4OEP_LARGE_SCLEAR_NSCHONHORN_PAINTING_HPP
#define M4OEP_LARGE_SCLEAR_NSCHONHORN_PAINTING_HPP

#include "GameObject.hpp"

class Painting : public GameObject
{
private:
    Quad mFrame;
    Quad mImage;
    Quad mAsh;
    Quad mBurn;

    bool isBurned;

public:
    Painting(int xPos, int yPos);
    void render() override;
    void move(int deltaX, int deltaY) override;
    void setPos(int newX, int newY) override;
    bool isColliding(int x, int y) override;
    unsigned getWidth() override;
    unsigned getHeight() override;
    void burn();
};


#endif //M4OEP_LARGE_SCLEAR_NSCHONHORN_PAINTING_HPP
