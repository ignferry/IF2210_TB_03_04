#include "../header/Inventory.hpp"
#include "../header/Pair.hpp"
#include "../header/Exception.hpp"

Inventory::Inventory() {
    this->item = new Item*[INVENTORY_SLOT];
    for (int i = 0; i < INVENTORY_SLOT; i++) {
        this->item[i] = nullptr;
    }
}

Inventory::~Inventory() {
    for (int i = 0; i < INVENTORY_SLOT; i++) {
        delete this->item[i];
    }
    delete[] this->item;
}

void Inventory::addItem(int inventorySlotID, string name, int quantity, ItemList& itemList) {
    this->item[inventorySlotID] = itemList.createItem(name);
    this->item[inventorySlotID]->setQuantity(quantity);
    if (itemList.selectItem(name)->getType() == "TOOL") {
        this->item[inventorySlotID]->setDurability(10);
    }
}

void Inventory::subtractItem(int inventorySlotID, int quantity) {
    try
    {
        this->item[inventorySlotID]->subtractQuantity(quantity);
    }
    catch(Item_No_QuantityException& e)
    {
        cout << e.what() << endl;
    }
    catch(Tool_QuantityException& e){
        cout << e.what() << endl;
    }
    catch(Non_Tool_QuantityException& e){
        cout << e.what() << endl;
    }
    
}

