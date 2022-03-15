#ifndef CRAFTING_HPP
#define CRAFTING_HPP

#include <Item.hpp>

#define CraftSlot 9;

class Crafting
{
private:
    Item *craftArr;

public:
    Crafting();
    ~Crafting();
    bool isSlotEmpty(int position);     // Mengecek apakah slot position kosong
    void addItem(Item i, int position); // Menambahkan item ke slot position
    void discardItem(int position);     // Membuang item di slot position
    void showCraftTable();
    // Bool isExistInRecipe();
};

#endif