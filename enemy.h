#ifndef ENEMY_H
#define ENEMY_H
#include <qpoint.h>
#include <qpixmap.h>
#include <waypoint.h>
#include <qobject.h>
#include <qsize.h>
#include <qpainter.h>
#include <qlist.h>
class WayPoint;
class QPainter;
class GameWindow;
class Tower;

class Enemy:public QObject
{
    Q_OBJECT
public:
    Enemy(Waypoint *startWayPoint, GameWindow *game, int waves, const QPixmap &sprite=QPixmap(":/Resources/dl.png"));
    ~Enemy();
    void draw(QPainter *painter);
    void move();
    QPoint pos();
    void getRemoved();
    void getDamaged(int damage);
    void getAttacked(Tower* attacker);
    void gotLostSight(Tower* attacker);
    void slowdown();
public slots:
    void doActivate();
protected:
    int AllHp;
    int NowHp;
    double runSpeed;
    bool run;
    QPoint m_pos;
    QPixmap m_sprite;
    Waypoint* EnemyWay;
    GameWindow* m_game;
    QSize enermySize;
    QList<Tower*> AttackTower;
    int m_waves;
    bool isSlowedDown=false;
};
#endif // ENEMY_H
