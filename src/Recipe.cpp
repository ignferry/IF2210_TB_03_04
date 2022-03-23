#include "../header/Recipe.hpp"

// CONSTRUCTOR
Recipe::Recipe()
{
    // Default ctor Recipe
    this->row = 3;
    this->col = 3;
    this->ingredients = new string *[3];
    for (int i = 0; i < this->row; i++)
    {
        this->ingredients[i] = new string[3];
        for (int j = 0; j < 3; j++)
        {
            this->ingredients[i][j] = "-";
        }
    }
    this->resultName = "";
    this->resultQuantity = 0;
}

Recipe::Recipe(int row, int col)
{
    // Custom ctor Recipe dengan row dan col sesuai dengan parameter
    this->row = row;
    this->col = col;
    this->ingredients = new string *[this->row];
    this->ingredients = new string *[3];
    for (int i = 0; i < this->row; i++)
    {
        this->ingredients[i] = new string[3];
        for (int j = 0; j < 3; j++)
        {
            this->ingredients[i][j] = "-";
        }
    }
    this->resultName = "";
    this->resultQuantity = 0;
}

// CCTOR
Recipe::Recipe(const Recipe &r)
{
    // cctor Recipe
    this->row = r.row;
    this->col = r.col;
    this->resultName = r.resultName;
    this->resultQuantity = r.resultQuantity;
    this->ingredients = new string *[3];
    for (int i = 0; i < 3; i++)
    {
        this->ingredients[i] = new string[3];
        for (int j = 0; j < 3; j++)
        {
            this->ingredients[i][j] = "-";
        }
    }
    for (int i = 0; i < this->row; i++)
    {
        for (int j = 0; j < this->col; j++)
        {
            this->ingredients[i][j] = r.ingredients[i][j];
        }
    }
}

// DESTRUCTOR
Recipe::~Recipe()
{
    for (int i = 0; i < this->row; i++)
    {
        delete[] this->ingredients[i];
    }
    delete[] this->ingredients;
}

// GETTER DAN SETTER
const int Recipe::getRow()
{
    // Mengembalikan nilai atribut row
    return this->row;
}
void Recipe::setRow(int row)
{
    // Mengubah atribut row pada suatu objek Recipe sesuai dengan parameter row
    this->row = row;
}

const int Recipe::getCol()
{
    // Mengembalikan nilai atribut col
    return this->col;
}
void Recipe::setCol(int col)
{
    // Mengubah atirbut col pada suatu objek Recipe sesuai dengan parameter col
    this->col = col;
}

const string Recipe::getIngredientsAt(int row, int col)
{
    // Mengembalikan nama ingredient pada koordinat (row, col)
    return this->ingredients[row][col];
}
void Recipe::setIngredientAt(string name, int row, int col)
{
    // Mengubah nama ingredient pada koordinat (row, col) menjadi name
    this->ingredients[row][col] = name;
}

const string Recipe::getResultName()
{
    // Mengembalikan nama hasil crafting
    return this->resultName;
}
void Recipe::setResultName(string name)
{
    // Mengubah nama hasil crafting menjadi name
    this->resultName = name;
}

const int Recipe::getResultQuantity()
{
    // Mengembalikan jumlah hasil crafting
    return this->resultQuantity;
}
void Recipe::setResultQuantity(int quantity)
{
    // Mengubah jumlah hasil crafting menjadi quantity
    this->resultQuantity = quantity;
}

void Recipe::printRecipe()
{
    // Menampilkan informasi dari recipe
    cout << "Untuk membuat " << this->resultQuantity << " buah " << this->resultName << " dibutuhkan: " << endl;
    for (int i = 0; i < this->row; i++)
    {
        for (int j = 0; j < this->col; j++)
        {
            cout << ingredients[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}