#ifndef PHOTOOFDAY_H
#define PHOTOOFDAY_H

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
        void setCategory(int categ);

        QString getPlace();
        void setTag(QString tag);
        void setPlace(QString place);
        bool getIsImage();
        QString getImage();
        QDate getDate();
        int getCategory();
        int getDishCategory();
        void setDishCategory(int categ);
        void setCategory();

};

#endif // PHOTOOFDAY_H
