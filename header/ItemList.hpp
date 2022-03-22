#ifndef __ITEM_LIST_HPP__
#define __ITEM_LIST_HPP__

#include "Item2.hpp"
#include <vector>
#include <fstream>
#include <iostream>
#include <filesystem>

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

        Item* selectItem(string itemName) const;
        // Mengembalikan pointer to objek Item dalam vector items
        // Fungsi digunakan hanya untuk membaca atribut umum suatu item

        Item* createItem(string itemName);
        // Mengembalikan pointer to objek baru Item dengan nama itemName

        void printItems() const;
};

#endif