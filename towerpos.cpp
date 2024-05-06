#include "towerpos.h"
#include "qpainter.h"
#include "qpoint.h"
#include "qsize.h"

const QSize Towerpos::Size(44, 44);

Towerpos::Towerpos(QPoint pos,const QPixmap &sprite)
    :towerpos(pos),m_hasTower(false),sprite(sprite)
{

}

//部署位中心
const QPoint Towerpos::Center() const
{
  QPoint offsetPoint(Size.width() / 2, Size.height() / 2);
    return towerpos + offsetPoint;
}
// 判断是否点击的是区域内
bool Towerpos::containPoint(const QPoint &pos) const
{
    bool isXInHere = towerpos.x() < pos.x() && pos.x() < (towerpos.x() + Size.width());
    bool isYInHere = towerpos.y() < pos.y() && pos.y() < (towerpos.y() + Size.height());
    return isXInHere && isYInHere;
}

bool Towerpos::hasTower() const
{
   return m_hasTower;
}

void Towerpos::setHasTower(bool hasTower)
{
   m_hasTower=hasTower;
}

void Towerpos::draw(QPainter *painter) const
{
   painter->drawPixmap(towerpos.x(), towerpos.y(), sprite);
}



