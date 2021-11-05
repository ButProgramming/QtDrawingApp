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
    IShape(int x, int y) : m_x(x), m_y(y){};
    virtual void draw(QPaintDevice* device) = 0;
protected:
    int m_x{};
    int m_y{};
};

class Ellipse : public IShape
{
public:
    Ellipse(int x, int y) : IShape(x, y){};
    void draw(QPaintDevice* device)
    {
        QPainter painter(device);
        QRect rect(m_x, m_y, 100, 100);
        painter.drawEllipse(rect);
        qDebug() << m_x << " " << m_y;
    }
};

#endif // ISHAPE_H
