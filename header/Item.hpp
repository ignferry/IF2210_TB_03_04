#ifndef _ITEM_HPP_
#define _ITEM_HPP_

#include <iostream>
using namespace std;
#define MAX_DURABILITY 10
#include "ItemException.hpp"
class Item
{
private:
    int ID;
    string Name;

public:
    // Constructor
    Item();
    Item(int ID, string Name);

    // Deep Copy
    virtual Item *deepCopy() const = 0;
    // Mengembalikan pointer to item yang menunjuk pada salinan dari item dan child object

    // Destuctor
    virtual ~Item();

    // Setter Getter
    int getID() const;
    void setID(int id);

    string getName() const;
    void setName(string name);

    virtual string getType() const = 0;

    virtual int getQuantity() const = 0;
    virtual void setQuantity(int quantity);

    virtual string getVariant() const;
    virtual void setVariant(string Variant);

    virtual int getDurability() const;
    virtual void setDurability(int durability);

    // Modifier
    virtual void addQuantity(int quantity);
    virtual void subtractQuantity(int quantity);
    virtual void addDurability(int durability);
    virtual void subtractDurability(int durability);

    // Comparison
    virtual bool operator==(const Item &item);
};

class Non_Tool : public Item
{
private:
    int Quantity;
    string Variant;

public:
    // Constructor
    Non_Tool();
    Non_Tool(int ID, string name, int Quantity, string Variant);

    // Deep Copy
    Item *deepCopy() const;

    bool operator==(const Non_Tool &nt);

    // Setter Getter
    string getType() const;

    string getVariant() const;
    void setVariant(string Variant);

    int getQuantity() const;

    // Modifier
    void setQuantity(int quantity);
    void addQuantity(int quantity);
    void subtractQuantity(int quantity);
};

class Tool : public Item
{
private:
    int Durability;

public:
    // Constructor
    Tool();
    Tool(int ID, string name, int Durability);

    Item *deepCopy() const;

    // Setter Getter
    string getType() const;
    int getQuantity() const;

    int getDurability() const;
    void setDurability(int durability);

    // Modifier
    void addDurability(int durability);
    void subtractDurability(int durability);
    bool operator==(const Tool &t);
};

#endif