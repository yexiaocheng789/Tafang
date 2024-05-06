#include "tower.h"
#include "game.h"
#include <enemy.h>
#include <bullet.h>
#include <qpixmap.h>
#include <qpainter.h>
#include <qsize.h>
#include <QColor>
#include <QTimer>
#include <QVector2D>
#include <QtMath>
#include <round.h>
const QSize Tower::Size(44, 44);

Tower::Tower(QPoint pos,GameWindow* game,const QPixmap &sprite)
: m_damage(10)
, m_firerate(100)//攻击频率
, m_chooseEnemy(NULL)
, m_game(game)
, m_pos(pos)
, m_sprite(sprite)
, m_type(0)
{
  m_attackRange=150;//攻击范围
  m_fireRateTimer = new QTimer(this);
  connect(m_fireRateTimer, SIGNAL(timeout()), this, SLOT(shootWeapon()));
}

//选择敌人
void Tower::chooseEnemyforAttack(Enemy* enemy)
{
  m_chooseEnemy=enemy;
  attackEnemy();
  m_chooseEnemy->getAttacked(this);
}

void Tower::checkEnemyinRange()
{
    if(m_chooseEnemy)
    {
      if(!judgeCircle(m_pos,m_attackRange,m_chooseEnemy->pos(),1))
            looseSightofEnemy();//范围内没有敌人
    }
    else {
        QList<Enemy *> enemyList = m_game->enemyList();
        foreach(Enemy *enemy,enemyList)
            if(judgeCircle(m_pos,m_attackRange,enemy->pos(),1))
               { chooseEnemyforAttack(enemy);
                 break;}
    }
}

void Tower::attackEnemy()
{
    m_fireRateTimer->start(m_firerate);
}

//攻击
void Tower::shootWeapon()
{
    Bullet *bullet = new Bullet(m_pos,m_chooseEnemy->pos(),m_damage,m_chooseEnemy,m_game,m_type);
    bullet->move();
    m_game->addBullet(bullet);
}

//目标击杀
void Tower::targetkilled()
{
    if(m_chooseEnemy)
    {m_chooseEnemy=NULL;}
    m_fireRateTimer->stop();
}

void Tower::looseSightofEnemy()
{
    m_chooseEnemy->gotLostSight(this);
    if(m_chooseEnemy)
        m_chooseEnemy=NULL;
    m_fireRateTimer->stop();

}

bool Tower::hasEnemy()
{
    if(m_chooseEnemy)
        return true;
    else {
        return false;
    }
}

void Tower::draw_range(QPainter *painter)
{
    if(m_type==1)
    m_sprite = QPixmap(":/Resources/sy.png");
    painter->save();
    static const QPoint offsetPoint(-Size.width()/2,-Size.height()/2);
    painter->translate(m_pos);
    painter->drawPixmap(offsetPoint,m_sprite);
    painter->restore();
}


