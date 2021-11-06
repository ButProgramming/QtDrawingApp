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

#include <vector>
using namespace std;

namespace consts
{
    const int sizeOfCenterEllipse = 20;
}

class Shape
{
public:
    Shape(const QRect& rect) : m_rect(rect) {}
    virtual ~Shape(){}
    virtual void draw(QPaintDevice* device) = 0;

    void updateCreate(int lastX, int lastY)
    {
        m_rect.setBottomRight(QPoint(lastX, lastY));
    };

    QPoint getCenter()
    {
        return m_rect.center();
    }


protected:
    QRect m_rect;
    int m_x{};
    int m_y{};
    int m_length{};
    int m_width{};
    bool m_selected = false;
};


#endif // ISHAPE_H
