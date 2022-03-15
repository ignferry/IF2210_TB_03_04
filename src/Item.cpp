#include "../header/Item.hpp"

Item::Item() {
    this->ID = 0;
    this->Name = "NaN";
    this->Type = "NaN";
    this->Quantity = 0;
    this->Durability = 0;
}

int Item::getID() {
    return this->ID;
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

void Item::setQuantity(int quantity) {
    this->Quantity = quantity;
}

void Item::addQuantity(int quantity) {
    this->Quantity += quantity;
}

void Item::subtractQuantity(int quantity) {
    this->Quantity -= quantity;
}

int Item::getDurability() {
    return this->Durability;
}

void Item::setDurability(int durability) {
    this->Durability = durability;
}

void Item::addDurability(int durability) {
    this->Durability += durability;
}

void Item::subtractDurability(int durability) {
    this->Durability -= durability;
}