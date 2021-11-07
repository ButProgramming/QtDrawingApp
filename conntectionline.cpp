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

void ConnectionLine::updateConnection(const std::vector<Shape *> &shapes)
{

    if(!m_firstIDShape || !m_secondIDShape)
        return;

    qDebug() << "here2";

    for(auto shape:shapes)
    {
        if(dynamic_cast<AreaShape*>(shape)!=nullptr)
        {
            if(dynamic_cast<AreaShape*>(shape)->getID() == m_firstIDShape)
            {

                m_rect.setBottomRight(shape->getCenter());
            }
            if(dynamic_cast<AreaShape*>(shape)->getID() == m_secondIDShape)
            {
                m_rect.setTopLeft(shape->getCenter());
            }
        }
    }
}
