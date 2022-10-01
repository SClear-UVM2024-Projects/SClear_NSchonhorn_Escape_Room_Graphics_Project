#ifndef CONFETTIFY_QUAD_H
#define CONFETTIFY_QUAD_H

struct color {
    double red;
    double green;
    double blue;
};

struct point {
    int x;
    int y;
};

class Quad {
protected:
    color fill;
    color initialFill;
    point center;
    unsigned int width;
    unsigned int height;
    double alpha;

public:
    Quad();
    Quad(color fill, point center, unsigned int width, unsigned int height);

    int getCenterX() const;
    int getLeftX() const;
    int getRightX() const;
    int getCenterY() const;
    int getTopY() const;
    int getBottomY() const;
    point getCenter() const;

    // Temporary Color Accessor Methods
    double getRed() const;
    double getGreen() const;
    double getBlue() const;
    double getAlpha() const;

    // Initial Color Accessor Methods
    double getRedInitial() const;
    double getGreenInitial() const;
    double getBlueInitial() const;
    double getAlphaInitial() const;

    color getFill() const;

    unsigned int getWidth() const;
    unsigned int getHeight() const;

    void setColor(double red, double green, double blue);
    void setColor(double red, double green, double blue, double alpha);
    void setColor(color fill);
    void move(int deltaX, int deltaY);
    void setPos(int newX, int newY);
    void resize(unsigned int width, unsigned int height);

    virtual void draw(bool useAlpha = false) const;
    void setAlpha(float alpha);
};

#endif //CONFETTIFY_QUAD_H
