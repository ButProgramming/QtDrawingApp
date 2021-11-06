#include "areashape.h"


void AreaShape::drawSelection(QPainter &painter)
{
    painter.setPen(Qt::DotLine);
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(m_rect);
}
