#include "ellipse.h"


void Ellipse::draw(QPaintDevice *device)
{
    QPainter* painter = new QPainter(device);
    painter->setBrush(Qt::white);
    painter->drawEllipse(m_rect);
    if(m_selected)
        drawSelection(painter);
    if(m_shouldDrawCenter)
        drawEllipseCenter(painter);

    delete painter;
}

bool Ellipse::contains(const QPoint &point)
{
    std::unique_ptr<QGraphicsEllipseItem> ellipse(new QGraphicsEllipseItem(m_rect));
    if(ellipse->contains(point))
        return true;

    return false;
}

