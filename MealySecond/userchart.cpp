#include "userchart.h"

UserChart::UserChart()
{
    mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("C:/Qt/DB/test.db");
    mydb.open();

    int count1=0, count2=0, count3=0, count4=0, count5=0;
    QDate qdate = qdate.currentDate();

    QString thisMonth = QString::number(qdate.month());

    QSqlQuery qry;

    qry.exec("SELECT count(*) FROM INFO where DishCategory = 1 and Month ='"+thisMonth+"'");
    if(qry.next()){
            count1 = qry.value(0).toInt();
    }
    qry.exec("SELECT count(*) FROM INFO where DishCategory = 2");
    if(qry.next()){
            count2 = qry.value(0).toInt();
    }
    qry.exec("SELECT count(*) FROM INFO where DishCategory = 3 AND Month ='"+thisMonth+"'");
    if(qry.next()){
            count3 = qry.value(0).toInt();
    }
    qry.exec("SELECT count(*) FROM INFO where DishCategory = 4 AND Month ='"+thisMonth+"'");
    if(qry.next()){
            count4 = qry.value(0).toInt();
    }
    qry.exec("SELECT count(*) FROM INFO where DishCategory = 5 AND Month ='"+thisMonth+"'");
    if(qry.next()){
            count5 = qry.value(0).toInt();
    }

    QPieSeries *series = new QPieSeries();
    series->append("Korean",count1);
    series->append("Japanese",count2);
    series->append("Chinese",count3);
    series->append("Western",count4);
    series->append("Else",count5);

    QPieSlice *slice0 = series->slices().at(0);
    slice0->setLabelVisible();

    QPieSlice *slice1 = series->slices().at(1);
    slice1->setLabelVisible();

    QPieSlice *slice2 = series->slices().at(2);
    slice2->setLabelVisible();

    QPieSlice *slice3 = series->slices().at(3);
    slice3->setLabelVisible();

    QPieSlice *slice4 = series->slices().at(4);
    slice4->setLabelVisible();

    QChart *chart = new QChart();

    chart->addSeries(series);
    chart->setAnimationOptions(QChart::AllAnimations);

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
}

QChartView * UserChart::getChart(){
    return chartView;
}

double UserChart::getPercentage(int count, int totalCount){
    return count / totalCount;
}
