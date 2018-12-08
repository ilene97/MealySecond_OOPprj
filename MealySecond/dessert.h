#ifndef DESSERT_H
#define DESSERT_H

#include "food.h"


class Dessert : public Food
{
public:
    static int count;
    Dessert(QDate date);
    //~Dessert();
    int getCategory();
};

#endif // DESSERT_H
