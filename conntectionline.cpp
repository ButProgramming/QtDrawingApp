#include "conntectionline.h"


void ConnectionLine::draw(QPaintDevice *device)
{
    QPainter* painter = new QPainter(device);
    QPainterPath* path = new QPainterPath();
    path->moveTo(m_points.first);
    path->lineTo(m_points.second);

    QPen* pen = new QPen(Qt::black);
    pen->setWidth(consts::sizeOfPenForLine);
    painter->setPen(*pen);
    painter->drawPath(*path);

    delete pen;
    delete path;
    delete painter;
}

void ConnectionLine::linkToShape(int firstID, int secondID)
{
    if(firstID!=NULL)
        m_firstIDShape = firstID;
    else if(secondID!=NULL)
        m_secondIDShape = secondID;
}

void ConnectionLine::updateConnection(const std::vector<Shape *> &shapes)
{

    if(!m_firstIDShape || !m_secondIDShape)
        return;

    for(const auto& shape:shapes)
    {
        if(dynamic_cast<AreaShape*>(shape)!=nullptr)
        {
            if(dynamic_cast<AreaShape*>(shape)->getID() == m_firstIDShape)
            {
                m_points.first = dynamic_cast<AreaShape*>(shape)->getCenter();
            }
            if(dynamic_cast<AreaShape*>(shape)->getID() == m_secondIDShape)
            {
                m_points.second = dynamic_cast<AreaShape*>(shape)->getCenter();
            }
        }
    }
}

void ConnectionLine::safe(QDataStream &out)
{
    out << m_points.first;
    out << m_points.second;
    out << m_firstIDShape;
    out << m_secondIDShape;
}

void ConnectionLine::load(QDataStream &in)
{
    in >> m_points.first;
    in >> m_points.second;
    in >> m_firstIDShape;
    in >> m_secondIDShape;
}

void ConnectionLine::updateCreate(const QPoint& lastPoint)
{
    m_points.second = lastPoint;
}
