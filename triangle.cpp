#include "triangle.h"


void Triangle::draw(QPaintDevice *device)
{
    QPainter painter(device);

    QPainterPath path;
    path.moveTo(m_rect.left() + (m_rect.width() / 2), m_rect.top());
    path.lineTo(m_rect.bottomLeft());
    path.lineTo(m_rect.bottomRight());
    path.lineTo(m_rect.left() + (m_rect.width() / 2), m_rect.top());


    QPen pen(Qt::black);
    pen.setWidth(2);
    painter.setPen(pen);
    painter.drawPath(path);
    painter.fillPath(path, QBrush(QColor ("white")));
    if(isSelected)
        drawSelection(painter);
}

bool Triangle::contains(const QPoint &point)
{
    QPainterPath path;
    path.moveTo(m_rect.left() + (m_rect.width() / 2), m_rect.top());
    path.lineTo(m_rect.bottomLeft());
    path.lineTo(m_rect.bottomRight());
    path.lineTo(m_rect.left() + (m_rect.width() / 2), m_rect.top());
    if(path.contains(point))
        return true;

    return false;
}
