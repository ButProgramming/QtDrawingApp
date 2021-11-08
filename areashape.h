#ifndef AREASHAPE_H
#define AREASHAPE_H

#include "ishape.h"


class AreaShape : public IShape
{
public:
    AreaShape(const QPoint& point) : IShape(point) { m_ID = ID++; }

    virtual ~AreaShape(){}
    virtual bool contains(const QPoint& point) = 0;
    virtual void drawSelection(QPainter* painter);

    void safe(QDataStream &out) override;
    void load(QDataStream &in) override;
    void updateCreate(const QPoint& lastPoint) override;

    void update(const QPoint& differense);
    void drawCenter(bool shouldDrawCenter) { m_shouldDrawCenter = shouldDrawCenter; }
    bool containsCenter(const QPoint& point);
    void drawEllipseCenter(QPainter* painter);

    void setSelected(bool selected) { m_selected = selected;}
    bool isSelected() {return m_selected;}
    int getID() {return m_ID;}
    QPoint getCenter() { return m_rect.center(); }

protected:
    bool m_shouldDrawCenter = false;
    static int ID;
    int m_ID{};
    bool m_selected = false;
};

#endif // AREASHAPE_H
