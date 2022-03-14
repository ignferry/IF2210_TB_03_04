#include "../header/Load.hpp"
#include <fstream>
#include <iostream>

/* constructor */
Load::Load() {
    cout << "Loading..." << endl;
    this->item();
    this->print_item();
    cout << "Load succsesfull" << endl;
}
/* read configuration item and add to buffer_item */
void Load::item() {
    //cout << "aaa" << endl;
    string configPath = "./config";
    string itemConfigPath = configPath + "/item.txt";

    // read item from config file
    ifstream itemConfigFile(itemConfigPath);
    for(string line; getline(itemConfigFile, line);) {
        //cout << line << endl;
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
        buffer_item.push_back(item_info);
    }
}
/* print item in buffer_item */
void Load::print_item() {
    vector<array<string, 4>>::iterator it;
    for(it = buffer_item.begin(); it != buffer_item.end(); ++it) {
        for(int i = 0; i < 4; i++) {
            cout << (*it)[i] << " ";
        }
        cout << endl;
    }
}