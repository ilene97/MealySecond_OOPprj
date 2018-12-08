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
    MainWindow(QWidget *parent = nullptr);

    void SetTagName();

    ~MainWindow();

private slots:
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

private:
    Tag * tag[8];

protected:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
