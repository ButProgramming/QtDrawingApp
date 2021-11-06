#include "ellipse.h"


void Ellipse::draw(QPaintDevice *device)
{

    QPainter painter(device);
    painter.setBrush(Qt::white);
    painter.drawEllipse(m_rect);
    if(m_selected)
        drawSelection(painter);
    if(m_shouldDrawCenter)
        painter.drawEllipse(m_rect.center(), consts::sizeOfCenterEllipse, consts::sizeOfCenterEllipse);
    qDebug() << m_rect.center() << "from ellipse draw()";

}

bool Ellipse::contains(const QPoint &point)
{
    QGraphicsEllipseItem ellipse(m_rect);
    if(ellipse.contains(point))
        return true;

    return false;
}
