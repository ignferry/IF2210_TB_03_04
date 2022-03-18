#ifndef __RECIPE_LIST_HPP__
#define __RECIPE_LIST_HPP__

#include "Recipe.hpp"
#include "Crafting.hpp"
#include <vector>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <tuple>

class RecipeList {
    private:
        vector<Recipe> recipes;
    public:
        // CONSTRUCTOR
        RecipeList();
        // Default constructor
        RecipeList(string directory);
        // Constructor yang langsung mengisi vector recipes sesuai dengan konfigurasi pada directory

        // CCTOR
        RecipeList(RecipeList& rl);

        void setRecipesConfiguration(string directory);
        // Mengisi vector recipes sesuai dengan konfigurasi recipe pada directory

        Recipe searchRecipe(string itemName);
        // Mengembalikan recipe dengan nama itemName

        void printRecipe(string itemName);
        // Menampilkan recipe dengan nama itemName

        tuple<string, int> searchCraftableItem(Crafting &c);
        // Mencari nama item yang dapat di-craft dengan konfigurasi pada c
        // Jika tidak ada item yang dapat di-craft, mengembalikan NULL
};


#endif