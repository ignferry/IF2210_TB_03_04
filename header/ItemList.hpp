#ifndef __ITEM_LIST_HPP__
#define __ITEM_LIST_HPP__

#include "Item.hpp"
#include <vector>

using namespace std;

class ItemList {
    private: 
        vector<Item*> items;
    public:
        // CONSTRUCTOR
        ItemList();
        // Default constructor
        ItemList(string directory);
        // Constructor yang langsung mengisi vector item sesuai dengan konfigurasi pada directory

        // CCTOR
        ItemList(const ItemList& il);

        // DTOR
        ~ItemList();

        void setItemsConfiguration(string directory);
        // Mengisi vector item sesuai dengan konfigurasi pada directory

        Item* searchItem(string itemName);
        // Mengembalikan pointer to objek Item dengan nama itemName
};

#endif