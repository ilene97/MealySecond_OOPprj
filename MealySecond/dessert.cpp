#include "dessert.h"

Dessert::Dessert(QDate date) :
    Food(date)
{
    this->count++;
}

int Dessert::getCategory(){
    return DESSERT;
}

int Dessert::count = 0;
