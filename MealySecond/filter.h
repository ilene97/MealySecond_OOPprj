#ifndef FILTER_H
#define FILTER_H

#include <QDialog>

namespace Ui {
class Filter;
}

class Filter : public QDialog
{
    Q_OBJECT

public:
    explicit Filter(QWidget *parent = nullptr);
    void SetFilter(QString * filt);
    QString * GetFilter();
    ~Filter();

private slots:
    void on_setting_clicked();

private:
    QString filter[8];
    Ui::Filter *ui;
};

#endif // FILTER_H
