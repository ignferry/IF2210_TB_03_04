#ifndef __ITEM_LIST_HPP__
#define __ITEM_LIST_HPP__

#include "Item.hpp"
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

        Item* createItem(string itemName, int quantity);
        // Mengembalikan pointer to objek baru Item dengan nama itemName dengan jumlah quantity
        // Hanya dapat digunakan untuk item non tool
        // Jika item bertipe tool akan mengembalikan nullptr

        void printItems() const;
        // Print ID, nama, dan tipe semua item yang ada di itemList
};

#endif