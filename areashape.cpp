#include "areashape.h"

int AreaShape::ID = 1;

void AreaShape::drawSelection(QPainter &painter)
{
    painter.setPen(Qt::DotLine);
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(m_rect);
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
    unsigned short int type{};

    in >> m_rect;
    in >> m_selected;
    in >> m_shouldDrawCenter;
    in >> m_ID;

}

void AreaShape::updateCreate(const QPoint& lastPoint)
{
    m_rect.setBottomRight(lastPoint);
}
