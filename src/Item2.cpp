#include "../header/Item2.hpp"


/* 1.ITEM MODULE Implementations */
Item::Item() {
    this->ID = 0;
    this->Name = "NaN";
}

Item::Item(int ID, string name){
    this->ID = ID;
    this->Name = name;
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

void Item::setQuantity(int quantity) {
    // No modifiable quantity Exception
}

string Item::getVariant() const {
    // No variant Exception
    return NULL;
}

void Item::setVariant(string Variant) {
    // No variant Exception
}

int Item::getDurability() const {
    // No durability exception
    return 0;
} 

void Item::setDurability(int durability) {
    // No durability Exception
}

void Item::addQuantity(int quantity) {
    // No modifiable quantity Exception
}

void Item::subtractQuantity(int quantity) {
    // No modifiable quantity Exception
}

/* 2. TOOL ITEM MODULE Implementations */

Non_Tool::Non_Tool() : Item(0,"NaN"){
    this->Variant = "-";
};

Non_Tool::Non_Tool(int ID, string name, int Quantity, string Variant) : Item(ID,name){
    this->Quantity = Quantity;
    this->Variant = Variant;
}

Item* Non_Tool::deepCopy() const {
    return new Non_Tool(*this);
}

string Non_Tool::getType() const {
    return "NONTOOL";
}

string Non_Tool::getVariant() const{
    return this->Variant;
}

void Non_Tool::setVariant(string Variant){
    this->Variant = Variant;
}

void Non_Tool::setQuantity(int quantity){
    this->Quantity = quantity;
    // Exception Non_Tool 0 <= Q <= 64
}
void Non_Tool::addQuantity(int quantity){
    this->Quantity += quantity;
    // Exception Non_Tool 0 <= Q <= 64
}
void Non_Tool::subtractQuantity(int quantity){
    this->Quantity -= quantity;
    // Exception Non_Tool 0 <= Q <= 64
}

/* 3. TOOL ITEM MODULE Implementations */

Tool::Tool() : Item(0,"NaN"){
    this->Durability = 0;
}

Tool::Tool(int ID, string name, int Durability) : Item(ID, name){
    this->Durability = Durability;
    // Exception 0 <= D <= 10
}

Item* Tool::deepCopy() const {
    return new Tool(*this);
}

string Tool::getType() const {
    return "TOOL";
}

int Tool::getQuantity() const {
    return 1;
}

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

// 4. Comperator Similarity
bool Item::operator==(const Item& item) {
    return this->ID == item.ID && this->Name == item.Name;
}

bool Non_Tool::operator==(const Non_Tool& item){
    return Item::operator==(item) && this->Quantity == item.Quantity && this->Variant == item.Variant;
}
bool Tool::operator==(const Tool& item){
    return Item::operator==(item) && this->Durability == item.Durability;
}