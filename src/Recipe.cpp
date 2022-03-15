#include "../header/Recipe.hpp"

// CONSTRUCTOR
Recipe::Recipe() {
// Default ctor Recipe
    this->row = 3;
    this->col = 3;
    this->ingredients = new string*[3];
    for (int i = 0; i < this->row; i++) {
        this->ingredients[i] = new string[3];
    }
    this->resultName = "";
    this->resultQuantity = 0;
}

Recipe::Recipe(int row, int col) {
// Custom ctor Recipe dengan row dan col sesuai dengan parameter
    this->row = row;
    this->col = col;
    this->ingredients = new string*[this->row];
    for (int i = 0; i < this->row; i++) {
        this->ingredients[i] = new string[this->col];
    }
    this->resultName = "";
    this->resultQuantity = 0;
}


// DESTRUCTOR
Recipe::~Recipe() {
    for (int i = 0; i < this->row; i++) {
        delete[] this->ingredients[i];
    }
    delete[] this->ingredients;
}


// GETTER DAN SETTER
const int Recipe::getRow() {
// Mengembalikan nilai atribut row
    return this->row;
}
void Recipe::setRow(int row){
// Mengubah atribut row pada suatu objek Recipe sesuai dengan parameter row
    this->row = row;
}

const int Recipe::getCol(){
// Mengembalikan nilai atribut col
    return this->col;
}
void Recipe::setCol(int col){
// Mengubah atirbut col pada suatu objek Recipe sesuai dengan parameter col
    this->col = col;
}

const string Recipe::getIngredientsAt(int row, int col){
// Mengembalikan nama ingredient pada koordinat (row, col)
    return this->ingredients[row][col];
}
void Recipe::setIngredientAt(string name, int row, int col){
// Mengubah nama ingredient pada koordinat (row, col) menjadi name
    this->ingredients[row][col] = name;
}

const string Recipe::getResultName(){
// Mengembalikan nama hasil crafting
    return this->resultName;
}
void Recipe::setResultName(string name){
// Mengubah nama hasil crafting menjadi name
    this->resultName = name;
}

const int Recipe::getResultQuantity(){
// Mengembalikan jumlah hasil crafting
    return this->resultQuantity;
}
void Recipe::setResultQuantity(int quantity){
// Mengubah jumlah hasil crafting menjadi quantity
    this->resultQuantity = quantity;
}