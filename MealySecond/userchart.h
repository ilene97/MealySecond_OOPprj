#ifndef USERCHART_H
#define USERCHART_H



#include <QChart>
#include <QChartView>
#include <QPainter>
#include <QPieSeries>
#include <QPieSlice>
#include <QtSql>
#include <QSqlQuery>
#include <QDebug>
#include <QFileInfo>
#include <QDate>

QT_CHARTS_USE_NAMESPACE

class UserChart
{
private:
    QChartView * chartView;

public:
    UserChart();
    QChartView * getChart();
    QSqlDatabase mydb;
    double getPercentage(int count, int totalCount);
};

#endif // USERCHART_H
