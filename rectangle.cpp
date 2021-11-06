#include "rectangle.h"

void Rectangle::draw(QPaintDevice *device)
{
    QPainter painter(device);

    if(m_selected)
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

void Rectangle::drawSelection(QPainter &painter)
{
    painter.setPen(Qt::DotLine);
    painter.setBrush(Qt::white);
    painter.drawRect(m_rect);
}
