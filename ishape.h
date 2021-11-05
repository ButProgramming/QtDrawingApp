#ifndef ISHAPE_H
#define ISHAPE_H

/*#include <QMainWindow>
#include <QObject>
#include <QWidget>*/
#include <QMainWindow>
#include <QMouseEvent>
#include <QPainter>
#include <QEvent>

#include <QObject>
#include <QCursor>
#include <QPoint>
#include <QDebug>


class IShape
{
public:
    IShape(const QRect& rect) : m_rect(rect) {}
    IShape(int x, int y, int length, int width) : m_x(x), m_y(y), m_length(length), m_width(width){}
    virtual void draw(QPaintDevice* device) = 0;

protected:
    QRect m_rect;
    int m_x{};
    int m_y{};
    int m_length{};
    int m_width{};
};

class Rectangle : public IShape
{
public:
    Rectangle(const QRect& rect) : IShape(rect) {}
    void draw(QPaintDevice *device) override
    {
        QPainter painter(device);
        painter.setBrush(Qt::white);
        painter.drawRect(m_rect);
        qDebug() << m_x << " " << m_y;
    }
};

class Ellipse : public IShape
{
public:
    Ellipse(const QRect& rect) : IShape(rect) {}
    Ellipse(int x, int y, int length, int width) : IShape(x, y, length, width){}

    void draw(QPaintDevice* device) override
    {
        QPainter painter(device);
        painter.setBrush(Qt::white);
        painter.drawEllipse(QRect(m_x, m_y, m_length, m_width));
        qDebug() << m_x << " " << m_y;
    }
};

class Triangle : public IShape
{
public:
    Triangle(const QRect& rect) : IShape(rect) {}

    void draw(QPaintDevice* device) override
    {
        QPainter painter(device);
        QPainterPath path;


        path.moveTo(m_rect.left() + (m_rect.width() / 2), m_rect.top());
        path.lineTo(m_rect.bottomLeft());
        path.lineTo(m_rect.bottomRight());
        path.lineTo(m_rect.left() + (m_rect.width() / 2), m_rect.top());


        QPen pen(Qt::black);
        pen.setWidth(2);
        painter.setPen(pen);
        painter.drawPath(path);
        painter.fillPath(path, QBrush(QColor ("white")));
    }
};

class ConnectionLine : public IShape
{
public:
    ConnectionLine(const QRect& rect) : IShape(rect){}

    void draw(QPaintDevice* device) override
    {
        QPainter painter(device);
        QPainterPath path;

        path.moveTo(m_rect.left(), m_rect.top());
        path.lineTo(m_rect.bottomRight());

        QPen pen(Qt::black);
        pen.setWidth(2);
        painter.setPen(pen);
        painter.drawPath(path);
        //path.lineTo(m_rect.bottomRight());
        //path.lineTo(m_rect.left() + (m_rect.width() / 2), m_rect.top());
    }
};

#endif // ISHAPE_H
