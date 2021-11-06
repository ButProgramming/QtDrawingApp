#ifndef AREASHAPE_H
#define AREASHAPE_H

#include "ishape.h"


class AreaShape : public IShape
{
public:
    AreaShape(const QRect& rect) : IShape(rect) {}

    virtual bool contains(const QPoint& point) = 0;

    virtual void drawSelection(QPainter& painter);
    void setSelected(bool selected) { m_selected = selected;}
    bool isSelected() {return m_selected;}
    void update(int dx, int dy)
    {
        m_rect.setBottomLeft(QPoint(m_rect.bottomLeft().x() - dx, m_rect.bottomLeft().y() - dy));
        m_rect.setTopRight(QPoint(m_rect.topRight().x() - dx, m_rect.topRight().y() - dy));
    }
    void drawCenter(bool shouldDrawCenter)
    {
        m_shouldDrawCenter = shouldDrawCenter;
    }
protected:
    bool m_shouldDrawCenter = false;
    //void setNotSelected() { isSelected = false;}

};

#endif // AREASHAPE_H
