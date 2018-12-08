#ifndef ALLIMAGE_H
#define ALLIMAGE_H

#include <QDialog>
#include <QHBoxLayout>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QFileInfo>
#include <QStringList>
#include <QMouseEvent>
#include <QLabel>

namespace Ui {
class AllImage;
}

class AllImage : public QDialog
{
    Q_OBJECT

public:
    explicit AllImage(QWidget *parent = nullptr);
    ~AllImage();

private:
    QSqlDatabase allimagedb;
    Ui::AllImage *ui;
};

#endif // ALLIMAGE_H
