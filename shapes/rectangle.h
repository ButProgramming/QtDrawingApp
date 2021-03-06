#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "abstract/areashape.h"

class Rectangle : public AreaShape
{
public:
	Rectangle(const QPoint& point) : AreaShape(point) {}

	void draw(QPaintDevice* device) override;
	bool contains(const QPoint& point) override;
	void drawSelection(QPainter* painter) override;
};

#endif // RECTANGLE_H
