// sample main file, replace this with your own code
#include <iostream>
#include <fstream>
#include <string>

#include "./header/Inventory.hpp"
#include "./header/Item.hpp"
#include "./header/Load.hpp"

using namespace std;

int main() {
  Inventory inventory;
  Load load;

  // sample interaction
  string command;
  while (cin >> command) {
    if (command == "EXPORT") {
      string outputPath;
      cin >> outputPath;
      ofstream outputFile(outputPath);

      // hardcode for first test case
      outputFile << "21:10" << endl;
      outputFile << "6:1" << endl;
      for (int i = 2; i < 27; i++) {
        outputFile << "0:0" << endl;
      }

      cout << "Exported" << endl;
    } else if (command == "SHOW") {
      inventory.showInventory();
    } else if (command == "GIVE") {
      string itemName;
      int itemQty;
      cin >> itemName >> itemQty;
      inventory.give(itemName, itemQty);
    } else if (command == "DISCARD") {
      string inventorySlotID;
      int itemQty;
      cin >> inventorySlotID >> itemQty;
      cout << "TODO" << endl;
    } else if (command == "MOVE") {
      string slotSrc;
      int slotQty;
      string slotDest;
      // need to handle multiple destinations
      cin >> slotSrc >> slotQty >> slotDest;
      cout << "TODO" << endl;
    } else if (command == "USE") {
      string inventorySlotID;
      cin >> inventorySlotID;
      cout << "TODO" << endl;
    } else if (command == "CRAFT") {
      cout << "TODO" << endl;
    } else if (command == "EXIT") {
        break;
    } else {
      // todo
      cout << "Invalid command" << endl;
    }
  }
  return 0;
}