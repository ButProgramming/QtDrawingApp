#ifndef CONNTECTIONLINE_H
#define CONNTECTIONLINE_H

#include "shape.h"
#include "areashape.h"

class ConnectionLine : public Shape
{
public:
    ConnectionLine(const QRect& rect) : Shape(rect){}

    void draw(QPaintDevice* device) override;

    void linkToShape(int firstIDLink, int secondIDLink);
    void updateConnection(const vector<Shape*>& shapes);

public:
    int m_firstIDShape{};
    int m_secondIDShape{};

};

#endif // CONNTECTIONLINE_H
