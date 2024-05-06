#ifndef GAME_H
#define GAME_H
#include <QMainWindow>
#include <qlist.h>
#include <towerpos.h>
#include <waypoint.h>
#include <enemy.h>

class Tower;
namespace Ui {
class MainWindow;
}
class Bullet;
class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();
    void getHpDamage();
    void removedEnemy(Enemy *enemy);
    void removedBullet(Bullet *bullet);
    bool loadWave();
    QList<Enemy*> enemyList(){return m_enemyList;}
    void addBullet(Bullet* bullet);
    void awardCost(int gold);
public slots:
    void updateMap();
    void restart();
private:
    Ui::MainWindow *ui;
    void paintEvent(QPaintEvent *);
    QList<Towerpos> m_towerPositionsList;
    QList<Tower *> m_towersList;
    QList<Waypoint*> m_waypointList;
    QList<Enemy *> m_enemyList;
    QList<Bullet *> m_bulletList;
    void loadTowerPositions();
    void mousePressEvent(QMouseEvent *event);
    void addWayPoints();
    bool canBuyTower() const;
    int waves;
    int myHp;
    int cost;
    bool m_gameWin;
    bool m_gameEnded;

};

#endif // GAME_H
