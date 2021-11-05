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

class IShape;

class Node
{
    IShape* parent = nullptr;
    int x{};
    int y{};
};

class IShape
{
public:
    IShape(int x, int y, int length, int width) : m_x(x), m_y(y), m_length(length), m_width(width){};
    virtual void draw(QPaintDevice* device) = 0;
protected:
    int m_x{};
    int m_y{};
    int m_length{};
    int m_width{};
};

class Ellipse : public IShape
{
public:
    Ellipse(int x, int y, int length, int width) : IShape(x, y, length, width){}
    void draw(QPaintDevice* device)
    {
        QPainter painter(device);
        painter.setBrush(Qt::white);
        painter.drawEllipse(QRect(m_x, m_y, m_length, m_width));
        qDebug() << m_x << " " << m_y;
    }
};

#endif // ISHAPE_H
