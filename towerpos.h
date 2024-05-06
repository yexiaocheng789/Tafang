#ifndef TOWERPOS_H
#define TOWERPOS_H
#include "qpainter.h"
#include "qpoint.h"
#include "qpixmap.h"

class Towerpos
{
public:
    Towerpos(QPoint pos,const QPixmap &sprite=QPixmap(":/Resources/keng.png"));
    void setHasTower(bool hasTower = true);
    bool hasTower() const;
    const QPoint Center() const;
    bool containPoint(const QPoint &pos) const;
    void draw(QPainter *painter) const;

 private:
    QPoint   towerpos;
    bool     m_hasTower;
    QPixmap  sprite;
    static const QSize Size;
};

#endif // TOWERPOS_H
