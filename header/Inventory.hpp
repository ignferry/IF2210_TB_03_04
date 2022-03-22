#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include <iostream>
#include <iomanip>
#include <vector>
#include <tuple>
#include "Item2.hpp"
#include "ItemList.hpp"
using namespace std;

#define INVENTORY_SLOT 27
#define MAX_ITEM 64
#define RESET "\033[0m"
#define BOLDGREEN "\033[1m\033[32m"

class Inventory {
    private:
        Item** item;

    public:
        Inventory();
        ~Inventory();
        void addItem(int inventorySlotID, string name, int quantity, ItemList& itemList);
        void subtractItem(int inventorySlotID, int quantity);
        void deleteItem(int inventorySlotID);
        bool isEmptySlot(int inventorySlotID);
        bool isFullSlot(int inventorySlotID);
        int remainingSlot(int inventorySlotID);
        int string_to_int(string strInventorySlotID);
        void borderInventory();
        void durabilityOutput(int durability);
        void showInventory();
        void giveMessage(int inventorySlotID, string name, int quantity);
        void give(string name, int quantity, ItemList& itemList);
        void discard(string strInventorySlotID, int quantity);
        void move(string strInventorySlotIDSrc, string strInventorySlotIDDest);
        void use(string strInventorySlotID);

        /* return attribute array of item */
        Item** get_items() const;

};

#endif