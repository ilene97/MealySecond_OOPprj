#ifndef MIDNIGHTSNACK_H
#define MIDNIGHTSNACK_H

#include "food.h"

class MidnightSnack : public Food
{
public:
    static int count;
    MidnightSnack(QDate date);
    int getCategory();
};

#endif // MIDNIGHTSNACK_H
