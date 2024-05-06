#ifndef BULLET_H
#define BULLET_H
#include <qpoint.h>
#include <qpropertyanimation.h>
#include "enemy.h"
#include <game.h>
#include <qsize.h>
class GameWindow;
class Enemy;
class Bullet:public QObject
{
    Q_OBJECT
    Q_PROPERTY(QPoint m_currentPos READ currentPos WRITE setCurrentPos)
public:
    Bullet(QPoint startPos,QPoint targetPos,int damage,Enemy* target,GameWindow *game,int type,
    const QPixmap& sprite = QPixmap(":/Resources/bullet.png"));

    void draw(QPainter *painter) const;//图形
    void move();//子弹移动
    void setCurrentPos(QPoint pos);//实际坐标
    QPoint currentPos(){return m_currentPos;}//返回实际坐标
public slots://槽函数
    void hitTarget();
private:
    QPoint m_currentPos;
    const QPoint m_startPos;
    const QPoint m_targetPos;
    QPixmap m_sprite;
    Enemy* m_target;
    GameWindow* m_game;
    int m_damage;
    static const QSize m_size;
    int m_type;
};

#endif // BULLET_H
