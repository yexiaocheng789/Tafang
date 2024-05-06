#include "bullet.h"
#include <qpoint.h>
#include <qpixmap.h>
#include <game.h>
#include <enemy.h>
#include <tower.h>
#include <QPropertyAnimation>
#include <qsize.h>

// 设置子弹的大小
const QSize Bullet::m_size(8,8);

// 构造函数，初始化子弹的各个属性
Bullet::Bullet(QPoint startPos,QPoint targetPos,int damage
               ,Enemy* target,GameWindow *game,int type,const QPixmap &sprite)
    :m_startPos(startPos)
    ,m_targetPos(targetPos)
    ,m_currentPos(startPos)
    ,m_sprite(sprite)
    ,m_target(target)
    ,m_game(game)
    ,m_damage(damage)
    ,m_type(type)
{

}

// 绘制子弹
void Bullet::draw(QPainter *painter) const
{
    painter->drawPixmap(m_currentPos,m_sprite);
}

// 子弹移动的动画效果
void Bullet::move()
{
    static const int duration = 100;
    QPropertyAnimation *animation = new QPropertyAnimation(this, "m_currentPos");
    animation->setDuration(duration);
    animation->setStartValue(m_startPos);
    animation->setEndValue(m_targetPos);
    connect(animation,SIGNAL(finished()),this,SLOT(hitTarget()));
    animation->start();
}

// 设置当前位置
void Bullet::setCurrentPos(QPoint pos)
{
    m_currentPos=pos;
}

// 子弹击中目标
void Bullet::hitTarget()
{
    // 检查子弹类型，根据类型更新伤害
    if(m_type==1){
        m_damage=2;
        m_target->slowdown();
    }
    // 检查目标是否仍然是有效的敌人
    if (m_game->enemyList().indexOf(m_target) != -1)
        m_target->getDamaged(m_damage);


    //移除子弹
    m_game->removedBullet(this);
}
