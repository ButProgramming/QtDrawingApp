#ifndef CONNTECTIONLINE_H
#define CONNTECTIONLINE_H

#include "abstract/ishape.h"
#include "abstract/areashape.h"

class ConnectionLine : public IShape
{
public:
    ConnectionLine(const QPoint& point) {m_points.first = point;}

    void draw(QPaintDevice* device) override;
    void safe(QDataStream &out) override;
    void load(QDataStream& in) override;
    void updateCreate(const QPoint& lastPoint) override;

    void linkToShape(int firstIDLink, int secondIDLink);
    void updateConnection(const std::vector<IShape*>& shapes);

private:
    int m_firstIDShape{};
    int m_secondIDShape{};
    std::pair<QPoint, QPoint> m_points;
};

#endif // CONNTECTIONLINE_H
