#include "../header/Inventory.hpp"

Inventory::Inventory() {
    this->item = new Item[INVENTORY_SLOT];
}

Inventory::~Inventory() {
    delete[] this->item;
}

bool Inventory::isEmptySlot(int inventorySlotID) {
    return this->item[inventorySlotID].getID() == 0;
}

bool Inventory::isFullSlot(int inventorySlotID) {
    return this->item[inventorySlotID].getQuantity() == MAX_ITEM;
}

int Inventory::remainingSlot(int inventorySlotID) {
    return MAX_ITEM - this->item[inventorySlotID].getQuantity();
}

void Inventory::borderInventory() {
    for (int i = 0; i < 9; i++) {
        string stuff(20, '-');
        cout << "+" << stuff;
    }
    cout << "+" << endl;
}

void Inventory::showInventory() {
    this->borderInventory();
    int count = 0;
    for (int i = 0; i < INVENTORY_SLOT; i++) {
        if (!this->isEmptySlot(i)) {
            cout << "| " << right << setw(15) << this->item[i].getName() << "/" << left << setw(2) << this->item[i].getQuantity() << " ";
        } else {
            string stuff(18, ' ');
            cout << "| " << stuff << " "; 
        }
        count++;
        if (count % 9 == 0) {
            cout << "|" << endl;
            this->borderInventory();
        }
    }
}

void Inventory::give(string name, int quantity) {
    for (int i = 0; i < INVENTORY_SLOT; i++) {
        if (this->item[i].getName() == name && !this->isFullSlot(i)) {
            if (quantity > this->remainingSlot(i)) {
                quantity -= this->remainingSlot(i);
                this->item[i].addQuantity(this->remainingSlot(i));
            } else {
                this->item[i].addQuantity(quantity);
                break;
            }
        }
    }
    if (quantity > 0) {
        for (int i = 0; i < INVENTORY_SLOT; i++) {
            if (this->isEmptySlot(i)) {
                if (quantity > MAX_ITEM) {
                    quantity -= MAX_ITEM;
                    this->item[i].addQuantity(MAX_ITEM);
                } else {
                    this->item[i].addQuantity(quantity);
                    break;
                }
            }
        }
    }
}

int main() {
    Inventory i;
    i.showInventory();
    return 0;
}

// g++ -std=c++17 .\\src\\Inventory.cpp .\\src\\Item.cpp -o .\\src\\main.exe
// .\\src\\main