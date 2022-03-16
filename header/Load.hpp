#ifndef __LOAD_HPP__
#define __LOAD_HPP__
#include <vector>
#include <array>
#include <string>
using namespace std;

class Load {
    private:
        string configPath;
        /* vector that contain array size 4 for saving the result of reading item configuration */
        /* example
            [["1", "OAK_LOG", "LOG", "NONTOOL"],
             ["2", "SPURCE_LOG", "LOG", "NONTOOL"],
             ["3", "BIRCH_LOG", "LOG", "NONTOOL"]] */
        vector<array<string, 4>> buffer_item;
        /* vector that contain vector of string for saving the result of reading recipe configuration */
        /* example
            [[[3, 3], [STONE, STONE, -], [STONE, STICK, -], [-, STICK, -], [STONE_AXE, 1]],
             [[1 1], [BIRCH_LOG], [BIRCH_PLANK 4]],
             [[2 1], [PLANK], [PLANK], [STICK 4]]] */
        vector<vector<vector<string>>> buffer_recipe;
    public:
        /* constructor */
        Load();

        /* read configuration item and add to buffer_item */
        void read_item();
        /* print item in buffer_item */
        void print_item();
        /* return info ke-i from item ke-n */
        /* i = 0 for ID
           i = 1 for name
           i = 2 for type
           i = 3 for tool/nontool */
        string get_info_item(int n, int i) const;

        /* read configuration recipe and add to buffer_recipe*/
        void read_recipe();
        /* print recipe in buffer_recipe */
        void print_recipe();
        /* return row from recipe ke-n*/
        int get_row_recipe(int n) const;
        /* return column from recipe ke-n*/
        int get_col_recipe(int n) const;
        /* return vector configuration from recipe ke-n*/
        vector<vector<string>> get_configuration_recipe(int n) const;
        /* return result crafting from recipe ke-n*/
        string get_result_recipe(int n) const;
        /* return amount result from recipe ke-n*/
        int get_amount_result_recipe(int n) const;
        /* return item ID from item name */
        int getID(string name);
        /* return item type from item name */
        string getType(string name);
};

#endif