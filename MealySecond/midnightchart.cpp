#include "midnightchart.h"


MidnightChart::MidnightChart()
{
    QHorizontalStackedBarSeries *series = new QHorizontalStackedBarSeries();

    QBarSet *midSnack = new QBarSet("ate Midnight Snack");
    QBarSet *noMidSnack = new QBarSet("no Midnight Snack!");

    series->append(midSnack);
    series->append(noMidSnack);

    qdate = qdate.currentDate();
    QString thisYear = QString::number(qdate.year());
    QString thisMonth = QString::number(qdate.month());
    QString lastMonth = QString::number(qdate.month()-1);
    QString lastLastMonth = QString::number(qdate.month()-2);

    int countThis=0, countLast=0, countLastLast =0;

    QStringList monthlist;
    monthlist<<thisYear +"."+ thisMonth<<thisYear +"."+ lastMonth<<thisYear +"."+ lastLastMonth;

    QSqlQuery qry;

    qry.exec("SELECT count(*) FROM INFO where Category = 'MidnightSnack' and Month ='"+thisMonth+"'");
    if(qry.next()){
            countThis = qry.value(0).toInt();
    }
    qry.exec("SELECT count(*) FROM INFO where Category = 'MidnightSnack' and Month ='"+lastMonth+"'");
    if(qry.next()){
            countLast = qry.value(0).toInt();
    }
    qry.exec("SELECT count(*) FROM INFO where Category = 'MidnightSnack' and Month ='"+lastLastMonth+"'");
    if(qry.next()){
            countLastLast = qry.value(0).toInt();
    }

    *midSnack<<countThis<<countLast<<countLastLast;
    QDate lastqdate = qdate.addMonths(-1);
    QDate lastLastqdate = lastqdate.addMonths(-1);

    *noMidSnack<<qdate.daysInMonth()-countThis<<lastqdate.daysInMonth()-countLast<<lastLastqdate.daysInMonth()-countLastLast;


    QChart* chart = new QChart();
    chart->addSeries(series);
    chart->setAnimationOptions(QChart::AllAnimations);

    QBarCategoryAxis* axis = new QBarCategoryAxis();
    axis->append(monthlist);
    chart->createDefaultAxes();
    chart->setAxisY(axis,series);

    QCategoryAxis *axisX = new QCategoryAxis();
    axisX->setStartValue(0);
    axisX->setMax(31);
    axisX->count();
    axisX->setRange(0,31);
    chart->setAxisX(axisX);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
}

QChartView* MidnightChart::getMignightChart()
{
    return chartView;
}

QString MidnightChart::getA()
{
    this->qdate = qdate.currentDate();
    return QString::number(qdate.daysInMonth());
}
