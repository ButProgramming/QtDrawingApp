#ifndef AREASHAPE_H
#define AREASHAPE_H

#include "shape.h"


class AreaShape : public Shape
{
public:
    AreaShape(const QRect& rect) : Shape(rect) { m_ID = ID++; }

    virtual ~AreaShape(){}
    virtual bool contains(const QPoint& point) = 0;
    virtual void drawSelection(QPainter& painter);
    void safe(QDataStream &out) override;
    void load(QDataStream &in) override;

    void setSelected(bool selected) { m_selected = selected;}
    bool isSelected() {return m_selected;}
    void update(int dx, int dy)
    {
        m_rect.setBottomLeft(QPoint(m_rect.bottomLeft().x() - dx, m_rect.bottomLeft().y() - dy));
        m_rect.setTopRight(QPoint(m_rect.topRight().x() - dx, m_rect.topRight().y() - dy));
    }
    QPoint getCenter()
    {
        return m_rect.center();
    }
    void drawCenter(bool shouldDrawCenter)
    {
        m_shouldDrawCenter = shouldDrawCenter;
    }

    bool containsCenter(QPoint point)
    {
        QRect rect(
                   m_rect.center().x() - consts::sizeOfCenterEllipse,
                   m_rect.center().y() - consts::sizeOfCenterEllipse,
                   consts::sizeOfCenterEllipse*2,
                   consts::sizeOfCenterEllipse*2
                   );
        QGraphicsEllipseItem centerEllipse(rect);

        if(centerEllipse.contains(point))
            return true;

        return false;

    }

    int getID() {return m_ID;}
protected:
    bool m_shouldDrawCenter = false;
    static int ID;
    int m_ID{};
    bool m_selected = false;

};

#endif // AREASHAPE_H
