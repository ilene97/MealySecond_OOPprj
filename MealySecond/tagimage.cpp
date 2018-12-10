#include "tagimage.h"
#include "ui_tagimage.h"

TagImage::TagImage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TagImage)
{
    ui->setupUi(this);

    tagdb = QSqlDatabase::addDatabase("QSQLITE");
    tagdb.setDatabaseName("C:/Qt/DB/test.db");
    tagdb.open();
}

void TagImage::SetTag(QString str){
    tagname = str;

    QSqlQuery qry(tagdb);
    qry.exec("SELECT * FROM INFO where Tag = '"+tagname+"'");

    int i=0;
    while(qry.next()){
        QSqlRecord record = qry.record();
        if(record.value(6).toString()!=nullptr){
            int year = record.value(0).toInt();
            int month = record.value(1).toInt();
            int day = record.value(2).toInt();
            QDate date;
            date.setDate(year,month,day);

            QString category = record.value(7).toString();

            tagImage[i] = new Food(date);
            if(category == "Dish"){
                tagImage[i]->setCategory(0);
                tagImage[i]->setDishCategory(record.value(8).toInt());
            }
            else if(category == "Dessert"){
                tagImage[i]->setCategory(1);
                tagImage[i]->setDishCategory(0);
            }
            else{
                tagImage[i]->setCategory(2);
                tagImage[i]->setDishCategory(0);
            }
            tagImage[i]->setTag(record.value(3).toString());
            tagImage[i]->setPlace(record.value(4).toString());
            tagImage[i]->setImage(record.value(6).toString());

            i++;
        }
    }

    for(int j = 11;j>=i;j--)
        tagImage[j]=new Food();

    this->setWindowTitle(str);
}


void TagImage::SetLabel(){

    if(tagImage[0]->getIsImage()){
        ui->label_1->setPixmap(QPixmap(tagImage[0]->getImage()));
        ui->label_1->installEventFilter(this);
    }
    if(tagImage[1]->getIsImage()){
        ui->label_2->setPixmap(QPixmap(tagImage[1]->getImage()));
        ui->label_2->installEventFilter(this);
    }
    if(tagImage[2]->getIsImage()){
        ui->label_3->setPixmap(QPixmap(tagImage[2]->getImage()));
        ui->label_3->installEventFilter(this);
    }
    if(tagImage[3]->getIsImage()){
        ui->label_4->setPixmap(QPixmap(tagImage[3]->getImage()));
        ui->label_4->installEventFilter(this);
    }
    if(tagImage[4]->getIsImage()){
        ui->label_5->setPixmap(QPixmap(tagImage[4]->getImage()));
        ui->label_5->installEventFilter(this);
    }
    if(tagImage[5]->getIsImage()){
        ui->label_6->setPixmap(QPixmap(tagImage[5]->getImage()));
        ui->label_6->installEventFilter(this);
    }
    if(tagImage[6]->getIsImage()){
        ui->label_7->setPixmap(QPixmap(tagImage[6]->getImage()));
        ui->label_7->installEventFilter(this);
    }
    if(tagImage[7]->getIsImage()){
        ui->label_8->setPixmap(QPixmap(tagImage[7]->getImage()));
        ui->label_8->installEventFilter(this);
    }
    if(tagImage[8]->getIsImage()){
        ui->label_9->setPixmap(QPixmap(tagImage[8]->getImage()));
        ui->label_9->installEventFilter(this);
    }
    if(tagImage[9]->getIsImage()){
        ui->label_10->setPixmap(QPixmap(tagImage[9]->getImage()));
        ui->label_10->installEventFilter(this);
    }
    if(tagImage[10]->getIsImage()){
        ui->label_11->setPixmap(QPixmap(tagImage[10]->getImage()));
        ui->label_11->installEventFilter(this);
    }
    if(tagImage[11]->getIsImage()){
        ui->label_12->setPixmap(QPixmap(tagImage[11]->getImage()));
        ui->label_12->installEventFilter(this);
    }
}

bool TagImage::eventFilter(QObject *object, QEvent *event)
{
    if(event->type() == QMouseEvent::MouseButtonPress)
    {
        bool ok;
        QStringList list = object->objectName().split("_");
        int num = list[1].toInt(&ok,10);
        Info info;

        QString category;
        if(tagImage[num-1]->getCategory()==0){
            switch (tagImage[num-1]->getDishCategory()) {
            case 1:
                category="Korean";
                break;
            case 2:
                category="Chinese";
                break;
            case 3:
                category="Japanese";
                break;
            case 4:
                category="Italian";
                break;
            case 5:
                category="ETC";
            }
        }
        else if(tagImage[num-1]->getCategory()==1)
            category="Dessert";
        else if(tagImage[num-1]->getCategory()==2)
            category="MidnightSnack";

        info.SetInfo(tagImage[num-1], category);
        info.exec();
    }
    return QWidget::eventFilter(object,event);
}
TagImage::~TagImage()
{
    delete ui;
}
