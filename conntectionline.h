#ifndef CONNTECTIONLINE_H
#define CONNTECTIONLINE_H

#include "shape.h"

class ConnectionLine : public Shape
{
public:
    ConnectionLine(const QRect& rect) : Shape(rect){}

    void draw(QPaintDevice* device) override;

    void linkToShape(int firstIDLink, int secondIDLink);

public:
    int m_firstIDShape{};
    int m_secondIDShape{};

};

#endif // CONNTECTIONLINE_H
