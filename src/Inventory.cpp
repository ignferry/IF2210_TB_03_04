#include "../header/Inventory.hpp"

Inventory::Inventory() {
    this->item = new Item[INVENTORY_SLOT];
}

Inventory::~Inventory() {
    delete[] this->item;
}

void Inventory::addItem(int inventorySlotID, string name, int quantity) {
    Load l("load");
    this->item[inventorySlotID].setID(l.getID(name));
    this->item[inventorySlotID].setName(name);
    this->item[inventorySlotID].setType(l.getType(name));
    this->item[inventorySlotID].setQuantity(quantity);
    if (l.getType(name) == "TOOL") {
        this->item[inventorySlotID].setDurability(MAX_DURABILITY);
    }
}

void Inventory::subtractItem(int inventorySlotID, int quantity) {
    this->item[inventorySlotID].subtractQuantity(quantity);
}

void Inventory::deleteItem(int inventorySlotID) {
    this->item[inventorySlotID].setID(0);
    this->item[inventorySlotID].setName("NaN");
    this->item[inventorySlotID].setType("NaN");
    this->item[inventorySlotID].setQuantity(0);
    this->item[inventorySlotID].setDurability(0);
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

int Inventory::string_to_int(string strInventorySlotID) {
    return stoi(strInventorySlotID.substr(1, strInventorySlotID.length()));
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
        if (!this->isEmptySlot(i)) {
            if (this->item[i].getType() == "NONTOOL") {
                cout << "| " << right << setw(15) << this->item[i].getName() << "/qty:" << left << setw(2) << this->item[i].getQuantity() << " ";
            } else {
                cout << "| " << right << setw(15) << this->item[i].getName() << "/";
                this->durabilityOutput(this->item[i].getDurability());
            }
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
    Load l("load");
    for (int i = 0; i < INVENTORY_SLOT; i++) {
        if (l.getType(name) == "NONTOOL" && this->item[i].getName() == name && !this->isFullSlot(i)) {
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
                if (l.getType(name) == "NONTOOL") {
                    if (quantity > MAX_ITEM) {
                        quantity -= MAX_ITEM;
                        this->addItem(i, name, MAX_ITEM);
                        this->giveMessage(i, name, MAX_ITEM);
                    } else {
                        this->addItem(i, name, quantity);
                        this->giveMessage(i, name, quantity);
                        break;
                    }
                } else {
                    quantity -= 1;
                    this->addItem(i, name, 1);
                    this->giveMessage(i, name, 1);
                    if (quantity == 0) {
                        break;
                    }
                }
            }
        }
    }
}

void Inventory::discard(string strInventorySlotID, int quantity) {
    int inventorySlotID = this->string_to_int(strInventorySlotID);
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

void Inventory::use(string strInventorySlotID) {
    int inventorySlotID = this->string_to_int(strInventorySlotID);
    if (this->item[inventorySlotID].getType() == "TOOL") {
        this->item[inventorySlotID].subtractDurability(1);
        cout << "Berhasil menggunakan item " << this->item[inventorySlotID].getName() << endl;
        if (this->item[inventorySlotID].getDurability() == 0) {
            this->deleteItem(inventorySlotID);
        }
    } else if (this->item[inventorySlotID].getType() == "NONTOOL") {
        cout << "Item " << this->item[inventorySlotID].getName() << " tidak dapat digunakan karena bukan tool" << endl;
    } else {
        cout << "Tidak ada item yang dapat digunakan dalam slot ini" << endl;
    }
}