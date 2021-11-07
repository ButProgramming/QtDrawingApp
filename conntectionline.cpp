#include "conntectionline.h"


void ConnectionLine::draw(QPaintDevice *device)
{
    QPainter painter(device);
    QPainterPath path;

    //path.moveTo(m_rect.left(), m_rect.top());
    //path.lineTo(m_rect.bottomRight());
    path.moveTo(m_points.at(consts::firstPoint));
    path.lineTo(m_points.at(consts::secondPoint));

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

                m_points.at(consts::firstPoint) = dynamic_cast<AreaShape*>(shape)->getCenter();
            }
            if(dynamic_cast<AreaShape*>(shape)->getID() == m_secondIDShape)
            {
                m_points.at(consts::secondPoint) = dynamic_cast<AreaShape*>(shape)->getCenter();
            }
        }
    }
}

void ConnectionLine::safe(QDataStream &out)
{
    out<<m_rect;
    out << m_firstIDShape;
    out << m_secondIDShape;
}

void ConnectionLine::load(QDataStream &in)
{
    in >> m_rect;
    in >> m_firstIDShape;
    in >> m_secondIDShape;
}

void ConnectionLine::updateCreate(int lastX, int lastY)
{

    m_points.at(consts::secondPoint) = QPoint(lastX, lastY);
    //m_rect.setBottomRight(QPoint(lastX, lastY));

}
