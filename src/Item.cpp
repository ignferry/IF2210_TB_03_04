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

bool Item::operator==(const Item& item) {
    return this->ID == item.ID;
}