#include "mainwindow.h"
#include "addimagedialog.h"
#include "food.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QSplashScreen *splash = new QSplashScreen;
    splash->setPixmap(QPixmap("C:/Users/ilene/Documents/Visual Studio 2017/Qt Projects/CalendarFunction/Splash.png"));

    splash->show();
    QTimer::singleShot(1500,splash,SLOT(close()));
    QTimer::singleShot(1500,&w,SLOT(show()));

    return a.exec();
}

