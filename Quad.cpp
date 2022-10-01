#include "Quad.h"
#include "graphics.h"

Quad::Quad() {
    fill = {0, 0, 0};
    initialFill = {fill.red, fill.green, fill.blue};
    center = {0, 0};
    width = 50;
    height = 50;
    alpha = 1.0f;
}

Quad::Quad(color fill, point center, unsigned int width, unsigned int height) {
    this->fill = fill;
    initialFill = {fill.red, fill.green, fill.blue};
    this->center = center;
    this->width = width;
    this->height = height;
    this->alpha = 1.0f;
}

int Quad::getCenterX() const {
    return center.x;
}

int Quad::getLeftX() const {
    return center.x - (width / 2);
}

int Quad::getRightX() const {
    return center.x + (width / 2);
}

int Quad::getCenterY() const {
    return center.y;
}

int Quad::getTopY() const {
    return center.y - (height / 2);
}

int Quad::getBottomY() const {
    return center.y + (height / 2);
}

point Quad::getCenter() const {
    return center;
}

double Quad::getRed() const {
    return fill.red;
}

double Quad::getGreen() const {
    return fill.green;
}

double Quad::getBlue() const {
    return fill.blue;
}

double Quad::getRedInitial() const {
    return initialFill.red;
}

double Quad::getGreenInitial() const {
    return initialFill.green;
}

double Quad::getBlueInitial() const {
    return initialFill.blue;
}

color Quad::getFill() const {
    return fill;
}

unsigned int Quad::getWidth() const {
    return width;
}

unsigned int Quad::getHeight() const {
    return height;
}

void Quad::setColor(double red, double green, double blue) {
    fill = {red, green, blue};
}

void Quad::setColor(color fill) {
    this->fill = fill;
}

void Quad::move(int deltaX, int deltaY) {
    center.x += deltaX;
    center.y += deltaY;
}

void Quad::resize(unsigned int width, unsigned int height) {
    this->width = width;
    this->height = height;
}

void Quad::draw(bool useAlpha) const {
    // Don't forget to set the color to the fill field
    useAlpha
            ? glColor4f(fill.red, fill.green, fill.blue, alpha)
            : glColor3f(fill.red, fill.green, fill.blue);
    glBegin(GL_QUADS);
    glVertex2i(getLeftX(), getTopY());
    glVertex2i(getRightX(), getTopY());
    glVertex2i(getRightX(), getBottomY());
    glVertex2i(getLeftX(), getBottomY());
    glEnd();
}

void Quad::setPos(int newX, int newY)
{
    center.x = newX;
    center.y = newY;
}

double Quad::getAlpha() const
{
    return alpha;
}

double Quad::getAlphaInitial() const
{
    // FIXME: Cheating a bit here, this should get changed
    return 1.0f;
}

void Quad::setColor(double red, double green, double blue, double alpha)
{
    this->fill = {red, green, blue};
    this->alpha = alpha;
}

void Quad::setAlpha(float alpha)
{
    if (alpha > 1.0f)
    {
        alpha = 1.0f;
    }
    else if (alpha < 0.0f)
    {
        alpha = 0.0f;
    }

    this->alpha = alpha;
}
