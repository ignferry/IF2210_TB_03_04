#include "../header/Export.hpp"
#include "../header/Item.hpp"
#include <fstream>

Export::Export(string fileName, Inventory *inventory) : fileName(fileName) {
    this->outputPath = "./tests"; // apakah selalu di test?
    this->inventory = inventory;
    this->out();
}

void Export::out() {
    this->outputPath += "/" + fileName;
    ofstream outputFile(outputPath);
    int i = 0;
    Item** items = inventory->get_items();
    while(i < 27) {
        if(!(inventory->isEmptySlot(i))) {
            outputFile << items[i]->getID() << ":";
            if(items[i]->getType() == "TOOL") outputFile << items[i]->getDurability() << endl;
            else outputFile << items[i]->getQuantity() << endl;
        } else {
            outputFile << "0:0" << endl;
        }
        i++;
        
    }
}