#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "areashape.h"

class Rectangle : public AreaShape
{
public:
    Rectangle(const QRect& rect) : AreaShape(rect) {}
    void draw(QPaintDevice *device) override;

    bool contains(const QPoint& point) override;
};

#endif // RECTANGLE_H
