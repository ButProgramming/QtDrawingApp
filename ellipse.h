#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "areashape.h"

class Ellipse : public AreaShape
{
public:
    Ellipse(const QPoint& point) : AreaShape(point) {}

    void draw(QPaintDevice* device) override;
    bool contains(const QPoint& point) override;
};

#endif // ELLIPSE_H
