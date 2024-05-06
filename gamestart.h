#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <qlabel.h>
#include <qpushbutton.h>
#include "game.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);

    QLabel *label;
    QPushButton *startBtn;
    QPushButton *setBtn;
    QPushButton *helpBtn;
    QPushButton *quitBtn;
    QLabel *startLl;
    game *win = new game;

public slots:
    void startBtnclick();
    void quitBtnclick();

signals:

};
#endif // WIDGET_H
