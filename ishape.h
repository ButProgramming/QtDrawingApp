#ifndef ISHAPE_H
#define ISHAPE_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QPainter>
#include <QEvent>

#include <QObject>
#include <QCursor>
#include <QPoint>
#include <QDebug>
#include <QGraphicsEllipseItem>


class IShape
{
public:
    IShape(const QRect& rect) : m_rect(rect) {}
    virtual void draw(QPaintDevice* device) = 0;

protected:
    QRect m_rect;
    int m_x{};
    int m_y{};
    int m_length{};
    int m_width{};
    bool isSelected = false;
};


#endif // ISHAPE_H
