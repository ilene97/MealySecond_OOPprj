#include "filter.h"
#include "ui_filter.h"

Filter::Filter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Filter)
{
    ui->setupUi(this);
    ui->setting->setStyleSheet("border-image:url(C:/Users/ilene/Documents/Visual Studio 2017/Qt Projects/CalendarFunction/setting.png)");
    this->setWindowTitle("Filter");
}

void Filter::SetFilter(QString * filt){
    for(int i=0;i<8;i++)
        filter[i] = filt[i];

    ui->tedit1->setText(filter[0]);
    ui->tedit2->setText(filter[1]);
    ui->tedit3->setText(filter[2]);
    ui->tedit4->setText(filter[3]);
    ui->tedit5->setText(filter[4]);
    ui->tedit6->setText(filter[5]);
    ui->tedit7->setText(filter[6]);
    ui->tedit8->setText(filter[7]);
}

QString * Filter::GetFilter(){
    return filter;
}

Filter::~Filter()
{
    delete ui;
}

void Filter::on_setting_clicked()
{
    filter[0] = ui->tedit1->toPlainText();
    filter[1] = ui->tedit2->toPlainText();
    filter[2] = ui->tedit3->toPlainText();
    filter[3] = ui->tedit4->toPlainText();
    filter[4] = ui->tedit5->toPlainText();
    filter[5] = ui->tedit6->toPlainText();
    filter[6] = ui->tedit7->toPlainText();
    filter[7] = ui->tedit8->toPlainText();

    close();
}
