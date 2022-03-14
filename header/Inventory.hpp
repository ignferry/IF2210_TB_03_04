#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include <iostream>
#include <iomanip>
#include "Item.hpp"
using namespace std;

#define INVENTORY_SLOT 27

class Inventory {
    private:
        Item* item;

    public:
        Inventory();
        ~Inventory();
        Item getItem(int inventorySlotID);
        bool isEmptySlot(int inventorySlotID);
        void borderInventory();
        void showInventory();

};

#endif