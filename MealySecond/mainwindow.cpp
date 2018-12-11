#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QVBoxLayout"
#include "filter.h"
#include "allimage.h"
#include "tagimage.h"
#include "userchart.h"
#include "midnightchart.h"
#include "QVector"
#include "dish.h"
#include "dessert.h"
#include "midnightsnack.h"
#include "food.h"

#include <QFileDialog>
#include <QList>
#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->show();

    mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("C:/Qt/DB/test.db");
    mydb.open();

    QSqlQuery alldataquery(mydb);
    alldataquery.exec("SELECT * FROM INFO");

        while(alldataquery.next()){

            QSqlRecord thisRecord = alldataquery.record();
            int year = thisRecord.value(0).toInt();
            int month = thisRecord.value(1).toInt();
            int day = thisRecord.value(2).toInt();
            QDate date; date.setDate(year,month,day);

            QString category = thisRecord.value(7).toString();
            Food *food;
            if(category=="Dish"){
                food = new Dish(date);
                food->setDishCategory(thisRecord.value(8).toInt());
            }
            else if(category==("Dessert"))
                food = new Dessert(date);
            else
                food = new MidnightSnack(date);

            food->setImage(thisRecord.value(6).toString());
            qDebug()<<thisRecord.value(6).toString();

            food->setTag(thisRecord.value(3).toString());
            food->setPlace(thisRecord.value(4).toString());

            addFoodinMap(date, food);
        }

        for(int i=0;i<8;i++){
            tag[i] = new Tag();
        }

        //initial value
        tag[0]->SetTag("Sangdo");
        tag[1]->SetTag("HeukSeok");
        tag[2]->SetTag("GangNam");
        tag[3]->SetTag("Bucheon");

        SetTagName();

        ui->addPhoto->setStyleSheet("border-image:url(C:/Users/ilene/Documents/Visual Studio 2017/Qt Projects/CalendarFunction/addbutton.png)");
        ui->logo->setStyleSheet("border-image:url(C:/Users/ilene/Documents/Visual Studio 2017/Qt Projects/CalendarFunction/mealysecond.png)");
        ui->tag_filter->setStyleSheet("border-image:url(C:/Users/ilene/Documents/Visual Studio 2017/Qt Projects/CalendarFunction/tagfilter.png)");
        ui->all_images->setStyleSheet("border-image:url(C:/Users/ilene/Documents/Visual Studio 2017/Qt Projects/CalendarFunction/viewall.png)");

        ui->mealButton->setStyleSheet("border-image:url(C:/Users/ilene/Documents/Visual Studio 2017/Qt Projects/CalendarFunction/mealbutton.png)");
        ui->dessertButton->setStyleSheet("border-image:url(C:/Users/ilene/Documents/Visual Studio 2017/Qt Projects/CalendarFunction/dessertbutton.png)");
        ui->midsnackButton->setStyleSheet("border-image:url(C:/Users/ilene/Documents/Visual Studio 2017/Qt Projects/CalendarFunction/snackbutton.png)");
        ui->label_4->setStyleSheet("border-image:url(C:/Users/ilene/Documents/Visual Studio 2017/Qt Projects/CalendarFunction/recommendment.png)");

        QVBoxLayout *vbox = new QVBoxLayout();
            ui->groupBox->setLayout(vbox);
            QVBoxLayout *vbox2 = new QVBoxLayout();
            ui->groupBox_3->setLayout(vbox2);

            userchart = new UserChart();
            vbox->addWidget(userchart->getChart());

            midnightChart = new MidnightChart();
            vbox2->addWidget(midnightChart->getMignightChart());

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_calendarWidget_clicked(const QDate &date){

    QWidget * placeHolder = new QWidget();
    QVBoxLayout *vbox = new QVBoxLayout(placeHolder);

    ui->imageArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->imageArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->imageArea->setWidget(placeHolder);

    today = date;

    ui->dateView->setText(date.toString("dd"));
    ui->yearView->setText(date.toString("yyyy"));
    ui->monthView->setText(date.toString("MM"));
/*
    ui->dishCount->setText(QString::number(Dish::count));
    ui->dessertCount->setText(QString::number(Dessert::count));
    ui->snackCount->setText(QString::number(MidnightSnack::count));
    ui->imageCount->clear();
*/
    if( !photosInDay.empty() && photosInDay.find(date) != photosInDay.end()
             &&photosInDay.find(date).value().front().getIsImage()){

        int imageCount = photosInDay.find(date).value().count();

        for(int i=0; i<=imageCount/3; i++){
            QHBoxLayout *picture = new QHBoxLayout();

            picture->setAlignment(Qt::AlignLeft);

            int num = 3;
            if(i==(imageCount/3)) num = imageCount % 3;

            QList<Food>::iterator p = photosInDay.find(date).value().begin();
            for(; p != photosInDay.find(date).value().end(); p++){


                //qDebug()<<num;
                if(num<1) break;

                QLabel *label = new QLabel();
                QImage image(p->getImage());

                //qDebug()<<p->image_list.front();
                label->setPixmap(QPixmap::fromImage(image));
                label->setFixedHeight(180);
                label->setFixedWidth(180);
                label->setScaledContents(true);
                picture->addWidget(label);
                num--;
            }
            vbox->addLayout(picture);
            vbox->addSpacing(20);
        }
        //ui->imageCount->setText(QString::number(imageCount));
    }

}

