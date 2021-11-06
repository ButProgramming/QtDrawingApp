#ifndef CONNTECTIONLINE_H
#define CONNTECTIONLINE_H

#include "ishape.h"

class ConnectionLine : public IShape
{
public:
    ConnectionLine(const QRect& rect) : IShape(rect){}

    void draw(QPaintDevice* device) override
    {
        QPainter painter(device);
        QPainterPath path;

        path.moveTo(m_rect.left(), m_rect.top());
        path.lineTo(m_rect.bottomRight());

        QPen pen(Qt::black);
        pen.setWidth(2);
        painter.setPen(pen);
        painter.drawPath(path);
    }
};

#endif // CONNTECTIONLINE_H
