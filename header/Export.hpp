#ifndef __EXPORT_HPP__
#define __EXPORT_HPP__
#include <string>
#include <iostream>
#include "Inventory.hpp"

using namespace std;

class Export {
    private:
        string outputPath;
        string fileName;
        Inventory* inventory; 
    public:
        Export(string fileName, Inventory* inventory);
        void out();
};

#endif