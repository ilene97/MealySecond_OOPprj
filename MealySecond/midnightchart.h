#ifndef MIDNIGHTCHART_H
#define MIDNIGHTCHART_H

#include <QChartView>
#include <QHorizontalStackedBarSeries>
#include <QBarSeries>
#include <QBarSet>
#include <QChart>
#include <QtCharts/QLegend>
#include <QBarCategoryAxis>
#include <QHorizontalBarSeries>
#include <QLineSeries>
#include <QCategoryAxis>
#include <QtSql>
#include <QSqlQuery>
#include <QDebug>
#include <QFileInfo>
#include <QDate>

QT_CHARTS_USE_NAMESPACE

class MidnightChart
{
private:
    QDate qdate;
    QChartView *chartView;

public:
    MidnightChart();
    QChartView* getMignightChart();
    QString getA();
};

#endif // MIDNIGHTCHART_H
