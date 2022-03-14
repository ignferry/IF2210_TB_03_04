#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include <iostream>
#include <iomanip>
#include "Item.hpp"
using namespace std;

#define INVENTORY_SLOT 27
#define MAX_ITEM 64

class Inventory {
    private:
        Item* item;

    public:
        Inventory();
        ~Inventory();
        bool isEmptySlot(int inventorySlotID);
        bool isFullSlot(int inventorySlotID);
        int remainingSlot(int inventorySlotID);
        void borderInventory();
        void showInventory();
        void give(string name, int quantity);

};

#endif