void Inventory::deleteItem(int inventorySlotID) {
    delete this->item[inventorySlotID];
    this->item[inventorySlotID] = nullptr;
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

void Inventory::give(string name, int quantity, ItemList& itemList) {
    // Memberikan item dengan nama name sebanyak quantity

    // Catat slot inventory yang mengandung item dengan nama name dan berapa quantity yang masih dapat ditampungnya
    // Hanya untuk NONTOOL
    Item* item = itemList.selectItem(name);

    // Cek apakah ada item dengan nama name
    if (item == nullptr) {
        throw new NoSuchItemException(name);
    }

    string itemType = item->getType();
    vector<Pair<int, int>> sameNameSlots; // {slotID, quantity}

    if (itemType == "NONTOOL") {
        int i = 0;
        while (i < INVENTORY_SLOT && quantity > 0) {
            if (!this->isEmptySlot(i)) {
                if (this->item[i]->getName() == name && !this->isFullSlot(i)) {
                    if (quantity > this->remainingSlot(i)) {
                        sameNameSlots.push_back(Pair<int, int>(i, this->remainingSlot(i)));
                        quantity -= this->remainingSlot(i);
                    }
                    else {
                        sameNameSlots.push_back(Pair<int, int>(i, quantity));
                        quantity = 0;
                    }
                }
            }
            i++;
        }
    }

    // Catat slot inventory yang kosong jika masih ada item yang memerlukan slot
    vector<Pair<int, int>> emptySlotsUsed; // {slotID, quantity}
    if (quantity != 0) {
        int i = 0;
        while (i < INVENTORY_SLOT && quantity > 0) {
            if (this->isEmptySlot(i)) {
                if (itemType == "NONTOOL") {
                    if (quantity > MAX_ITEM) {
                        emptySlotsUsed.push_back(Pair<int, int>(i, MAX_ITEM));
                        quantity -= MAX_ITEM;
                    }
                    else {
                        emptySlotsUsed.push_back(Pair<int, int>(i, quantity));
                        quantity = 0;
                    }
                }
                else {
                    emptySlotsUsed.push_back(Pair<int, int>(i, 1));
                    quantity -= 1;
                }
            }
            i++;
        }
    }
    
    // Command gagal jika masih ada sejumlah item yang belum teralokasi suatu slot
    if (quantity != 0) {
        throw new InventoryFullException();
    }
    else {
        // Memberikan item ke slot sesuai dengan proses sebelumnya
        for (auto itr : sameNameSlots) {
            int slotID = itr.getFirst();
            int slotQuantity = itr.getSecond();
            this->giveMessage(slotID, name, slotQuantity);
            this->item[slotID]->addQuantity(slotQuantity);
        }
        for (auto itr : emptySlotsUsed) {
            int slotID = itr.getFirst();
            int slotQuantity = itr.getSecond();
            this->giveMessage(slotID, name, slotQuantity);
            this->item[slotID] = itemList.createItem(name);
            if (this->item[slotID]->getType() == "NONTOOL") {
                this->item[slotID]->setQuantity(slotQuantity);
            }
        }
    }
}

void Inventory::discard(string strInventorySlotID, int quantity) {
    // Membuang quantity buah item dari slot inventory slotID
    int inventorySlotID = this->string_to_int(strInventorySlotID);
    if (inventorySlotID != -1) {
        if (inventorySlotID < 0 || inventorySlotID > 26) {
            // Cek apakah SlotID dalam rentang slot inventory
            throw new OutOfInventoryBoundsException(inventorySlotID);
        }
        else if (this->isEmptySlot(inventorySlotID)) {
             // Cek apakah slot kosong
            throw new SlotEmptyException(strInventorySlotID);
        }
        else if (this->item[inventorySlotID]->getQuantity() > quantity) {
            cout << "Berhasil membuang item " << this->item[inventorySlotID]->getName() << " sebanyak " << quantity << " pada slot ID inventory ke-" << inventorySlotID << endl;
            this->subtractItem(inventorySlotID, quantity);
        } else if (this->item[inventorySlotID]->getQuantity() == quantity) {
            cout << "Berhasil menghapus item " << this->item[inventorySlotID]->getName() << " pada slot ID inventory ke-" << inventorySlotID << endl;
            this->deleteItem(inventorySlotID);
        } else {
            cout << "Nilai masukan melebihi jumlah item yang tersedia" << endl;
        }
    } else {
        cout << "Masukan tidak valid" << endl;
    }
}

void Inventory::move(string strInventorySlotIDSrc, string strInventorySlotIDDest) {
    int inventorySlotIDSrc = this->string_to_int(strInventorySlotIDSrc);
    int inventorySlotIDDest = this->string_to_int(strInventorySlotIDDest);

    // Cek apakah SlotID dalam rentang slot inventory
    if (inventorySlotIDSrc < 0 || inventorySlotIDSrc > 26) {
        throw new OutOfInventoryBoundsException(inventorySlotIDSrc);
    }
    if (inventorySlotIDDest < 0 || inventorySlotIDDest > 26) {
        throw new OutOfInventoryBoundsException(inventorySlotIDDest);
    }

    // Cek apakah slot src kosong
    if (this->isEmptySlot(inventorySlotIDSrc)) {
        throw new SlotEmptyException(strInventorySlotIDSrc);
    }

    // Pindahkan item secara keseluruhan ke slot baru jika slot destinasi kosong
    if (this->item[inventorySlotIDDest] == nullptr && inventorySlotIDDest != inventorySlotIDSrc) {
        this->item[inventorySlotIDDest] = this->item[inventorySlotIDSrc];
        this->item[inventorySlotIDSrc] = nullptr;
        cout << "Berhasil memindahkan " << this->item[inventorySlotIDDest]->getName() << " sebanyak " << this->item[inventorySlotIDDest]->getQuantity() << " ke slot ID inventory ke-" << inventorySlotIDDest << endl;
    }
    // Item pada slot destinasi sama dengan item pada slot sumber dan jenis item NONTOOL
    else if (this->item[inventorySlotIDSrc]->getName() == this->item[inventorySlotIDDest]->getName() && this->item[inventorySlotIDSrc]->getType() == "NONTOOL") {
        if (!this->isFullSlot(inventorySlotIDDest)) {
            try{
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
            }
            catch(Item_No_QuantityException& e)
            {
                cout << e.what() << endl;
            }
            catch(Tool_QuantityException& e){
                cout << e.what() << endl;
            }
            catch(Non_Tool_QuantityException& e){
                cout << e.what() << endl;
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

    // Cek apakah SlotID dalam rentang slot inventory
    if (inventorySlotID < 0 || inventorySlotID > 26) {
        throw new OutOfInventoryBoundsException(inventorySlotID);
    }
    // Cek apakah slot kosong
    if (this->isEmptySlot(inventorySlotID)) {
        throw new SlotEmptyException(strInventorySlotID);
    }
    if (this->item[inventorySlotID]->getType() == "TOOL") {
        try{
            cout << "Berhasil menggunakan item " << this->item[inventorySlotID]->getName() << endl;
            this->item[inventorySlotID]->subtractDurability(1);
            if (this->item[inventorySlotID]->getDurability() == 0) {
                this->deleteItem(inventorySlotID);
            }
        }
        catch(Item_No_DurabilityException& e)
        {
            cout << e.what() << endl;
        }
        catch(Tool_DurabilityException& e){
            cout << e.what() << endl;
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