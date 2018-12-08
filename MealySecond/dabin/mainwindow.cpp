#include "mainwindow.h"
#include "filter.h"
#include "tagimage.h"
#include "allimage.h"
#include "ui_mainwindow.h"

Tag::Tag():isTag(false){
    tagname = "";
}

void Tag::SetTag(QString name){
    tagname=name;
    isTag=true;
}

void Tag::DeleteTag(){
    tagname = "";
    isTag = false;
}

bool Tag::GetIsTag(){
    return isTag;
}

QString Tag::GetTagName(){
    return tagname;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    for(int i=0;i<8;i++){
        tag[i] = new Tag();
    }

    //initial value
    tag[0]->SetTag("Sangdo");
    tag[1]->SetTag("Heukseok");
    tag[2]->SetTag("Gangnam");
    tag[3]->SetTag("Hongdae");

    SetTagName();
}

void MainWindow::SetTagName(){
    ui->tag1_bt->setText(tag[0]->GetTagName());
    ui->tag2_bt->setText(tag[1]->GetTagName());
    ui->tag3_bt->setText(tag[2]->GetTagName());
    ui->tag4_bt->setText(tag[3]->GetTagName());
    ui->tag5_bt->setText(tag[4]->GetTagName());
    ui->tag6_bt->setText(tag[5]->GetTagName());
    ui->tag7_bt->setText(tag[6]->GetTagName());
    ui->tag8_bt->setText(tag[7]->GetTagName());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_all_images_clicked()
{
    AllImage allImage;
    allImage.exec();
}

void MainWindow::on_tag_filter_clicked()
{
    Filter filter;
    QString str[8];

    for(int i=0;i<8;i++){
        if(tag[i]->GetIsTag())
            str[i]=tag[i]->GetTagName();
        else
            str[i]="no tag";
    }
    filter.SetFilter(str);

    filter.exec();

    QString * copy = filter.GetFilter();

    for(int i=0;i<8;i++){
        if(copy[i]=="")
            tag[i]->DeleteTag();
        else if(copy[i]!="no tag")
            if(str[i]!=copy[i])
                tag[i]->SetTag(copy[i]);
    }

    SetTagName();
}

void MainWindow::on_tag1_bt_clicked()
{
    if(tag[0]->GetIsTag()){
        TagImage tagImage;

        tagImage.SetTag(tag[0]->GetTagName());
        tagImage.SetLabel();

        tagImage.exec();
    }
}

void MainWindow::on_tag2_bt_clicked()
{
    if(tag[1]->GetIsTag()){
        TagImage tagImage;

        tagImage.SetTag(tag[1]->GetTagName());
        tagImage.SetLabel();

        tagImage.exec();
    }
}

void MainWindow::on_tag3_bt_clicked()
{
    if(tag[2]->GetIsTag()){
        TagImage tagImage;

        tagImage.SetTag(tag[2]->GetTagName());
        tagImage.SetLabel();

        tagImage.exec();
    }
}

void MainWindow::on_tag4_bt_clicked()
{
    if(tag[3]->GetIsTag()){
        TagImage tagImage;

        tagImage.SetTag(tag[3]->GetTagName());
        tagImage.SetLabel();

        tagImage.exec();
    }
}

void MainWindow::on_tag5_bt_clicked()
{
    if(tag[4]->GetIsTag()){
        TagImage tagImage;

        tagImage.SetTag(tag[4]->GetTagName());
        tagImage.SetLabel();

        tagImage.exec();
    }
}

void MainWindow::on_tag6_bt_clicked()
{
    if(tag[5]->GetIsTag()){
        TagImage tagImage;

        tagImage.SetTag(tag[5]->GetTagName());
        tagImage.SetLabel();

        tagImage.exec();
    }
}

void MainWindow::on_tag7_bt_clicked()
{
    if(tag[6]->GetIsTag()){
        TagImage tagImage;

        tagImage.SetTag(tag[6]->GetTagName());
        tagImage.SetLabel();

        tagImage.exec();
    }
}

void MainWindow::on_tag8_bt_clicked()
{
    if(tag[7]->GetIsTag()){
        TagImage tagImage;

        tagImage.SetTag(tag[7]->GetTagName());
        tagImage.SetLabel();

        tagImage.exec();
    }
}
