// sample main file, replace this with your own code
#include <iostream>
#include <fstream>
#include <string>

#include "./header/Inventory.hpp"
#include "./header/Item.hpp"
#include "./header/Load.hpp"
#include "./header/Export.hpp"

using namespace std;

int main() {
  Load load;
  Inventory inventory(&load);

  // sample interaction
  string command;
  while (cin >> command) {
    if (command == "EXPORT") {
      string fileName;
      cin >> fileName;
      Export ekspor(fileName, &inventory);

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
      inventory.discard(inventorySlotID, itemQty);
    } else if (command == "MOVE") {
      string slotSrc;
      int slotQty;
      // need to handle multiple destinations
      cin >> slotSrc >> slotQty;
      string slotDest[slotQty];
      for (int i = 0; i < slotQty; i++) {
        cin >> slotDest[i];
      }
      inventory.move(slotSrc, slotDest[0]);
    } else if (command == "USE") {
      string inventorySlotID;
      cin >> inventorySlotID;
      inventory.use(inventorySlotID);
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