#include "gamestart.h"
#include <QPalette>
#include <QIcon>
#include <QBrush>
#include <QPainter>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QFont>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    this->resize(1200,1200);
    this->setWindowTitle("hungry snake");
    this->setWindowIcon(QIcon(":/res/app.ico"));
    this->setGeometry(QRect(800,400,1200,1200));
    QPalette palette;
    QPixmap pixmap=QPixmap(":/res/back.jpg").scaled(this->size());
    palette.setColor(QPalette::Window,Qt::blue);
    palette.setBrush(QPalette::Window,QBrush(pixmap));
    this->setPalette(palette);

    this->label = new QLabel(this);
    label->setPixmap(QPixmap(":/res/app/ico"));

    //添加按钮
    this ->startBtn = new QPushButton(this);
    QLabel *startLl = new QLabel();
    startLl->setText("开始游戏");
    startLl->setParent(startBtn);
    startLl->setAlignment(Qt::AlignCenter);
    QFont ft;
    ft.setPointSize(10);
    startLl->setFont(ft);
    QVBoxLayout *startLlhBox = new QVBoxLayout(startBtn);
    startLlhBox->addWidget(startLl);
    startBtn->move(540,200);
    startBtn->resize(160,100);
    connect(startBtn, &QPushButton::clicked, this, &Widget::startBtnclick);

    //按钮
    this->setBtn= new QPushButton(this);
    QLabel *setLl = new QLabel();
    setLl->setText("游戏设置");
    setLl->setParent(startBtn);
    setLl->setAlignment(Qt::AlignCenter);
    QFont ft1;
    ft1.setPointSize(10);
    setLl->setFont(ft1);
    QVBoxLayout *setLlBox = new QVBoxLayout(setBtn);
    setLlBox->addWidget(setLl);
    setBtn->move(540,400);
    setBtn->resize(160,100);

    this->helpBtn= new QPushButton(this);
    QLabel *helpLl = new QLabel();
    helpLl->setText("关于游戏");
    helpLl->setParent(startBtn);
    helpLl->setAlignment(Qt::AlignCenter);
    QFont ft2;
    ft2.setPointSize(10);
    helpLl->setFont(ft2);
    QVBoxLayout *helpLlBox = new QVBoxLayout(helpBtn);
    helpLlBox->addWidget(helpLl);
    helpBtn->move(540,600);
    helpBtn->resize(160,100);

    this->quitBtn= new QPushButton(this);
    QLabel *quitLl = new QLabel();
    quitLl->setText("退出游戏");
    quitLl->setParent(startBtn);
    quitLl->setAlignment(Qt::AlignCenter);
    QFont ft3;
    ft3.setPointSize(10);
    quitLl->setFont(ft3);
    QVBoxLayout *quitLlBox = new QVBoxLayout(quitBtn);
    quitLlBox->addWidget(quitLl);
    quitBtn->move(540,800);
    quitBtn->resize(160,100);
    connect(quitBtn, &QPushButton::clicked, this, &Widget::quitBtnclick);


}

void Widget::startBtnclick(){
    this->hide();
    win->show();
}

void Widget::quitBtnclick(){

    this->close();
    exit(0);
}

