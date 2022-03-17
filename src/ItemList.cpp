#include "../header/ItemList.hpp"

// CONSTRUCTOR
ItemList::ItemList() {}
// Default constructor

ItemList::ItemList(string directory) {
// Constructor yang langsung mengisi vector item sesuai dengan konfigurasi pada directory

}

// CCTOR
ItemList::ItemList(const ItemList& il) {

}

// DTOR
ItemList::~ItemList() {

}

void ItemList::setItemsConfiguration(string directory) {
// Mengisi vector item sesuai dengan konfigurasi pada directory

}

Item* ItemList::searchItem(string itemName) {
// Mengembalikan pointer to objek Item dengan nama itemName
    Item* x;
    return x;
}