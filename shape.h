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
#include <array>

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
    const int firstPoint = 0; // for std::array
    const int secondPoint = 1;
}

class Shape
{
public:
    Shape() {}
    Shape(const QRect& rect) : m_rect(rect) {}
    Shape(const QPoint& point) : m_rect(QRect(point.x(), point.y(), NULL, NULL)) {}
    virtual ~Shape(){}
    virtual void draw(QPaintDevice* device) = 0;
    virtual void safe(QDataStream& out) = 0;
    virtual void load(QDataStream& in) = 0;

    virtual void updateCreate(int lastX, int lastY) = 0;




protected:
    QRect m_rect;

};


#endif // ISHAPE_H
