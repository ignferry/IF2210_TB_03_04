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
        void addItem(int inventorySlotID, string name, string type, int quantity);
        void subtractItem(int inventorySlotID, int quantity);
        void deleteItem(int inventorySlotID);
        bool isEmptySlot(int inventorySlotID);
        bool isFullSlot(int inventorySlotID);
        int remainingSlot(int inventorySlotID);
        void borderInventory();
        void showInventory();
        void giveMessage(int inventorySlotID, string name, int quantity);
        void give(string name, int quantity);
        void discard(int inventorySlotID, int quantity);

};

#endif