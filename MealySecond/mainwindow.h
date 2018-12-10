#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QString>
#include <QLabel>
#include <QPainter>
#include <QMouseEvent>
#include <Qt>
#include <QToolButton>
#include <QMap>
#include <QList>
#include <QPalette>
#include <QVBoxLayout>
#include <QtSql>
#include <QSqlQuery>
#include <QFileInfo>
#include "recommend.h"

#include "food.h"
#include "addimagedialog.h"

namespace Ui {
class MainWindow;
}

class Tag{
private:
    QString tagname;
    bool isTag;

public:
    Tag();

    void SetTag(QString name);

    void DeleteTag();

    QString GetTagName();

    bool GetIsTag();

};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    void SetTagName();

    QMap<QDate,QList<Food>> photosInDay;

    explicit MainWindow(QWidget *parent = nullptr);
    void RecommendFood(QString category);
    ~MainWindow();

signals:
    void sendDate(QDate);

public slots:
    void addFoodinMap(QDate date, Food *food);

private slots:
    void on_calendarWidget_clicked(const QDate &date);
    void on_addPhoto_clicked();
    void on_all_images_clicked();
    void on_tag_filter_clicked();
    void on_tag1_bt_clicked();
    void on_tag2_bt_clicked();
    void on_tag3_bt_clicked();
    void on_tag4_bt_clicked();
    void on_tag5_bt_clicked();
    void on_tag6_bt_clicked();
    void on_tag7_bt_clicked();
    void on_tag8_bt_clicked();

    void on_mealButton_clicked();

    void on_dessertButton_clicked();

    void on_midsnackButton_clicked();

private:
    Tag * tag[8];
    Ui::MainWindow *ui;
    QDate today;
    int today_int;
    QSqlDatabase mydb;

};

#endif // MAINWINDOW_H

