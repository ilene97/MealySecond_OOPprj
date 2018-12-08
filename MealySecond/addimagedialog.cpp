 #include "addimagedialog.h"
#include "ui_addimagedialog.h"
#include "QFileDialog"

#include "mainwindow.h"
#include "food.h"
#include <QMouseEvent>

AddImageDialog::AddImageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddImageDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Add Photo");

    mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("C:/Qt/DB/test.db");
    mydb.open();

    if ( !mydb.open() )
    {
        qDebug() << "Failed to connect to database: " + mydb.lastError().text();
    }

    qDebug() << "Successfully connected to database...";

    ui->star1->installEventFilter(this);
    ui->star2->installEventFilter(this);
    ui->star3->installEventFilter(this);
    ui->star4->installEventFilter(this);
    ui->star5->installEventFilter(this);

    ui->pushButton->setStyleSheet("border-image:url(C:/Users/ilene/Documents/Visual Studio 2017/Qt Projects/CalendarFunction/add.png)");
    ui->OKButton->setStyleSheet("border-image:url(C:/Users/ilene/Documents/Visual Studio 2017/Qt Projects/CalendarFunction/ok.png)");

        for(int i=0;i<5;i++)
            isStar[i]=false;
}

AddImageDialog::~AddImageDialog()
{
    delete ui;
}
/*
void AddImageDialog::on_cancelButton_clicked()
{
    ui->placeEdit->clear();
    ui->tagEdit->clear();
    this->hide();
}
*/
void AddImageDialog::on_pushButton_clicked()
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

void AddImageDialog::on_OKButton_clicked()
{
    tag = ui->tagEdit->text();
    place = ui->placeEdit->text();



    Food *photooftoday;
    int kind = ui->comboBox->currentIndex();
    QString category;
    int dishCategory = 0;
    switch (kind) {
        case DISH :
            photooftoday = new Dish(date);
            photooftoday->setDishCategory(ui->comboBox->currentIndex());
            dishCategory = (ui->comboBox->currentIndex())+1;
            category = "Dish";
            break;
        case DESSERT :
            photooftoday = new Dessert(date);
            category = "Dessert";
            break;
        case MIDNIGHT_SNACK :
            photooftoday = new MidnightSnack(date);
            category = "MidnightSnack";
            break;
        default:
            photooftoday = new Food(date); //need modify
            break;
    }

    photooftoday->setImage(image);
    photooftoday->setPlace(place);
    photooftoday->setTag(tag);

    QSqlQuery query(mydb);
    query.prepare("INSERT INTO INFO (Year, Month, Day, Tag, Place, Rating, Image, Category, DishCategory) "
                  "VALUES(:Year, :Month, :Day, :Tag, :Place, :Rating, :Image, :Category, :DishCategory)");

    query.bindValue(":Year",2018);
    query.bindValue(":Year",date.toString("yyyy").toInt());
    query.bindValue(":Month",date.toString("MM").toInt());
    query.bindValue(":Day",date.toString("dd").toInt());
    query.bindValue(":Tag",tag);

    query.bindValue(":Place", place);
    query.bindValue(":Rating",getRate());
    query.bindValue(":Image",image);
    query.bindValue(":Category",category);
    query.bindValue(":DishCategory",dishCategory);

    query.exec();

    thisfood = photooftoday;

    hide();
}

int AddImageDialog::getRate(){
    int rate=0;
    for(int i=0;i<5;i++)
    {
        if(isStar[i]==true)
            rate++;
    }
    return rate;
}
bool AddImageDialog::eventFilter(QObject *object, QEvent *event)
{
    if(event->type() == QMouseEvent::MouseButtonPress)
    {
        QStringList qsplit = object->objectName().split("r");
        int j = qsplit[1].toInt();

        QImage star("C:/Users/ilene/Documents/Visual Studio 2017/Qt Projects/CalendarFunction/fullstar.png");
        QImage blank("C:/Users/ilene/Documents/Visual Studio 2017/Qt Projects/CalendarFunction/emptystar.png");

        if(isStar[j-1]==true){
            for(int i = j-1;i<5;i++)
                isStar[i]=false;
        }
        else{
            for(int i = 0;i<j;i++)
                isStar[i]=true;
        }

        if(isStar[0]==true)
            ui->star1->setPixmap(QPixmap::fromImage(star));
        else
            ui->star1->setPixmap(QPixmap::fromImage(blank));

        if(isStar[1]==true)
            ui->star2->setPixmap(QPixmap::fromImage(star));
        else
            ui->star2->setPixmap(QPixmap::fromImage(blank));

        if(isStar[2]==true)
            ui->star3->setPixmap(QPixmap::fromImage(star));
        else
            ui->star3->setPixmap(QPixmap::fromImage(blank));

        if(isStar[3]==true)
            ui->star4->setPixmap(QPixmap::fromImage(star));
        else
            ui->star4->setPixmap(QPixmap::fromImage(blank));

        if(isStar[4]==true)
            ui->star5->setPixmap(QPixmap::fromImage(star));
        else
            ui->star5->setPixmap(QPixmap::fromImage(blank));

    }
    return QWidget::eventFilter(object,event);
}

//Getter&Setter
void AddImageDialog::setDate(QDate date){
    this->date = date;
    ui->dateViewer->setText(this->date.toString("yyyy.MM.dd"));
}
QString AddImageDialog::getTag(){return tag;}
QString AddImageDialog::getPlace(){return place;}
QString AddImageDialog::getImageLocation(){return image;}
Food* AddImageDialog::getThisFood(){return thisfood;}
