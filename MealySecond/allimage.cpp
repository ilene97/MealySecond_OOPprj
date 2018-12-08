#include "allimage.h"
#include "ui_allimage.h"

AllImage::AllImage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AllImage)
{
    ui->setupUi(this);

    allimagedb = QSqlDatabase::addDatabase("QSQLITE");
    allimagedb.setDatabaseName("C:/Qt/DB/test.db");

    allimagedb.open();

    QSqlQuery month = QSqlQuery(allimagedb);
    month.exec("SELECT Month FROM INFO group by Month");

    QWidget * placeHolder = new QWidget();
    QVBoxLayout *vbox = new QVBoxLayout(placeHolder);

    ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->scrollArea->setWidget(placeHolder);

    while(month.next()){
        QSqlRecord mrecord = month.record();
        QString curmonth = mrecord.value(0).toString();
        QVBoxLayout * box= new QVBoxLayout();
        QLabel * date = new QLabel();

        date->setStyleSheet ( "color : #8f563b");
        date->setFont(QFont("Arial", 20));
        date->setFixedHeight(50);
        date->setText("2018/"+curmonth);
        box->addSpacing(10);
        box->addWidget(date);

        QSqlQuery simage;
        simage.exec("SELECT * FROM INFO WHERE Month = '"+curmonth+"'");

        int imagesize = 0;
        if(simage.last())
        {
            imagesize =  simage.at()+1;
            simage.first();
        }

        for(int i=0;i<=imagesize/4;i++){
            QHBoxLayout *picture = new QHBoxLayout();
            picture->setAlignment(Qt::AlignLeft);

            int num = 4;
            if(i==(imagesize/4))
                num = (imagesize%4);

            do{
                if(num<1)
                    break;
                QLabel * label = new QLabel();
                QSqlRecord irecord = simage.record();
                QImage image(irecord.value(6).toString());

                label->setPixmap(QPixmap::fromImage(image));
                label->setFixedHeight(200);
                label->setFixedWidth(187);
                label->setScaledContents(true);
                picture->addWidget(label);
                num--;
            } while (simage.next());
            box->addLayout(picture);
        }
        vbox->addLayout(box);
        vbox->addSpacing(20);
    }
}

AllImage::~AllImage()
{
    delete ui;
}
