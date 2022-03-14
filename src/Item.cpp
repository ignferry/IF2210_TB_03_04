#include "../header/Item.hpp"

Item::Item() {
    this->ID = 0;
    this->Name = "NaN";
    this->Quantity = 0;
}

int Item::getID() {
    return this->ID;
}

string Item::getName() {
    return this->Name;
}

int Item::getQuantity() {
    return this->Quantity;
}

void Item::addQuantity(int quantity) {
    this->Quantity += quantity;
}