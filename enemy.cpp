#include "enemy.h"
#include "waypoint.h"
#include "tower.h"
#include "round.h"
#include "game.h"
#include <math.h>
#include <QPainter>
#include <QColor>
#include <QDebug>
#include <QMatrix>
#include <QVector2D>
#include <QtMath>

// 敌人类的构造函数
Enemy::Enemy(Waypoint *startWayPoint, GameWindow *game, int waves ,const QPixmap &sprite)
    :QObject(0)
    ,m_pos(startWayPoint->pos())
    ,m_sprite(sprite)
    ,EnemyWay(startWayPoint->nextWayPoint())
    ,enermySize(60,40)
    ,m_waves(waves)
{
    AllHp = 100+m_waves*50;
    NowHp = 100+m_waves*50;//敌人数值
     run= false;
     runSpeed = 1+0.2*m_waves;//速度
     m_game = game;
};

Enemy::~Enemy()
{
     AttackTower.clear();
     EnemyWay = NULL;
    m_game = NULL;
}

// 当敌人失去视野时，从攻击列表中移除攻击者
void Enemy::gotLostSight(Tower *attacker)
{
    AttackTower.removeOne(attacker);
}

// 绘制敌人的方法
void Enemy::draw(QPainter *painter)
{
    if(!run)
        return;// 如果敌人没有运行，就返回并不执行任何操作
    static const int Health_Bar_Width = 20;//画血条
    painter->save();// 保存当前状态
    QPoint healthBarPoint = m_pos + QPoint(-Health_Bar_Width/2-5,-enermySize.height()/3);// 血条的位置
    painter->setPen(Qt::NoPen);// 设置画笔的样式为无边框
    painter->setBrush(Qt::red);// 设置画刷颜色为红色
    QRect healthBarBackRect(healthBarPoint,QSize((double)NowHp/AllHp * Health_Bar_Width,2));// 总血条背景的矩形区域
    painter->drawRect(healthBarBackRect);// 绘制血条背景
    painter->setBrush(Qt::green);
    QRect healthBarRect(healthBarPoint, QSize((double)NowHp / AllHp * Health_Bar_Width, 2));// 实际血条的矩形区域
    painter->drawRect(healthBarRect);
    static const QPoint offsetPoint(-enermySize.width()/2,-enermySize.height()/2);// 敌人图像的偏移点
    painter->translate(m_pos);// 平移画笔的坐标系到敌人的位置
    painter->drawPixmap(offsetPoint,QPixmap(":/Resources/enemy.png"));
    painter->restore();
}

// 获取敌人的位置
QPoint Enemy::pos(){return m_pos;}


void Enemy::move()
{
    if (!run)
        return;

    if (judgeCircle(m_pos, 1, EnemyWay->pos(), 1))
    {
        if (EnemyWay->nextWayPoint())
        {
            m_pos = EnemyWay->pos();
            EnemyWay = EnemyWay->nextWayPoint();
        }
        else
        {
            m_game->getHpDamage();
            m_game->removedEnemy(this);
            return;
        }
    }

    QPoint targetPoint = EnemyWay->pos();
    QPoint offsetPoint = (targetPoint-m_pos);
    if(offsetPoint.x()==0&&offsetPoint.y()>0)
    {
        m_pos = m_pos + QPoint(0,1)*2*runSpeed;}
    else if(offsetPoint.x()==0&&offsetPoint.y()<0){
        m_pos = m_pos + QPoint(0,-1)*2*runSpeed;
    }
    else if(offsetPoint.x()>0){
        m_pos = m_pos + QPoint(1,0)*2*runSpeed;
    }
    else {
        m_pos = m_pos + QPoint(-1,0)*2*runSpeed;
    }

}


void Enemy::doActivate()
{
    run = true;
}

void Enemy::getAttacked(Tower *attacker)
{
    AttackTower.push_back(attacker);
}

//
void Enemy::getRemoved()
{
    if(AttackTower.empty())
        return;
    foreach(Tower* attacker,AttackTower)
        attacker->targetkilled();
    m_game->removedEnemy(this);
}

//敌人受伤害
void Enemy::getDamaged(int damage)
{
    NowHp-=damage;
    if(NowHp<=1)//敌人死亡
        {
        m_game->awardCost(100);
        this->getRemoved();
        }
}

//减速效果
void Enemy::slowdown()
{
    if(isSlowedDown==false)
    {
        isSlowedDown=true;
        runSpeed*=0.5;
    }

}
