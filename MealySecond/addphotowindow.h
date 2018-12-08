#ifndef ADDPHOTOWINDOW_H
#define ADDPHOTOWINDOW_H
namespace Ui {
class AddPhotoWindow;
}

class AddPhotoWindow : public QDialog
{
public:
    AddPhotoWindow();
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



private slots:
    void on_calendarWidget_clicked(const QDate &date);

    void on_addPhoto_clicked();

private:
    Ui::MainWindow *ui;

    QDate today;
    int today_int;
    QMap<QDate,QList<Food>> photosInDay;
};

#endif // ADDPHOTOWINDOW_H
