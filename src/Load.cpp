#include "../header/Load.hpp"
#include <fstream>
#include <iostream>
#include <filesystem>

/* constructor */
Load::Load() {
    this->configPath = "./config";
    cout << "Loading..." << endl;
    this->read_item();
    this->print_item();
    this->read_recipe();
    this->print_recipe();
    cout << "Load succsesfull" << endl;
}
Load::Load(string load) {
    this->configPath = "./config";
    this->read_item();
    this->read_recipe();
}
/* read configuration item and add to buffer_item */
void Load::read_item() {
    string itemConfigPath = this->configPath + "/item.txt";

    // read item from config file
    ifstream itemConfigFile(itemConfigPath);
    for(string line; getline(itemConfigFile, line);) {
        string word = "";
        array<string, 4> item_info;
        int i = 0;
        for(auto ch : line) {
            if(ch == ' ') {
                // add to array
                item_info[i] = word;
                word = "";
                i++;
            } else {
                word += ch;
            }
        }
        // add to array lastest word
        item_info[i] = word;
        i = 0;
        // add item info to buffer_item
        this->buffer_item.push_back(item_info);
    }
}
/* print item in buffer_item */
void Load::print_item() {
    vector<array<string, 4>>::iterator it;
    for(it = this->buffer_item.begin(); it != this->buffer_item.end(); ++it) {
        for(int i = 0; i < 4; i++) {
            cout << (*it)[i] << " ";
        }
        cout << endl;
    }
}
/* return info ke-i from item ke-n*/
/* i = 0 for ID
i = 1 for name
i = 2 for type
i = 3 for tool/nontool */
string Load::get_info_item(int n, int i) const {
    return this->buffer_item[n][i];
}
/* read configuration recipe and add to buffer_recipe*/
void Load::read_recipe() {
    string recipeConfigPath = this->configPath + "/recipe";
    for (const auto &entry : filesystem::directory_iterator(recipeConfigPath)) {
        ifstream itemConfigFile(entry.path());
        vector<vector<string>> recipe;
        for(string line; getline(itemConfigFile, line);) {
            string word = "";
            vector<string> recipe_info;
            for(auto ch : line) {
                if(ch == ' ') {
                    // add to vector
                    recipe_info.push_back(word);
                    word = "";
                } else {
                    word += ch;
                }
            }
            // add to vector lastest word
            recipe_info.push_back(word);
            // add recipe info to recipe
            recipe.push_back(recipe_info);
        }
        // add recipe to buffer_recipe
        this->buffer_recipe.push_back(recipe);
    }
}
/* print recipe in buffer_recipe */
void Load::print_recipe() {
    for(int i = 0; i < this->buffer_recipe.size(); i++) {
        cout << "resep ke-" << i + 1 << endl;
        for(int j = 0; j < get_row_recipe(i); j++) {
            for(int k = 0; k < get_col_recipe(i); k++) {
                cout << this->get_configuration_recipe(i)[j][k];
                if(k != get_col_recipe(i) - 1) {
                    cout << " "; 
                } else {
                    cout << endl;
                }
            }
        }
        cout << "menghasilkan " << get_amount_result_recipe(i) << " " << get_result_recipe(i) << endl;
        cout << "============================" << endl;
    }
}
/* return row from recipe ke-n*/
int Load::get_row_recipe(int n) const {
    return stoi(this->buffer_recipe[n][0][0]);
}
/* return column from recipe ke-n*/
int Load::get_col_recipe(int n) const {
    return stoi(this->buffer_recipe[n][0][1]);
}
/* return vector configuration from recipe ke-n*/
vector<vector<string>> Load::get_configuration_recipe(int n) const {
    vector<vector<string>> configuration;
    for(int i = 0; i < get_row_recipe(n); i++) {
        configuration.push_back(this->buffer_recipe[n][1 + i]);
    }
    return configuration;
}
/* return result crafting from recipe ke-n*/
string Load::get_result_recipe(int n) const {
    return this->buffer_recipe[n][get_row_recipe(n) + 1][0];
}
/* return amount result from recipe ke-n*/
int Load::get_amount_result_recipe(int n) const {
    return stoi(this->buffer_recipe[n][get_row_recipe(n) + 1][1]);
}

int Load::getID(string name) {
    vector<array<string, 4>>::iterator it;
    for (it = this->buffer_item.begin(); it != this->buffer_item.end(); it++) {
        if ((*it)[1] == name) {
            break;
        }
    }
    return stoi((*it)[0]);
}

string Load::getType(string name) {
    vector<array<string, 4>>::iterator it;
    for (it = this->buffer_item.begin(); it != this->buffer_item.end(); it++) {
        if ((*it)[1] == name) {
            break;
        }
    }
    return (*it)[3];
}