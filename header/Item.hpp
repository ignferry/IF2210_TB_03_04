#ifndef ITEM_HPP
#define ITEM_HPP

#include <iostream>
using namespace std;

class Item {
    private:
        int ID;
        string Name;
        int Quantity;

    public:
        Item();
        int getID();
        string getName();
        int getQuantity();
        void addQuantity(int quantity);

};

#endif