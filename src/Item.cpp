#include "../header/Item.hpp"

/* 1.ITEM MODULE Implementations */
Item::Item()
{
    this->ID = 0;
    this->Name = "NaN";
}

Item::Item(int ID, string name)
{
    this->ID = ID;
    this->Name = name;
}

Item::~Item(){};

int Item::getID() const
{
    return this->ID;
}

void Item::setID(int id)
{
    this->ID = id;
}

string Item::getName() const
{
    return this->Name;
}

void Item::setName(string name)
{
    this->Name = name;
}

void Item::setQuantity(int quantity)
{
    throw Item_No_QuantityException();
}

string Item::getVariant() const
{
    // throw Item_No_VariantException();
    return NULL;
}

void Item::setVariant(string Variant)
{
    throw Item_No_VariantException();
}

int Item::getDurability() const
{
    // throw Item_No_DurabilityException();
    return 0;
}

void Item::setDurability(int durability)
{
    throw Item_No_DurabilityException();
}

void Item::addQuantity(int quantity)
{
    throw Item_No_QuantityException();
}

void Item::subtractQuantity(int quantity)
{
    throw Item_No_QuantityException();
}

void Item::addDurability(int durability)
{
    throw Item_No_DurabilityException();
}

void Item::subtractDurability(int durability)
{
    throw Item_No_DurabilityException();
}

/* 2. TOOL ITEM MODULE Implementations */

Non_Tool::Non_Tool() : Item(0, "NaN")
{
    this->Variant = "-";
};

Non_Tool::Non_Tool(int ID, string name, int Quantity, string Variant) : Item(ID, name)
{
    int temp = Quantity;
    
    if (temp > 64 || temp < 0)
        throw Non_Tool_QuantityException();
    else{
        this->Quantity = Quantity;
        this->Variant = Variant;
    }
}

Item *Non_Tool::deepCopy() const
{
    return new Non_Tool(*this);
}

string Non_Tool::getType() const
{
    return "NONTOOL";
}

string Non_Tool::getVariant() const
{
    return this->Variant;
}

void Non_Tool::setVariant(string Variant)
{
    this->Variant = Variant;
}

int Non_Tool::getQuantity() const
{
    return this->Quantity;
}

void Non_Tool::setQuantity(int quantity)
{
    int temp = quantity;
    
    if (temp > 64 || temp < 0)
        throw Non_Tool_QuantityException();
    else
        this->Quantity = quantity;
}
void Non_Tool::addQuantity(int quantity)
{
    int temp = this->Quantity + quantity;
    
    if (temp > 64 || temp < 0)
        throw Non_Tool_QuantityException();
    else
        this->Quantity += quantity;
}
void Non_Tool::subtractQuantity(int quantity)
{
    int temp = this->Quantity - quantity;
    
    if (temp > 64 || temp < 0)
        throw Non_Tool_QuantityException();
    else
        this->Quantity -= quantity;
}

/* 3. TOOL ITEM MODULE Implementations */

Tool::Tool() : Item(0, "NaN")
{
    this->Durability = 0;
}

Tool::Tool(int ID, string name, int Durability) : Item(ID, name)
{
    int temp = Durability;

    if (temp > 10 || temp < 0)
        throw Tool_DurabilityException();
    else
        this->Durability = Durability;
}

Item *Tool::deepCopy() const
{
    return new Tool(*this);
}

string Tool::getType() const
{
    return "TOOL";
}

int Tool::getQuantity() const
{
    return 1;
}

int Tool::getDurability() const
{
    return this->Durability;
}

void Tool::setDurability(int durability)
{
    int temp = durability;

    if (temp > 10 || temp < 0)
        throw Tool_DurabilityException();
    else
        this->Durability = durability;
}

void Tool::addDurability(int durability)
{
    int temp = this->Durability + durability;

    if (temp > 10 || temp < 0)
        throw Tool_DurabilityException();
    else
        this->Durability += durability;
}

void Tool::subtractDurability(int durability)
{
    int temp = this->Durability - durability;

    if (temp > 10 || temp < 0)
        throw Tool_DurabilityException();
    else
    this->Durability -= durability;
}

// 4. Comperator Similarity
bool Item::operator==(const Item &item)
{
    return this->ID == item.ID && this->Name == item.Name;
}

bool Non_Tool::operator==(const Non_Tool &item)
{
    return Item::operator==(item) && this->Quantity == item.Quantity && this->Variant == item.Variant;
}
bool Tool::operator==(const Tool &item)
{
    return Item::operator==(item) && this->Durability == item.Durability;
}