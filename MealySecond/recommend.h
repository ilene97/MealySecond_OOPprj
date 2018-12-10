#ifndef RECOMMEND_H
#define RECOMMEND_H
#include "dessert.h"
#include <QtSql>
#include <QSqlQuery>
#include <QDebug>
#include <QFileInfo>
#include <QVector>

class Recommend
{
private:
//QSqlDatabase mydb;
//  QSqlQueryModel *model;
    QString place;
    int daysNotEat; //1-3
    int totaldays;  //1-3
    int rating;     //1-5
    double finalScore;
    
public:
    Recommend();
    Recommend(QString place, int daysNotEat, int totaldays, int rating);

    QString getPlace();
    int getDaysNotEat();
    int getTotalDays();
    int getRating();
    double getFinalScore();

    bool operator< (Recommend &a );


    //template<typename T>
    //int getDaysNotEat(T category);
    //template<typename T>
    //int getTotalDays(T category);
    //template<typename T>
    //int getRate(T category);
        
};

#endif // RECOMMEND_H
