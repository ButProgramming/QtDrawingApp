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
    void updateConnection(const std::vector<Shape*>& shapes);
    void safe(QDataStream &out) override;
    void load(QDataStream& in) override;

public:
    int m_firstIDShape{};
    int m_secondIDShape{};

};

#endif // CONNTECTIONLINE_H
