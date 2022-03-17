#include "../header/RecipeList.hpp"

// CONSTRUCTOR
RecipeList::RecipeList() {}
// Default constructor


RecipeList::RecipeList(string directory) {
// Constructor yang langsung mengisi vector recipes sesuai dengan konfigurasi pada directory
    this->setRecipesConfiguration(directory);
}


// CCTOR
RecipeList::RecipeList(RecipeList& rl) {
    for (auto itr : rl.recipes) {
        Recipe r(itr);
        this->recipes.push_back(r);
    }
}

void RecipeList::setRecipesConfiguration(string directory) {
// Mengisi vector recipes sesuai dengan konfigurasi recipe pada directory
    for (const auto &entry : filesystem::directory_iterator(directory)) {
        // Iterasi file
        ifstream recipeConfigFile(entry.path());
        
        int row, col;
        string line;

        // Set jumlah baris dan kolom
        getline(recipeConfigFile, line);
        stringstream lineStream(line);
        lineStream >> row >> col;

        Recipe r(row, col);

        // Set ingredients
        for (int i = 0; i < row; i++) {
            getline(recipeConfigFile, line);
            stringstream lineStream2(line);
            for (int j = 0; j < col; j++) {
                string ingredient;
                lineStream2 >> ingredient;
                r.setIngredientAt(ingredient, i, j);
            }
        }

        // Set nama dan jumlah hasil
        string resultName;
        int resultQuantity;
        getline(recipeConfigFile, line);
        stringstream lineStream3(line);
        lineStream3 >> resultName >> resultQuantity;
        r.setResultName(resultName);
        r.setResultQuantity(resultQuantity);

        this->recipes.push_back(r);
    }
}

Recipe RecipeList::searchRecipe(string itemName){
// Mengembalikan recipe dengan nama itemName
    Recipe r;
    vector<Recipe>::iterator it = this->recipes.begin();
    for (auto itr : this->recipes) {
        if (itr.getResultName() == itemName) {
            Recipe r(itr);
            return r;
        }
    }
    return r;
}

void RecipeList::printRecipe(string itemName) {
// Menampilkan recipe dengan nama itemName
// Jika tidak ditemukan, tidak melakukan apapun
    vector<Recipe>::iterator it = this->recipes.begin();
    while (it != this->recipes.end() && it->getResultName() != itemName) {
        it++;
    }
    if (it != this->recipes.end()) {
        it->printRecipe();
    }
}

tuple<string, int> RecipeList::searchCraftableItem(Crafting c) {
// Mencari nama item yang dapat di-craft dengan konfigurasi pada c
// Jika tidak ada item yang dapat di-craft, mengembalikan NULL
    for (auto itr : this->recipes) {
        if (c.configurationCheck(itr)) {
            return make_tuple(itr.getResultName(), itr.getResultQuantity());
        }
    }
}