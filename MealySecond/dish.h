#ifndef DISH_H
#define DISH_H

#include <QDate>
#include "food.h"

enum{
    KOREAN, CHINESE, JAPANESE, ITALIAN, ETC
};

class Dish : public Food
{
private:
    int dishCategory;
public:
    static int count;
    Dish(QDate date);
    int getCategory();
    int getDishCategory();
    void setDishCategory(int categ);

};

#endif // DISH_H
