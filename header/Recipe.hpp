#ifndef __RECIPE_HPP__
#define __RECIPE_HPP__

#include <string>
using namespace std;

class Recipe {
    private:
        int row;
        int col;
        string **ingredients;
        string resultName;
        int resultQuantity;
    public:
        // CONSTRUCTOR
        Recipe();
        // Default ctor Recipe
        Recipe(int row, int col);
        // Custom ctor Recipe dengan row dan col sesuai dengan parameter


        // CCTOR
        Recipe(Recipe &r);
        // cctor Recipe


        // DESTRUCTOR
        ~Recipe();


        // GETTER DAN SETTER
        const int getRow();
        // Mengembalikan nilai atribut row
        void setRow(int row);
        // Mengubah atribut row pada suatu objek Recipe sesuai dengan parameter row

        const int getCol();
        // Mengembalikan nilai atribut col
        void setCol(int col);
        // Mengubah atirbut col pada suatu objek Recipe sesuai dengan parameter col

        const string getIngredientsAt(int row, int col);
        // Mengembalikan nama ingredient pada koordinat (row, col)
        void setIngredientAt(string name, int row, int col);
        // Mengubah nama ingredient pada koordinat (row, col) menjadi name

        const string getResultName();
        // Mengembalikan nama hasil crafting
        void setResultName(string name);
        // Mengubah nama hasil crafting menjadi name

        const int getResultQuantity();
        // Mengembalikan jumlah hasil crafting
        void setResultQuantity(int quantity);
        // Mengubah jumlah hasil crafting menjadi quantity
};

#endif