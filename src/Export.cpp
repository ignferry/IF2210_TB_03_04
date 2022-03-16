#include "../header/Export.hpp"
#include <fstream>

Export::Export(string fileName, Inventory *inventory) : fileName(fileName) {
    this->outputPath = "./tests";
    this->inventory = inventory;
    this->out();
}

void Export::out() {
    this->outputPath += "/" + fileName;
    ofstream outputFile(outputPath);
    outputFile << "halo gan" << endl;
    outputFile << "6:1" << endl;
}