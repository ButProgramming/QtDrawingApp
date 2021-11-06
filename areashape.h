#ifndef AREASHAPE_H
#define AREASHAPE_H

#include "ishape.h"


class AreaShape : public IShape
{
public:
    AreaShape(const QRect& rect) : IShape(rect) {}

    virtual bool contains(const QPoint& point) = 0;

    void drawSelection(QPainter& painter);
    void setSelected() { isSelected = true;}
    void setNotSelected() { isSelected = false;}

};

#endif // AREASHAPE_H
