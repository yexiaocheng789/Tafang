#ifndef TOWER_H
#define TOWER_H
#include <qpoint.h>
#include <qpixmap.h>
#include <enemy.h>
#include <game.h>
class Enemy;
class GameWindow;
class Tower:public QObject
{
    Q_OBJECT
public:
    Tower(QPoint pos,GameWindow* game,const QPixmap &sprite=QPixmap(":/Resources/akx.png"));
    void draw_range(QPainter *painter);
    void targetkilled();
    void attackEnemy();
    void chooseEnemyforAttack(Enemy* enemy);
    void removeBullet();
    void looseSightofEnemy();
    void checkEnemyinRange();
    void setType(int type){m_type=type;}
    bool hasEnemy();
public slots:
    void shootWeapon();
protected:
    static const QSize Size;
    QPoint m_pos;
    int m_attackRange;
    int m_damage;
    int m_firerate;
    QPixmap  m_sprite;
    Enemy* m_chooseEnemy;
    QTimer* m_fireRateTimer;
    GameWindow* m_game;
    int m_type;
};

#endif // TOWER_H
