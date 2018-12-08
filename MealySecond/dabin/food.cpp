#include "food.h"

Food::Food():isImage(false){
}

Food::Food(QDate &date)
    :today(date), isImage(false)
{}

Food::~Food(){
    //qDeleteAll(image_list.begin(), image_list.end());
}

void Food::setImage(QString image_name){
   image = image_name;
   isImage = true;
}
bool Food::getIsImage(){
    return isImage;
}

QString Food::getImage(){
    return image;
}

QDate Food::getDay(){
    return today;
}

QString Food::getPlace(){
    return place;
}

void Food::setTag(QString tag){
    this->tag = tag;
}

void Food::setPlace(QString place){
    this->place = place;
}

void Food::setCategory(int category){
    this->category = category;
}

void Food::setDishCategory(int dishcategory){
    dishCategory = dishcategory;
}

int Food::getCategory(){
    return category;
}

int Food::getDishCategory(){
    return dishCategory;
}
