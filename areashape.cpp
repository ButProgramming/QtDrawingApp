#include "areashape.h"

int AreaShape::ID = 1;

void AreaShape::drawSelection(QPainter &painter)
{
    painter.setPen(Qt::DotLine);
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(m_rect);
}

void AreaShape::safe(QDataStream &out, unsigned short int type)
{
    out << m_rect;
    out << m_x;
    out << m_y;
    out << m_length;
    out << m_width;
    out << m_selected;
    out << m_shouldDrawCenter;
    out << m_ID;
    out << type;
}

unsigned short int AreaShape::load(QDataStream &in)
{
    in >> m_rect;
    in >> m_x;
    in >> m_y;
    in >> m_length;
    in >> m_width;
    in >> m_selected;
    in >> m_shouldDrawCenter;
    in >> m_ID;
    unsigned short int type{};
    in >> type;
    return type;
}
