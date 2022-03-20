#ifndef __CRAFTING_HPP__
#define __CRAFTING_HPP__

#include <string>
#include <iomanip>
#include "Item2.hpp"
#include "Recipe.hpp"
using namespace std;

class Crafting
{
private:
    Item ***craftArr;
    int rowEff;
    int colEff;

public:
    Crafting();
    Crafting(const Crafting &c);
    ~Crafting();
    void checkRow();
    void checkCol();
    int getRow();
    int getCol();
    bool isSlotEmpty(int row, int col);      // Mengecek apakah slot position kosong
    void addItem(Item *I, int row, int col); // Menambahkan item ke slot position
    void discardItem(int row, int col);      // Membuang item di slot position
    void showCraftTable();
    bool operator==(Recipe r); // Mengecek apakah recipe r sama dengan di craftable
    bool checkTranslation(Recipe r, int ver, int hor);
    bool checkSimetri(Recipe r);
    bool configurationCheck(Recipe r);
    bool isAllTool();
    bool isAllTheSameTool();
};

#endif