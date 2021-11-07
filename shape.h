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
#include <QDataStream>
#include <QtCore>
#include <QFile>

#include <vector>

enum class Type
{
    ELLIPSE,
    RECTANGLE,
    TRIANGLE,
    CONNECTION_LINE
};

namespace consts
{
    const int sizeOfCenterEllipse = 5;
}

class Shape
{
public:
    Shape(const QRect& rect) : m_rect(rect) {}
    virtual ~Shape(){}
    virtual void draw(QPaintDevice* device) = 0;
    virtual void safe(QDataStream& out) = 0;
    virtual void load(QDataStream& in) = 0;

    void updateCreate(int lastX, int lastY)
    {
        m_rect.setBottomRight(QPoint(lastX, lastY));
    };




protected:
    QRect m_rect;

};


#endif // ISHAPE_H
