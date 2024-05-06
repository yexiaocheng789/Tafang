#include "game.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameWindow w;
    w.setFixedSize(1280,720);
    // 创建一个按钮来触发暂停和恢复界面

    w.show();
    return a.exec();


}
