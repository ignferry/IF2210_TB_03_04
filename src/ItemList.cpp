#include "../header/ItemList.hpp"

// CONSTRUCTOR
ItemList::ItemList() {}
// Default constructor

ItemList::ItemList(string directory) {
// Constructor yang langsung mengisi vector item sesuai dengan konfigurasi pada directory
    this->setItemsConfiguration(directory);
}

// CCTOR
ItemList::ItemList(const ItemList& il) {
    for (auto itr : il.items) {
        this->items.push_back(itr->deepCopy());
    }
}

// DTOR
ItemList::~ItemList() {
    for (auto itr : this->items) {
        delete itr;
    }
}

void ItemList::setItemsConfiguration(string directory) {
// Mengisi vector item sesuai dengan konfigurasi pada directory
    ifstream itemConfigFile(directory);
    
    for(string line; getline(itemConfigFile, line);) {
        int ID;
        string name, variant, type;

        stringstream lineStream(line);
        lineStream >> ID >> name >> variant >> type;
        Item* item;

        if (type == "NONTOOL") {
            item = new Non_Tool(ID, name, 1, variant);
        }
        else {
            item = new Tool(ID, name, MAX_DURABILITY);
        }

        this->items.push_back(item);
    }
}

Item* ItemList::createItem(string itemName) {
// Mengembalikan pointer to objek Item dengan nama itemName
// Jika tidak ditemukan, mengembalikan nullptr
    for (auto itr : this->items) {
        if (itr->getName() == itemName) {
            return itr->deepCopy();
        }
    }
    // Mungkin nanti harus ada throw exception kalau tidak ketemu
    return nullptr;
}

void ItemList::printItems() const {
    for (auto itr : this->items) {
        cout << itr->getID() << " " << itr->getName() << " " << itr->getType() << endl;
    }
}