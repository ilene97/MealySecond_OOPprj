#include "addimagewindow.h"
#include "ui_addimagewindow.h"

AddImageWindow::AddImageWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddImageWindow)
{
    ui->setupUi(this);
}

AddImageWindow::~AddImageWindow()
{
    delete ui;
}

void AddImageWindow::on_cancelButton_clicked()
{
    ui->placeEdit->clear();
    ui->tagEdit->clear();
    hide();
}

void AddImageWindow::on_pushButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Choose"),"",tr("Images (*.png *.jpg *.jpeg *.bmp *.gif)"));

       if(QString::compare(filename, QString())!=0){
           QImage image;
           bool vaild = image.load(filename);

           if(vaild){
               image = image.scaledToWidth(ui->imageView->width(), Qt::SmoothTransformation);
               ui->imageView->setPixmap(QPixmap::fromImage(image));
           }
           else{
               //Error handing
           }
       }

       image = filename;
}

void AddImageWindow::on_OKButton_clicked()
{
    tag = ui->tagEdit->text();
    place = ui->placeEdit->text();
    //ui->test1->setText(tag);
    //ui->test2->setText(place);

    Food *photooftoday = new Food(date);
    photooftoday->AddImage(image);
    photooftoday->setPlace(place);
    photooftoday->setTag(tag);

    thisfood = photooftoday;

    hide();
}


//Getter&Setter
void AddImageWindow::setDate(QDate date){
    this->date = date;
    ui->dateViewer->setText(this->date.toString("yyyy.MM.dd"));
}
QString AddImageWindow::getTag(){return tag;}
QString AddImageWindow::getPlace(){return place;}
QString AddImageWindow::getImageLocation(){return image;}
Food AddImageWindow::getThisFood(){return *thisfood;}
