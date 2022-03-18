#include "../header/Item2.hpp"


/* 1.ITEM MODULE Implementations */
Item::Item() {
    this->ID = 0;
    this->Name = "NaN";
    this->Type = "NaN";
    this->Quantity = 0;
}

Item::Item(int ID, string name, string Type, int Quantity){
    this->ID = ID;
    this->Name = name;
    this->Type = Type;
    this->Quantity = Quantity;
}

Item::~Item(){};

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
    // Exception tipe hanya 2
}

int Item::getQuantity() const{
    return this->Quantity;
}

void Item::setQuantity(int quantity) {
    this->Quantity = quantity;
    // No Exception
}

void Item::addQuantity(int quantity) {
    this->Quantity += quantity;
    // No Exception
}

void Item::subtractQuantity(int quantity) {
    this->Quantity -= quantity;
    // No Exception
}

/* 2. TOOL ITEM MODULE Implementations */

Non_Tool::Non_Tool() : Item(0,"NaN","Non Tool",0){
    this->Variant = "-";
};

Non_Tool::Non_Tool(int ID, string name, int Quantity, string Variant) : Item(ID,name,"Non Tool",Quantity){
    this->Variant = Variant;
}

Non_Tool::~Non_Tool(){};

string Non_Tool::getVariant() const{
    return this->Variant;
}

void Non_Tool::setVariant(string Variant){
    this->Variant = Variant;
}

void Non_Tool::setQuantity(int quantity){
    this->Item::setQuantity(quantity);
    // Exception Non_Tool 0 <= Q <= 64
}
void Non_Tool::addQuantity(int quantity){
    this->Item::addQuantity(quantity);
    // Exception Non_Tool 0 <= Q <= 64
}
void Non_Tool::subtractQuantity(int quantity){
    this->Item::subtractQuantity(quantity);
    // Exception Non_Tool 0 <= Q <= 64
}

/* 3. TOOL ITEM MODULE Implementations */

Tool::Tool() : Item(0,"NaN","Tool",0){
    this->Durability = 0;
}

Tool::Tool(int ID, string name, int Durability) : Item(ID, name, "Tool", 1){
    this->Durability = Durability;
    // Exception 0 <= D <= 10
}

Tool::~Tool(){};

int Tool::getDurability() const{
    return this->Durability;
}

void Tool::setDurability(int durability) {
    this->Durability = durability;
    // Exception 0 <= D <= 10
}

void Tool::addDurability(int durability) {
    this->Durability += durability;
    // Exception 0 <= D <= 10
}

void Tool::subtractDurability(int durability) {
    this->Durability -= durability;
    // Exception 0 <= D <= 10
}

void Tool::setQuantity(int quantity){
    this->Item::setQuantity(quantity);
    // Exception Non_Tool 0 <= Q <= 1
}
void Tool::addQuantity(int quantity){
    this->Item::addQuantity(quantity);
    // Exception Non_Tool 0 <= Q <= 1
}
void Tool::subtractQuantity(int quantity){
    this->Item::subtractQuantity(quantity);
    // Exception Non_Tool 0 <= Q <= 1
}


// 4. Comperator Similarity
bool Item::operator==(const Item& item) {
    return this->ID == item.ID && this->Name == item.Name && this->Type == item.Type && this-> Quantity == item.Quantity;
}

bool Non_Tool::operator==(const Non_Tool& item){
    return Item::operator==(item) && this->Variant == item.Variant;
}
bool Tool::operator==(const Tool& item){
    return Item::operator==(item) && this->Durability == item.Durability;
}