#include "../header/Item.hpp"

Item::Item() {
    this->ID = 0;
    this->Name = "NaN";
    this->Type = "NaN";
    this->Quantity = 0;
}

int Item::getID() {
    return this->ID;
}

int Item::getID(string name) {
    
}

void Item::setID(int id) {
    this->ID = id;
}

string Item::getName() {
    return this->Name;
}

void Item::setName(string name) {
    this->Name = name;
}

string Item::getType() {
    return this->Type;
}

void Item::setType(string type) {
    this->Type = type;
}

int Item::getQuantity() {
    return this->Quantity;
}

void Item::addQuantity(int quantity) {
    this->Quantity += quantity;
}

void Item::subtractQuantity(int quantity) {
    this->Quantity -= quantity;
}