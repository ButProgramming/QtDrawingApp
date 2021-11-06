#include "ellipse.h"


void Ellipse::draw(QPaintDevice *device)
{

    QPainter painter(device);
    painter.setBrush(Qt::white);
    painter.drawEllipse(m_rect);
    if(isSelected)
        drawSelection(painter);

}

bool Ellipse::contains(const QPoint &point)
{
    QGraphicsEllipseItem ellipse(m_rect);
    if(ellipse.contains(point))
        return true;

    return false;
}
