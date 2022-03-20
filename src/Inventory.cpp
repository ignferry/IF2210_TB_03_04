#include "../header/Inventory.hpp"

Inventory::Inventory(Load *load) {
    this->item = new Item*[INVENTORY_SLOT];
    this->load = load;
    // for (int i = 0; i < INVENTORY_SLOT; i++) {
    //     delete this->item[i];
    // }
}

Inventory::~Inventory() {
    for (int i = 0; i < INVENTORY_SLOT; i++) {
        delete this->item[i];
    }
    delete[] this->item;
}

void Inventory::addItem(int inventorySlotID, string name, int quantity) {
    this->item[inventorySlotID]->setID(load->getID(name));
    this->item[inventorySlotID]->setName(name);
    // this->item[inventorySlotID].setType(load->getType(name));
    this->item[inventorySlotID]->setQuantity(quantity);
    if (load->getType(name) == "TOOL") {
        this->item[inventorySlotID]->setDurability(10);
    }
}

void Inventory::subtractItem(int inventorySlotID, int quantity) {
    this->item[inventorySlotID]->subtractQuantity(quantity);
}

void Inventory::deleteItem(int inventorySlotID) {
    delete this->item[inventorySlotID];
}

bool Inventory::isEmptySlot(int inventorySlotID) {
    return this->item[inventorySlotID] == nullptr;
}

bool Inventory::isFullSlot(int inventorySlotID) {
    return this->item[inventorySlotID]->getQuantity() == MAX_ITEM;
}

int Inventory::remainingSlot(int inventorySlotID) {
    return MAX_ITEM - this->item[inventorySlotID]->getQuantity();
}

int Inventory::string_to_int(string strInventorySlotID) {
    if (strInventorySlotID.at(0) == 'I') {
        return stoi(strInventorySlotID.substr(1, strInventorySlotID.length()));
    } else {
        return -1;
    }
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
            if (this->item[i]->getType() == "NONTOOL") {
                cout << "| " << right << setw(15) << this->item[i]->getName() << "/qty:" << left << setw(2) << this->item[i]->getQuantity() << " ";
            } else {
                cout << "| " << right << setw(15) << this->item[i]->getName() << "/";
                this->durabilityOutput(this->item[i]->getDurability());
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
    for (int i = 0; i < INVENTORY_SLOT; i++) {
        if (this->item[i]->getName() == name && load->getType(name) == "NONTOOL" && !this->isFullSlot(i)) {
            if (quantity > this->remainingSlot(i)) {
                this->giveMessage(i, name, this->remainingSlot(i));
                quantity -= this->remainingSlot(i);
                this->item[i]->addQuantity(this->remainingSlot(i));
            } else {
                this->giveMessage(i, name, quantity);
                this->item[i]->addQuantity(quantity);
                quantity = 0;
                break;
            }
        }
    }
    if (quantity > 0) {
        for (int i = 0; i < INVENTORY_SLOT; i++) {
            if (this->isEmptySlot(i)) {
                if (load->getType(name) == "NONTOOL") {
                    if (quantity > MAX_ITEM) {
                        this->giveMessage(i, name, MAX_ITEM);
                        quantity -= MAX_ITEM;
                        this->addItem(i, name, MAX_ITEM);
                    } else {
                        this->giveMessage(i, name, quantity);
                        this->addItem(i, name, quantity);
                        break;
                    }
                } else {
                    this->giveMessage(i, name, 1);
                    quantity -= 1;
                    this->addItem(i, name, 1);
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
    if (inventorySlotID != -1) {
        if (this->item[inventorySlotID]->getQuantity() > quantity) {
            cout << "Berhasil membuang item " << this->item[inventorySlotID]->getName() << " sebanyak " << quantity << " pada slot ID inventory ke-" << inventorySlotID << endl;
            this->subtractItem(inventorySlotID, quantity);
        } else if (this->item[inventorySlotID]->getQuantity() == quantity) {
            cout << "Berhasil menghapus item " << this->item[inventorySlotID]->getName() << " pada slot ID inventory ke-" << inventorySlotID << endl;
            this->deleteItem(inventorySlotID);
        } else {
            cout << "Gagal membuang item" << endl;
        }
    } else {
        cout << "Masukan tidak valid" << endl;
    }
}

void Inventory::move(string strInventorySlotIDSrc, string strInventorySlotIDDest) {
    int inventorySlotIDSrc = this->string_to_int(strInventorySlotIDSrc);
    int inventorySlotIDDest = this->string_to_int(strInventorySlotIDDest);
    if (this->item[inventorySlotIDSrc] == this->item[inventorySlotIDDest] && this->item[inventorySlotIDSrc]->getType() == "NONTOOL" && this->item[inventorySlotIDDest]->getType() == "NONTOOL") {
        if (!this->isFullSlot(inventorySlotIDDest)) {
            if (this->item[inventorySlotIDSrc]->getQuantity() > this->remainingSlot(inventorySlotIDDest)) {
                cout << "Berhasil menumpuk item " << this->item[inventorySlotIDDest]->getName() << " sebanyak " << this->remainingSlot(inventorySlotIDDest) << " pada slot ID inventory ke-" << inventorySlotIDDest << endl;
                this->item[inventorySlotIDSrc]->subtractQuantity(this->remainingSlot(inventorySlotIDDest));
                this->item[inventorySlotIDDest]->setQuantity(MAX_ITEM);
                cout << "Tersisa " << this->item[inventorySlotIDSrc]->getQuantity() << " " << this->item[inventorySlotIDSrc]->getName() << " pada slot ID inventory ke-" << inventorySlotIDSrc << endl;
            } else {
                cout << "Berhasil menumpuk item " << this->item[inventorySlotIDDest]->getName() << " pada slot ID inventory ke-" << inventorySlotIDDest << endl;
                this->item[inventorySlotIDDest]->addQuantity(this->item[inventorySlotIDSrc]->getQuantity());
                this->deleteItem(inventorySlotIDSrc);
            }
        } else {
            cout << "Destinasi slot ID inventory sudah penuh" << endl;
        }
    } else {
        cout << "Gagal menumpuk item" << endl;
    }
}

void Inventory::use(string strInventorySlotID) {
    int inventorySlotID = this->string_to_int(strInventorySlotID);
    if (this->item[inventorySlotID]->getType() == "TOOL") {
        cout << "Berhasil menggunakan item " << this->item[inventorySlotID]->getName() << endl;
        this->item[inventorySlotID]->subtractDurability(1);
        if (this->item[inventorySlotID]->getDurability() == 0) {
            this->deleteItem(inventorySlotID);
        }
    } else if (this->item[inventorySlotID]->getType() == "NONTOOL") {
        cout << "Item " << this->item[inventorySlotID]->getName() << " tidak dapat digunakan karena bukan tool" << endl;
    } else {
        cout << "Tidak ada item yang dapat digunakan dalam slot ini" << endl;
    }
}

/* return attribute array of item*/
Item** Inventory::get_items() const {
    return this->item;
}