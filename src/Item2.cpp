#include "../header/Item2.hpp"


/* 1.ITEM MODULE Implementations */
Item::Item() {
    this->ID = 0;
    this->Name = "NaN";
    this->Type = "NaN";
    this->Quantity = 0;
}

int Item::getID() const{
    return this->ID;
}

void Item::setID(int id) {
    this->ID = id;
}

string Item::getName() const{
    return this->Name;
}

void Item::setName(string name) {
    this->Name = name;
}

string Item::getType() const{
    return this->Type;
}

void Item::setType(string type) {
    this->Type = type;
}

int Item::getQuantity() const{
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

/* 2. TOOL ITEM MODULE Implementations */

Non_Tool::Non_Tool() : Item(0,"NaN","Non Tool",0){

}

Non_Tool::Non_Tool(int ID, string name, int Quantity) : Item(ID,name,"Non Tool",Quantity){
    
}

/* 3. TOOL ITEM MODULE Implementations */

Tool::Tool() : Item(0,"NaN","Tool",0){
    this->Durability = 0;
}

Tool::Tool(int ID, string name, int Durability) : Item(ID, name, "Tool", 1){
    this->Durability = Durability;
}

int Tool::getDurability() const{
    return this->Durability;
}

void Tool::setDurability(int durability) {
    this->Durability = durability;
}

void Tool::addDurability(int durability) {
    this->Durability += durability;
}

void Tool::subtractDurability(int durability) {
    this->Durability -= durability;
}

bool Item::operator==(const Item& item) {
    return this->ID == item.ID && this->Name == item.Name && this->Type == item.Type && this-> Quantity == item.Quantity;
}

bool Non_Tool::operator==(const Non_Tool& item){
    bool same = Item::this == item;

bool Tool::operator==(const Tool& item){
    bool same = Item::this == item;
    return same && this->Durability == t.Durability;
}