void MainWindow::on_addPhoto_clicked()
{
    AddImageDialog *addImageDialog = new AddImageDialog(this);
    connect(this, SIGNAL(sendDate(QDate)),addImageDialog,SLOT(setDate(QDate)));
    emit sendDate(today);

    addImageDialog->exec();
    addFoodinMap(today, addImageDialog->getThisFood());

}

void MainWindow::addFoodinMap(QDate date, Food *food){
    if(photosInDay.find(date) == photosInDay.end()){
        QList<Food> list;
        photosInDay.insert(date, list);
    }
    photosInDay.find(date).value().push_back(*food);
}


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


void MainWindow::on_mealButton_clicked()
{
    RecommendFood("Dish");
}

void MainWindow::on_dessertButton_clicked()
{
    RecommendFood("Dessert");
}

void MainWindow::on_midsnackButton_clicked()
{
    RecommendFood("MidnightSnack");
}


void MainWindow::RecommendFood(QString category){

    QVector<Food> vecFood;
    QVector<Food> tempvecFood;
    QVector<Recommend> vecFoodRecommend;
    int tempIndex[30];
    QDate curDate = curDate.currentDate();
    QDate date;
    int year, month, day,rating;
    QString tag, place;
    QSqlQuery *qry = new QSqlQuery(mydb);

    int count =0;
    int i=0;
    int tempMax=0;

    //*********************getting records with "2 or more times" (to calculate daysNotEat)****************************************

    qry->exec("select Year, Month, Day, Tag, Place, Rating from INFO where Category = '"+category+"' and Place in (select Place from INFO group by Place having count(*) > 1) order by Place");
    while(qry->next()){
        QSqlRecord mrecord = qry->record();

        year = mrecord.value(0).toInt();
        month = mrecord.value(1).toInt();
        day = mrecord.value(2).toInt();
        date.setDate(year,month,day);

        tag = mrecord.value(3).toString();
        place = mrecord.value(4).toString();
        rating = mrecord.value(5).toInt();

        Food food = Food(date);
        food.setPlace(place);
        food.setTag(tag);
        food.setRating(rating);
        tempvecFood.push_back(food);
    }

    QVector<Food>::iterator pos;

    QDate compareDate = tempvecFood.begin()->getDate();

    for(pos = tempvecFood.begin();pos!=tempvecFood.end();++pos){
        QDate tempDate;
        int temp;

        if((pos+1) == tempvecFood.end()){
            if(compareDate < pos->getDate()){
            tempIndex[i] = count;
            }
            else{
            tempIndex[i] = tempMax;
            }
            vecFood.push_back(tempvecFood[tempIndex[i]]);
        }
        else if(pos->getPlace() != (pos+1)->getPlace()){
            tempIndex[i] = tempMax++;

            compareDate = (pos+1)->getDate();
            vecFood.push_back(tempvecFood[tempIndex[i++]]);
        }
        else{
            if((pos)->getDate().daysTo((pos+1)->getDate())>0){
                tempDate = (pos+1)->getDate();
                temp =count+1;
            }
            else{
                tempDate = pos->getDate();
                temp = count;
            }

            if(compareDate<tempDate){
                tempMax = temp;
                compareDate = tempDate;
            }
       }
        count++;
    }
    qDebug()<<"recommend befo";

    QVector<Food>::iterator iter;
    int num=0;
    for (iter=vecFood.begin();iter!=vecFood.end();iter++) {
        int temp = tempIndex[0] + 1;
        if(num!=0)
            temp = tempIndex[num]-tempIndex[num-1];

        Recommend recFood(iter->getPlace(), date.daysTo(iter->getDate()),temp,iter->getRating());
        vecFoodRecommend.push_back(recFood);
    }

    //*********************getting 'Dessert' records without overlap (only 1 time)****************************************
    qry->exec("SELECT Year, Month, Day, Tag, Place, Rating from INFO where Category = '"+category+"' group by Place having count(*) = 1");
    while(qry->next()){
            QSqlRecord mrecord = qry->record();
            year = mrecord.value(0).toInt();
            month = mrecord.value(1).toInt();
            day = mrecord.value(2).toInt();

            date.setDate(year,month,day);
            tag = mrecord.value(3).toString();
            place = mrecord.value(4).toString();
            rating = mrecord.value(5).toInt();

            Food food= Food(date);
            food.setPlace(place);
            food.setTag(tag);
            food.setRating(rating);
            vecFood.push_back(food);

            Recommend recFood(place, date.daysTo(curDate) ,1,rating);
            vecFoodRecommend.push_back(recFood);          //final result score calculation from vecDesRecommend
    }

    std::sort(vecFoodRecommend.begin(), vecFoodRecommend.end());

    QVector<Recommend>::iterator it;
    for(it = vecFoodRecommend.begin();it!=vecFoodRecommend.end();it++)
        qDebug()<<it->getPlace()<<" "<<QString::number(it->getFinalScore());

    QString finalString = vecFoodRecommend.first().getPlace();
    ui->label_2->setText(finalString);

}
