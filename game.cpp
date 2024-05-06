#include "game.h"
#include <QApplication>
#include <qprocess.h>
#include <QPushButton>
#include "qpainter.h"
#include <vector>
#include "qpixmap.h"
#include <qpoint.h>
#include <QMouseEvent>
#include <enemy.h>
#include <qtimer.h>
#include <qobject.h>
#include "tower.h"
#include "bullet.h"
#include <qmediaplayer.h>
GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    waves(0),
    myHp(5),
    cost(1000)
{

    this->setWindowTitle("Arknights");
    this->setWindowIcon(QIcon(":/Resources/app.ico"));
    GameWindow::loadTowerPositions();
    GameWindow::addWayPoints();
    QPushButton *restartButton = new QPushButton("重启", this);
    restartButton->setGeometry(1100, 30, 100, 30);

    // 连接按钮点击事件到槽函数
    connect(restartButton, &QPushButton::clicked, this, &GameWindow::restart);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateMap()));
    timer->start(30);//游戏速度
    loadWave();//加载关卡
}
static const int Towercost=600;//角色的耗费

void GameWindow::restart()
{
    // 执行重新启动操作
    QApplication::quit();
    QProcess::startDetached(QApplication::applicationFilePath());
}

void GameWindow::addBullet(Bullet* bullet)
{
    Q_ASSERT(bullet);//判断一下
    m_bulletList.push_back(bullet);
}

void GameWindow::removedBullet(Bullet* bullet)
{
    Q_ASSERT(bullet);
    m_bulletList.removeOne(bullet);
    delete bullet;
}

void GameWindow::mousePressEvent(QMouseEvent *event)
{
   static int type=0;
   QPoint pressPos = event->pos();
   //角色牌范围
   if(50<pressPos.x()&&pressPos.x()<100&&50<pressPos.y()&&pressPos.y()<100)
   {
       type=0;
   }
   if(150<pressPos.x()&&pressPos.x()<200&&50<pressPos.y()&&pressPos.y()<100)
   {
       type=1;
   }

   auto it = m_towerPositionsList.begin();
   while(it != m_towerPositionsList.end())//判断是否可以放置
   {
       if(canBuyTower() && it->containPoint(pressPos) && !it->hasTower())
       {
           it->setHasTower(true);
           Tower *tower = new Tower(it->Center(),this);
           tower->setType(type);
           m_towersList.push_back(tower);
           cost-=Towercost;
           update();
           break;
       }
       ++it;
   }
}

void GameWindow::awardCost(int gold)
{
   cost += gold;
}

void GameWindow::updateMap()//游戏持续运行状态
{
    foreach(Enemy *enemy, m_enemyList)
        enemy->move();
    foreach(Tower *tower,m_towersList)
        tower->checkEnemyinRange();
    update();
}


void GameWindow::removedEnemy(Enemy *enemy)
{
    Q_ASSERT(enemy);
    m_enemyList.removeOne(enemy);
    delete enemy;
    if(m_enemyList.empty())
    {
        ++waves;
        if(!loadWave())
        {
            m_gameWin = true;
        }
    }
}

//加载关卡
bool GameWindow::loadWave()
{
    if(waves >= 10)
       return false;//十波之后结束
    Waypoint* startWayPoint = m_waypointList[0];
    int enemyStartInterval[]={500,1500,2500,3500,4500,5500};
    for(int i=0;i < 6; ++i)
    {
       Enemy *enemy = new Enemy(startWayPoint,this,waves);
        m_enemyList.push_back(enemy);
        QTimer::singleShot(enemyStartInterval[i], enemy, SLOT(doActivate()));
    }
    return true;
}

GameWindow::~GameWindow()
{
    delete ui;
}

//绘制
void GameWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    if(m_gameEnded || m_gameWin)
    {
        QString text = m_gameEnded ? "逊啊":"不愧是你";
        painter.setPen(QPen(Qt::red));
        QFont font;
        font.setPointSize(32);
        painter.setFont(font);
        painter.drawText(rect(),Qt::AlignCenter,text);
        return;
    }

    painter.drawPixmap(0, 0, QPixmap(":/Resources/gameback.jpg"));
    painter.setPen(QPen(Qt::white));
    painter.drawText(QRect(400, 25, 100, 25), QString("WAVE : %1").arg(waves + 1));
    painter.drawText(QRect(30, 25, 100, 25), QString("HP : %1").arg(myHp));
    painter.drawText(QRect(200, 25, 200, 25), QString("COST : %1").arg(cost));
    painter.drawPixmap(50,50,QPixmap(":/Resources/akx.png"));
    painter.drawPixmap(150,50,QPixmap(":/Resources/sy.png"));
    foreach (const Towerpos &towerPos, m_towerPositionsList)
        towerPos.draw(&painter);
    foreach (Tower *tower, m_towersList)
    {
        tower->draw_range(&painter);

    }
    foreach(Enemy* enemy, m_enemyList)
        enemy->draw(&painter);
    foreach (const Bullet *bullet, m_bulletList)
        bullet->draw(&painter);
}

bool GameWindow::canBuyTower() const
{

    if(cost >= Towercost)
        return true;
    else {
        return false;
    }
}

void GameWindow::getHpDamage()
{
    myHp-=1;
    if(myHp<=0)
       m_gameEnded=true;
}

//部署位
void GameWindow::loadTowerPositions()
{
    QPoint pos[] =
    {
        QPoint(250, 450),QPoint(370,450),QPoint(400,240),
        QPoint(490,450),QPoint(610,450),QPoint(610,330),
        QPoint(730,450),QPoint(850,450),

    };
    int len	= 8;

    for (int i = 0; i < len; ++i)
       m_towerPositionsList.push_back(Towerpos(pos[i]));
}

//路径点
void GameWindow::addWayPoints()
{
    Waypoint *waypoint1=new Waypoint(QPoint(250,250));
    m_waypointList.push_back(waypoint1);
    Waypoint *waypoint2=new Waypoint(QPoint(335,250));
    waypoint1->setNextWayPoint(waypoint2);
    m_waypointList.push_back(waypoint2);
    Waypoint *waypoint3=new Waypoint(QPoint(335,370));
    waypoint2->setNextWayPoint(waypoint3);
    m_waypointList.push_back(waypoint3);
    Waypoint *waypoint4=new Waypoint(QPoint(550,370));
    m_waypointList.push_back(waypoint4);
    waypoint3->setNextWayPoint(waypoint4);
    Waypoint *waypoint5=new Waypoint(QPoint(550,260));
    m_waypointList.push_back(waypoint5);
    waypoint4->setNextWayPoint(waypoint5);
    Waypoint *waypoint6=new Waypoint(QPoint(740,260));
    m_waypointList.push_back(waypoint6);
    waypoint5->setNextWayPoint(waypoint6);
    Waypoint *waypoint7=new Waypoint(QPoint(740,370));
    m_waypointList.push_back(waypoint7);
    waypoint6->setNextWayPoint(waypoint7);
    Waypoint *waypoint8=new Waypoint(QPoint(1040,370));
    m_waypointList.push_back(waypoint8);
    waypoint7->setNextWayPoint(waypoint8);
}
