#include "midnightsnack.h"

MidnightSnack::MidnightSnack(QDate date) :
    Food(date)
{
    this->count++;
}

int MidnightSnack::getCategory(){
    return MIDNIGHT_SNACK;
}

int MidnightSnack::count=0;
