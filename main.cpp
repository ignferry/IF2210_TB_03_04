// sample main file, replace this with your own code
#include <iostream>
#include <fstream>
#include <string>

#include "./header/Inventory.hpp"
#include "./header/Export.hpp"
#include "./header/RecipeList.hpp"
#include "./header/ItemException.hpp"
#include "./header/ItemList.hpp"
#include "./header/Pair.hpp"

using namespace std;

int main()
{
  ItemList itemList("./config/item.txt");
  RecipeList recipeList("./config/recipe");
  Inventory inventory;
  Crafting craftTable;

  // sample interaction
  string stuff1(226, '#');
  string stuff2(42, '-');
  string stuff3(97, ' ');
  string stuff4(75, ' ');
  string stuff5(99, ' ');

  cout << stuff3 << "!!! WELCOME TO MINECRAFT LITE !!!" << endl;
  cout << stuff1 << endl;
  cout << "+" << stuff2 << "+" << endl;
  cout << "| COMMAND : ";
  string command;
  while (cin >> command)
  {
    cout << "+" << stuff2 << "+" << endl;
    if (command == "EXPORT")
    {
      string fileName;
      cin >> fileName;
      Export ekspor(fileName, &inventory);

      cout << "Semua item pada inventory berhasil di export ke file " << fileName << endl;
    }
    else if (command == "SHOW")
    {
      cout << stuff4 << "CRAFTING" << endl;
      craftTable.showCraftTable();
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
      if (inventorySlotID.at(0) == 'I') {
        inventory.discard(inventorySlotID, itemQty);
      } else {
        cout << "Masukan inventory slot ID tidak valid" << endl;
      }
    }
    else if (command == "MOVE")
    {
      string slotSrc;
      int slotQty;
      cin >> slotSrc >> slotQty;
      int slotInt = stoi(slotSrc.substr(1, slotSrc.length()));
      string target;
      int row, col;
      if (slotSrc[0] == 'I')
      {
        if (slotQty > 1) {
          for (int i = 0; i < slotQty; i++)
          {
            cin >> target;
            int qty;
            cin >> qty;
            row = (target[1] - '0') / 3;
            col = (target[1] - '0') % 3;

              craftTable.addItem(inventory.get_items()[slotInt], row, col, qty);
              cout << qty << " "
                  << inventory.get_items()[slotInt]->getName() << " berhasil ditambahkan ke Crafting Table slot ke-" << target[1] - '0' << endl;
              if (inventory.get_items()[slotInt]->getType() == "TOOL")
              {
                inventory.deleteItem(slotInt);
              }
              else
              {
                inventory.get_items()[slotInt]->addQuantity(-1 * qty);
                if (inventory.get_items()[slotInt]->getQuantity() == 0)
                {
                  inventory.deleteItem(slotInt);
                }
              }

          }
        } else if (slotQty == 1) {
          cin >> target;
          if (target.at(0) == 'I') {
            inventory.move(slotSrc, target);
          } else {
            cout << "Masukan slot ID dest tidak valid" << endl;
          }
        }
      }
      else if (slotSrc[0] == 'C')
      {
        cin >> target;
        row = (slotInt) / 3;
        col = (slotInt) % 3;
        int targetInt = stoi(target.substr(1, target.length()));
        if (inventory.isEmptySlot(targetInt))
        {
          inventory.addItem(targetInt, craftTable.getItem(row, col)->getName(), 1, itemList);
        }
        else if (inventory.get_items()[targetInt]->getName() == craftTable.getItem(row, col)->getName())
        {
          inventory.get_items()[targetInt]->addQuantity(1);
        }
        craftTable.getItem(row, col)->addQuantity(-1);
        if (craftTable.getItem(row, col)->getQuantity() == 0)
        {
          craftTable.discardItem(row, col);
        }
        cout << "Item berhasil dipindahkan" << endl;
      }
      else
      {
        cout << "Masukan slot ID src tidak valid" << endl;
      }
    }
    else if (command == "USE")
    {
      string inventorySlotID;
      cin >> inventorySlotID;
      if (inventorySlotID.at(0) == 'I') {
        inventory.use(inventorySlotID);
      } else {
        cout << "Masukan inventory slot ID tidak valid" << endl;
      }
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
        Pair<string, int> a = recipeList.searchCraftableItem(craftTable);
        if (a.getFirst() != "NONE")
        {
          // craftTable.resetCraftTable();
          craftTable.substractQtyCraftTable();
          inventory.give(a.getFirst(), a.getSecond(), itemList);
        }
        else
        {
          cout << "Tidak ada item yang dapat dibuat sesuai Crafting Table!" << endl;
        }
      }
    }
    else if (command == "EXIT")
    {
      cout << stuff1 << endl;
      cout << stuff5 << "!!! THANK YOU FOR PLAYING !!!" << endl;
      break;
    }
    else
    {
      // todo
      cout << "!!! INVALID COMMAND !!!" << endl;
    }
    cout << stuff1 << endl;
    cout << "+" << stuff2 << "+" << endl;
    cout << "| COMMAND : ";
  }
  return 0;
}