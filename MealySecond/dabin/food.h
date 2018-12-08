#ifndef FOOD_H
#define FOOD_H

#include <QString>
#include <QDate>
#include <QList>

enum{
  DISH, DESSERT, MIDNIGHT_SNACK
};

class Food
{
private:
    QDate today;
    QString tag;
    QString place;
    QString image;
    int category;
    int dishCategory;
    bool isImage;

public:
    Food();
    Food ( QDate &date );
    virtual ~Food();

    void setImage(QString image_name);
    void setTag(QString tag);
    void setPlace(QString place);
    void setCategory(int category);
    void setDishCategory(int dishcategory);

    bool getIsImage();
    QString getImage();
    QDate getDay();
    QString getPlace();
    int getCategory();
    int getDishCategory();
};
#endif // FOOD_H
