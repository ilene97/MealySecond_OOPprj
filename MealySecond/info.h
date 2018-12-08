#ifndef INFO_H
#define INFO_H

#include "food.h"
#include <QDialog>

namespace Ui {
class Info;
}

class Info : public QDialog
{
    Q_OBJECT

public:
    explicit Info(QWidget *parent = nullptr);

    void SetInfo(Food * info, QString category);

    ~Info();

private:
    Ui::Info *ui;
};

#endif // INFO_H
