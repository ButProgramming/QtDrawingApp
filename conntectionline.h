#ifndef CONNTECTIONLINE_H
#define CONNTECTIONLINE_H

#include "shape.h"
#include "areashape.h"

class ConnectionLine : public Shape
{
public:
    //ConnectionLine(const QRect& rect) : Shape(rect){}
    ConnectionLine(const QPoint& point) {m_points.first = point;}

    void draw(QPaintDevice* device) override;

    void linkToShape(int firstIDLink, int secondIDLink);
    void updateConnection(const std::vector<Shape*>& shapes);
    void safe(QDataStream &out) override;
    void load(QDataStream& in) override;
    void updateCreate(int lastX, int lastY) override;

private:
    int m_firstIDShape{};
    int m_secondIDShape{};
    //std::array<QPoint, 2> m_points;
    std::pair<QPoint, QPoint> m_points;
};

#endif // CONNTECTIONLINE_H
