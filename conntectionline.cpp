#include "conntectionline.h"


void ConnectionLine::draw(QPaintDevice *device)
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

void ConnectionLine::linkToShape(int firstID, int secondID)
{
    if(firstID!=NULL)
    {
        m_firstIDShape = firstID;
    }
    else if(secondID!=NULL)
    {
        m_secondIDShape = secondID;
    }
}
