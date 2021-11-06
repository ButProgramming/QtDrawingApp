#ifndef CONNTECTIONLINE_H
#define CONNTECTIONLINE_H

#include "shape.h"

class ConnectionLine : public Shape
{
public:
    ConnectionLine(const QRect& rect) : Shape(rect){}

    void draw(QPaintDevice* device) override;

    void link(int firstIDLink, int secondIDLink);

private:
    int m_firstIDLink{};
    int m_secondIDLink{};

};

#endif // CONNTECTIONLINE_H
