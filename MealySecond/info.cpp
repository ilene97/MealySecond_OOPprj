#include "info.h"
#include "ui_info.h"
#include <QDebug>

Info::Info(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Info)
{
    ui->setupUi(this);
    this->setWindowTitle("Show Detail");
}

void Info::SetInfo(Food * info, QString category){
    ui->image->setPixmap(QPixmap(info->getImage()));
    QString sdate = info->getDate().toString("yyyy/MM/dd");
    qDebug()<<sdate;
    ui->label_date->setText(sdate);
    ui->label_place->setText(info->getPlace());
    ui->label_cate->setText(category);
}

Info::~Info()
{
    delete ui;
}
