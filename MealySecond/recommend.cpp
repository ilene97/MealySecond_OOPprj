#include "recommend.h"
#include "dish.h"
#include "dessert.h"
#include "midnightsnack.h"

#define weight1 0.3
#define weight2 0.3
#define weight3 0.4


Recommend::Recommend()
{
    QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("D:/sqlite/test.db");
    mydb.open();

    QSqlQuery* qry = new QSqlQuery(mydb);
    qry->exec("SELECT Year, Month, Day, Tag, Place, Category, DishCategory FROM INFO where Category = 'Dish'");


    //QVector<float> scoreVector;

}

Recommend::Recommend(QString place, int dne, int td, int rating){
    if(td ==1)  totaldays = 1;
    else if(td < 4)  totaldays = 2;
    else totaldays = 3;

    if(dne<3)
        daysNotEat = 0;
    else if(dne<7)
        daysNotEat = 1;
    else if(dne<14)
        daysNotEat = 2;
    else
        daysNotEat = 3;

    this->place = place;
    this->rating = rating;
    this->finalScore = daysNotEat / 3.0 * weight1
            +totaldays / 3.0 * weight2
            +this->rating / 5.0 * weight3;
}

QString Recommend::getPlace(){
    return this->place;
}

int Recommend::getDaysNotEat(){
    return this->daysNotEat;
}

int Recommend::getTotalDays(){
    return this->totaldays;
}

int Recommend::getRating(){
    return this->rating;
}

double Recommend::getFinalScore(){
    return this->finalScore;
}

bool Recommend::operator < (Recommend &a )
{
    return finalScore > a.finalScore;
}

