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

    public:
        Item();
        int getID();
        int getID(string name);
        void setID(int id);
        string getName();
        void setName(string name);
        string getType();
        void setType(string type);
        int getQuantity();
        void addQuantity(int quantity);
        void subtractQuantity(int quantity);

};

#endif