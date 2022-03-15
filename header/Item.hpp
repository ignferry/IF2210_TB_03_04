#ifndef ITEM_HPP
#define ITEM_HPP

#include <iostream>
using namespace std;

class Item {
    private:
        int ID;
        string Name;
        string Type;
        int Quantity;
        int Durability;

    public:
        Item();
        int getID();
        void setID(int id);
        string getName();
        void setName(string name);
        string getType();
        void setType(string type);
        int getQuantity();
        void setQuantity(int quantity);
        void addQuantity(int quantity);
        void subtractQuantity(int quantity);
        int getDurability();
        void setDurability(int durability);
        void addDurability(int durability);
        void subtractDurability(int durability);

};

#endif