// sample main file, replace this with your own code
#include <iostream>
#include <fstream>
#include <string>

#include "./header/Inventory.hpp"
#include "./header/Export.hpp"
#include "./header/RecipeList.hpp"
#include "./header/ItemList.hpp"

using namespace std;

int main()
{
  ItemList itemList("./config/item.txt");
  RecipeList recipeList("./config/recipe");
  Inventory inventory;
  Crafting craftTable;

  // sample interaction
  string command;
  while (cin >> command)
  {
    if (command == "EXPORT")
    {
      string fileName;
      cin >> fileName;
      Export ekspor(fileName, &inventory);

      cout << "Exported" << endl;
    }
    else if (command == "SHOW")
    {
      cout << "CRAFTING TABLE" << endl;
      craftTable.showCraftTable();
      cout << endl;
      cout << "INVENTORY" << endl;
      inventory.showInventory();
    }
    else if (command == "GIVE")
    {
      string itemName;
      int itemQty;
      cin >> itemName >> itemQty;
      inventory.give(itemName, itemQty, itemList);
    }
    else if (command == "DISCARD")
    {
      string inventorySlotID;
      int itemQty;
      cin >> inventorySlotID >> itemQty;
      inventory.discard(inventorySlotID, itemQty);
    }
    else if (command == "MOVE")
    {
      string slotSrc;
      int slotQty;
      // need to handle multiple destinations
      cin >> slotSrc >> slotQty;
      string target;
      int row, col;
      if (slotSrc[0] == 'I')
      {
        for (int i = 0; i < slotQty; i++)
        {
          cin >> target;
          row = (target[1] - '0') / 3;
          col = (target[1] - '0') % 3;
          if (target[0] == 'C')
          {
            craftTable.addItem(inventory.get_items()[slotSrc[1] - '0'], row, col);
            if (inventory.get_items()[slotSrc[1] - '0']->getType() == "TOOL")
            {
              // inventory.deleteItem(slotSrc[1] - '0'); INI GABISA
            }
            else
            {
              inventory.get_items()[slotSrc[1] - '0']->addQuantity(-1);
              if (inventory.get_items()[slotSrc[1] - '0']->getQuantity() == 0)
              {
                // inventory.deleteItem(slotSrc[1] - '0'); INI GABISA
              }
            }
            cout
                << inventory.get_items()[slotSrc[1] - '0']->getName() << " Berhasil ditambahkan ke Crafting Table slot ke-" << target[1] - '0' << endl;
          }
          else if (target[0] == 'I')
          {
            inventory.move(slotSrc, target);
          }
        }
      }
      else if (slotSrc[0] == 'C')
      {
        cin >> target;
        row = (slotSrc[1] - '0') / 3;
        col = (slotSrc[1] - '0') % 3;
        inventory.addItem(target[1] - '0', craftTable.getItem(row, col)->getName(), 1, itemList);
        craftTable.discardItem(row, col);
        cout << "Item berhasil dipindahkan" << endl;
      }
    }
    else if (command == "USE")
    {
      string inventorySlotID;
      cin >> inventorySlotID;
      inventory.use(inventorySlotID);
    }
    else if (command == "CRAFT")
    {
      if (craftTable.isAllTheSameTool() != "")
      {
        string itemName = craftTable.isAllTheSameTool();
        int durabilitySum = craftTable.durabilitySum();
        if (durabilitySum > 10)
        {
          inventory.give(itemName, 1, itemList);
        }
        else
        {
          for (int i = 0; i < INVENTORY_SLOT; i++)
          {
            if (inventory.isEmptySlot(i))
            {
              inventory.addItem(i, itemName, 1, itemList);
              inventory.get_items()[i]->setDurability(durabilitySum);
              break;
            }
          }
        }
      }
      else
      {
        tuple<string, int> a = recipeList.searchCraftableItem(craftTable);
        if (get<0>(a) != "NONE")
        {
          craftTable.resetCraftTable();
          inventory.give(get<0>(a), get<1>(a), itemList);
        }
        else
        {
          cout << "Tidak ada item yang dapat dibuat sesuai Crafting Table!" << endl;
        }
      }
    }
    else if (command == "EXIT")
    {
      break;
    }
    else
    {
      // todo
      cout << "Invalid command" << endl;
    }
  }
  return 0;
}