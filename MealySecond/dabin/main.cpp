#include "mainwindow.h"

#include <QSplashScreen>
#include <QApplication>
#include <QTimer>
#include <QPixmap>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSplashScreen * splash = new QSplashScreen;
    splash-> setPixmap(QPixmap("C:/Users/user/Documents/HeeJinBin/Splash.png"));
    MainWindow mw;

    splash->show();
    QTimer::singleShot(1500,&mw,SLOT(show()));
    QTimer::singleShot(1500,splash,SLOT(close()));

    return a.exec();
}
