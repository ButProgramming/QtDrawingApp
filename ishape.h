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
    QRect m_rect;

protected:

    int m_x{};
    int m_y{};
    int m_length{};
    int m_width{};
    bool m_selected = false;
};


#endif // ISHAPE_H
