#include "rectangle.h"

void Rectangle::draw(QPaintDevice *device)
{
    QPainter painter(device);

    if(isSelected)
    {
        drawSelection(painter);
        return;
    }

    painter.setBrush(Qt::white);
    painter.drawRect(m_rect);
}

bool Rectangle::contains(const QPoint &point)
{
    if(m_rect.contains(point))
        return true;

    return false;
}
