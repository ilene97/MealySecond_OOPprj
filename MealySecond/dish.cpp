#include "dish.h"

Dish::Dish(QDate date) :
    Food(date)
{
    this->count++;
}
int Dish::count=0;

int Dish::getCategory(){
    return DISH;
}

int Dish::getDishCategory(){
    return dishCategory;
}

void Dish::setDishCategory(int categ){
    this->dishCategory = categ;
}
