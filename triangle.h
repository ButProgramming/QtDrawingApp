#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "areashape.h"

class Triangle : public AreaShape
{
public:
    Triangle(const QRect& rect) : AreaShape(rect) {}

    void draw(QPaintDevice* device) override;

    bool contains(const QPoint& point) override;


};

#endif // TRIANGLE_H
