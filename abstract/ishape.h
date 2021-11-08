#ifndef ISHAPE_H
#define ISHAPE_H

#include <QMainWindow>
#include <QPainter>
#include <QPoint>
#include <QDebug>
#include <QGraphicsEllipseItem>
#include <QDataStream>

// stl
#include <vector>
#include <utility>
#include <memory>

enum class Type
{
	ELLIPSE,
	RECTANGLE,
	TRIANGLE,
	CONNECTION_LINE
};

namespace consts
{
	const int sizeOfCenterEllipse = 8;
	const int sizeOfPenForTriangle = 2;
	const int standartSizeOfPen = 1;
	const int sizeOfPenForLine = 2;
}

class IShape
{
public:
	IShape() {}
	IShape(const QPoint& point) : m_rect(QRect(point.x(), point.y(), NULL, NULL)) {}
	virtual ~IShape() {}

	virtual void draw(QPaintDevice* device) = 0;
	virtual void safe(QDataStream& out) = 0;
	virtual void load(QDataStream& in) = 0;
	virtual void updateCreate(const QPoint& lastPoint) = 0;

protected:
	QRect m_rect;
};


#endif // ISHAPE_H
