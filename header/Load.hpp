#ifndef __LOAD_HPP__
#define __LOAD_HPP__
#include <vector>
#include <array>
using namespace std;

class Load {
    private:
        /* vector that contain array size 4 for saving the result of reading item configuration */
        /* example
            [["1", "OAK_LOG", "LOG", "NONTOOL"],
             ["2", "SPURCE_LOG", "LOG", "NONTOOL"],
             ["3", "BIRCH_LOG", "LOG", "NONTOOL"]] */
        vector<array<string, 4>> buffer_item;
    public:
        /* constructor */
        Load();
        /* read configuration item and add to buffer_item */
        void item();
        /* print item in buffer_item */
        void print_item();
        /* return info ke-i from item ke-n*/
        string get_info_item(int n, int i);
};

#endif