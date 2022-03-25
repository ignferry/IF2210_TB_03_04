#ifndef __CRAFTING_HPP__
#define __CRAFTING_HPP__

#include <iomanip>
#include "Item.hpp"
#include "Recipe.hpp"
#include "Exception.hpp"
using namespace std;

class Crafting
{
private:
    Item ***craftArr;
    int rowEff;
    int colEff;

public:
    // CONSTRUCTOR
    Crafting();

    // COPY CONSTRUCTOR
    Crafting(const Crafting &c);

    // DESTRUCTOR
    ~Crafting();

    // ATRIBUT METHOD
    void checkRow();
    void checkCol();
    int getRow();
    int getCol();
    Item *getItem(int row, int col);

    // OTHER METHOD
    bool isSlotEmpty(int row, int col);
    // MENGECEK APAKAH SLOT CRAFTING DI KOLOM DAN BARIS MASUKAN KOSONG
    void addItem(Item *I, int row, int col, int qty);
    // MENAMBAHKAN ITEM KE KOLOM DAN BARIS CRAFTING TABLE
    void discardItem(int row, int col);
    // MENGHAPUS ITEM DI KOLOM DAN BARIS CRAFTING TABLE
    void showCraftTable();
    // MENAMPILKAN CRAFTING TABLE
    bool operator==(Recipe r);
    // MENGECEK KONFIGURASI CRAFTING TABLE DENGAN RECIPE APAKAH SAMA PERSIS ATAU TIDAK
    bool checkTranslation(Recipe r, int ver, int hor);
    // MENGECEK SETIAP TRANSLASI DARI CRAFTING TABLE DENGAN RECIPE
    bool checkSimetri(Recipe r);
    // MENGECEK SIMETRI DARI CRAFTING TABLE DENGAN RECIPE
    bool configurationCheck(Recipe r);
    // MENGECEK SEMUA KEMUNGKINAN CONFIGURASI CRAFTING TABLE DENGAN RECIPE
    bool isAllTool();
    // MENGECEK APAKAH SEMUA ITEM DI CRAFTING TABLE ADALAH TOOL
    string isAllTheSameTool();
    // MENGECEK APAKAH SEMUA ITEM DI CRAFTING TABLE ADALAH TOOL YANG SAMA
    int durabilitySum();
    void substractQtyCraftTable();
};

#endif