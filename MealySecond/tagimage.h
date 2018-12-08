#ifndef TAGIMAGE_H
#define TAGIMAGE_H

#include "food.h"
#include "info.h"
#include <QDialog>
#include <QDate>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QFileInfo>
#include <QMouseEvent>
#include <QLabel>

namespace Ui {
class TagImage;
}

class TagImage : public QDialog
{
    Q_OBJECT

public:
    explicit TagImage(QWidget *parent = nullptr);
    void SetTag(QString str);
    void SetLabel();
    bool eventFilter(QObject *object, QEvent *event);
    ~TagImage();

private:
    QSqlDatabase tagdb;
    QString tagname;
    Food * tagImage[12];
    int size;
    Ui::TagImage *ui;
};

#endif // TAGIMAGE_H
