#include "areashape.h"

int AreaShape::ID = 1;


void AreaShape::drawSelection(QPainter* painter)
{
    painter->setPen(Qt::DotLine);
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(m_rect);
}

void AreaShape::safe(QDataStream &out)
{
    out << m_rect;
    out << m_selected;
    out << m_shouldDrawCenter;
    out << m_ID;
}

void AreaShape::load(QDataStream &in)
{
    in >> m_rect;
    in >> m_selected;
    in >> m_shouldDrawCenter;
    in >> m_ID;
}

void AreaShape::update(const QPoint &differense)
{
    m_rect.setBottomLeft(QPoint(m_rect.bottomLeft() - differense));
    m_rect.setTopRight(QPoint(m_rect.topRight() - differense));
}

bool AreaShape::containsCenter(const QPoint &point)
{
    std::unique_ptr<QRect> rect(new QRect(
                m_rect.center().x() - consts::sizeOfCenterEllipse,
                m_rect.center().y() - consts::sizeOfCenterEllipse,
                consts::sizeOfCenterEllipse*2,
                consts::sizeOfCenterEllipse*2
                ));
    std::unique_ptr<QGraphicsEllipseItem> centerEllipse(new QGraphicsEllipseItem(*rect));

    if(centerEllipse->contains(point))
        return true;

    return false;
}

void AreaShape::updateCreate(const QPoint& lastPoint)
{
    m_rect.setBottomRight(lastPoint);
}

void AreaShape::drawEllipseCenter(QPainter *painter)
{
    painter->drawEllipse(m_rect.center(), consts::sizeOfCenterEllipse, consts::sizeOfCenterEllipse);
}
