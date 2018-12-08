#ifndef ADDIMAGEDIALOG_H
#define ADDIMAGEDIALOG_H

#include <QtWidgets>
#include <QDate>
#include "food.h"
#include "dish.h"
#include "dessert.h"
#include "midnightsnack.h"

#include <QtSql>
#include <QSqlQuery>
#include <QDebug>
#include <QFileInfo>

namespace Ui {
class AddImageDialog;
}

class AddImageDialog : public QDialog
{
    Q_OBJECT

//signals:
  //void sendNewFood(QDate,Food);


public:
    explicit AddImageDialog(QWidget *parent = nullptr);
    ~AddImageDialog();

    bool eventFilter(QObject *object, QEvent *event);
    int getRate();

    QString getTag();
    QString getPlace();
    QString getImageLocation();
    Food* getThisFood();


private slots:
    //void on_cancelButton_clicked();

    void on_pushButton_clicked();

    void on_OKButton_clicked();

    void setDate(QDate date);


private:
    Ui::AddImageDialog *ui;
    QString tag, place, image;
    QDate date;
    Food *thisfood;
    bool isStar[5];

    QSqlDatabase mydb;


};

#endif // ADDIMAGEDIALOG_H
