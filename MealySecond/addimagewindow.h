#ifndef ADDIMAGEWINDOW_H
#define ADDIMAGEWINDOW_H

#include <QWidget>
#include <QFileDialog>

#include "food.h"

namespace Ui {
class AddImageWindow;
}

class AddImageWindow : public QWidget
{
    Q_OBJECT

signals:
    void sendNewFood(Food);

public:
    explicit AddImageWindow(QWidget *parent = nullptr);
    ~AddImageWindow();

    QString getTag();
    QString getPlace();
    QString getImageLocation();
    Food getThisFood();

private slots:
    void on_cancelButton_clicked();

    void on_pushButton_clicked();

    void on_OKButton_clicked();

    void setDate(QDate date);

private:
    Ui::AddImageWindow *ui;

    QString tag, place, image;
    QDate date;
    Food *thisfood;
};

#endif // ADDIMAGEWINDOW_H
