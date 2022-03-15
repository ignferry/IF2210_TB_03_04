#include "../header/Inventory.hpp"

Inventory::Inventory() {
    this->item = new Item[INVENTORY_SLOT];
}

Inventory::~Inventory() {
    delete[] this->item;
}

void Inventory::addItem(int inventorySlotID, string name, string type, int quantity) {
    this->item[inventorySlotID].setID(this->item[inventorySlotID].getID(name));
    this->item[inventorySlotID].setName(name);
    this->item[inventorySlotID].setType(type);
    this->item[inventorySlotID].addQuantity(quantity);
}

void Inventory::subtractItem(int inventorySlotID, int quantity) {
    this->item[inventorySlotID].subtractQuantity(quantity);
}

void Inventory::deleteItem(int inventorySlotID) {
    this->item[inventorySlotID].setID(0);
    this->item[inventorySlotID].setName("NaN");
    this->item[inventorySlotID].setType("NaN");
    this->item[inventorySlotID].setQuantity(0);
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
        string stuff(24, '-');
        cout << "+" << stuff;
    }
    cout << "+" << endl;
}

void Inventory::durabilityOutput(int durability) {
    int count = 0;
    cout << BOLDGREEN;
    while (durability != 0) {
        if (durability - 2 >= 0) {
            cout << "I";
            durability -= 2;
        } else if (durability - 1 >= 0) {
            cout << "i";
            durability -= 1;
        }
        count++;
    }
    cout << RESET << left << setw(6-count) << " " << " ";
}

void Inventory::showInventory() {
    this->borderInventory();
    int count = 0;
    for (int i = 0; i < INVENTORY_SLOT; i++) {
        if (!this->isEmptySlot(i) && this->item[i].getType() == "NONTOOL") {
            cout << "| " << right << setw(15) << this->item[i].getName() << "/qty:" << left << setw(2) << this->item[i].getQuantity() << " ";
        } else if (!this->isEmptySlot(i) && this->item[i].getType() == "TOOL") {
            cout << "| " << right << setw(15) << this->item[i].getName() << "/";
            this->durabilityOutput(this->item[i].getDurability());
        } else {
            string stuff(22, ' ');
            cout << "| " << stuff << " "; 
        }
        count++;
        if (count % 9 == 0) {
            cout << "|" << endl;
            this->borderInventory();
        }
    }
}

void Inventory::giveMessage(int inventorySlotID, string name, int quantity) {
    cout << "Berhasil menambahkan item " << name << " sebanyak " << quantity << " pada slot ID inventory ke-" << inventorySlotID << endl;
}

void Inventory::give(string name, int quantity) {
    for (int i = 0; i < INVENTORY_SLOT; i++) {
        if (this->item[i].getName() == name && !this->isFullSlot(i)) {
            if (quantity > this->remainingSlot(i)) {
                quantity -= this->remainingSlot(i);
                this->giveMessage(i, name, this->remainingSlot(i));
                this->item[i].addQuantity(this->remainingSlot(i));
            } else {
                this->item[i].addQuantity(quantity);
                this->giveMessage(i, name, quantity);
                quantity = 0;
                break;
            }
        }
    }
    if (quantity > 0) {
        for (int i = 0; i < INVENTORY_SLOT; i++) {
            if (this->isEmptySlot(i)) {
                if (quantity > MAX_ITEM) {
                    quantity -= MAX_ITEM;
                    this->addItem(i, name, "TOOL", MAX_ITEM);
                    this->giveMessage(i, name, MAX_ITEM);
                } else {
                    this->addItem(i, name, "NONTOOL", quantity);
                    this->giveMessage(i, name, quantity);
                    break;
                }
            }
        }
    }
}

void Inventory::discard(int inventorySlotID, int quantity) {
    if (this->item[inventorySlotID].getQuantity() > quantity) {
        this->subtractItem(inventorySlotID, quantity);
        cout << "Berhasil membuang item " << this->item[inventorySlotID].getName() << " sebanyak " << quantity << " pada slot ID inventory ke-" << inventorySlotID << endl;
    } else if (this->item[inventorySlotID].getQuantity() == quantity) {
        cout << "Berhasil menghapus item " << this->item[inventorySlotID].getName() << " pada slot ID inventory ke-" << inventorySlotID << endl;
        this->deleteItem(inventorySlotID);
    } else {
        cout << "Gagal membuang item" << endl;
    }
}

void Inventory::use(int inventorySlotID) {
    
}

int main() {
    Inventory i;
    i.showInventory();
    i.give("DIAMOND_PICKAXE", 100);
    i.showInventory();
    i.give("DIAMOND_SWORD", 50);
    i.showInventory();
    i.give("DIAMOND_PICKAXE", 100);
    i.showInventory();
    i.give("DIAMOND_SWORD", 100);
    i.showInventory();
    i.give("DIAMOND_PICKAXE", 50);
    i.showInventory();
    i.discard(0, 63);
    i.showInventory();
    i.discard(1, 64);
    i.showInventory();
    i.discard(2, 65);
    i.showInventory();
    return 0;
}

// g++ -std=c++17 .\\src\\Inventory.cpp .\\src\\Item.cpp -o .\\src\\main.exe
// .\\src\\main