#include "triangle.h"

void Triangle::draw(QPaintDevice* device)
{
	QPainter* painter = new QPainter(device);
	QPainterPath* path = new QPainterPath();
	QPen* pen = new QPen(Qt::black);

	path->moveTo(m_rect.left() + (m_rect.width() / 2), m_rect.top());
	path->lineTo(m_rect.bottomLeft());
	path->lineTo(m_rect.bottomRight());
	path->lineTo(m_rect.left() + (m_rect.width() / 2), m_rect.top());

	pen->setWidth(consts::sizeOfPenForTriangle);
	painter->setPen(*pen);
	painter->drawPath(*path);
	painter->fillPath(*path, QBrush(QColor("white")));

	pen->setWidth(consts::standartSizeOfPen);
	painter->setPen(*pen);

	if (m_selected)
		drawSelection(painter);
	if (m_shouldDrawCenter)
		drawEllipseCenter(painter);


	delete pen;
	delete path;
	delete painter;
}

bool Triangle::contains(const QPoint& point)
{
	std::unique_ptr<QPainterPath> path(new QPainterPath());
	path->moveTo(m_rect.left() + (m_rect.width() / 2), m_rect.top());
	path->lineTo(m_rect.bottomLeft());
	path->lineTo(m_rect.bottomRight());
	path->lineTo(m_rect.left() + (m_rect.width() / 2), m_rect.top());
	if (path->contains(point))
		return true;

	return false;
}

