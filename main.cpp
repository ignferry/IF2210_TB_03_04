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
      cout << stuff1 << endl;
      cout << "+" << stuff2 << "+" << endl;
      cout << "| COMMAND : ";
    }
    else if (command == "SHOW")
    {
      cout << stuff4 << "CRAFTING" << endl;
      craftTable.showCraftTable();
      cout << "INVENTORY" << endl;
      inventory.showInventory();
      cout << stuff1 << endl;
      cout << "+" << stuff2 << "+" << endl;
      cout << "| COMMAND : ";
    }
    else if (command == "GIVE")
    {
      string itemName;
      int itemQty;
      cin >> itemName >> itemQty;
      inventory.give(itemName, itemQty, itemList);
      cout << stuff1 << endl;
      cout << "+" << stuff2 << "+" << endl;
      cout << "| COMMAND : ";
    }
    else if (command == "DISCARD")
    {
      string inventorySlotID;
      int itemQty;
      cin >> inventorySlotID >> itemQty;
      inventory.discard(inventorySlotID, itemQty);
      cout << stuff1 << endl;
      cout << "+" << stuff2 << "+" << endl;
      cout << "| COMMAND : ";
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
        for (int i = 0; i < slotQty; i++)
        {
          cin >> target;
          int qty;
          cin >> qty;
          row = (target[1] - '0') / 3;
          col = (target[1] - '0') % 3;
          if (target[0] == 'C')
          {
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
          else if (target[0] == 'I')
          {
            inventory.move(slotSrc, target);
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
      cout << stuff1 << endl;
      cout << "+" << stuff2 << "+" << endl;
      cout << "| COMMAND : ";
    }
    else if (command == "USE")
    {
      string inventorySlotID;
      cin >> inventorySlotID;
      inventory.use(inventorySlotID);
      cout << stuff1 << endl;
      cout << "+" << stuff2 << "+" << endl;
      cout << "| COMMAND : ";
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
          // craftTable.resetCraftTable();
          craftTable.substractQtyCraftTable();
          inventory.give(get<0>(a), get<1>(a), itemList);
        }
        else
        {
          cout << "Tidak ada item yang dapat dibuat sesuai Crafting Table!" << endl;
        }
      }
      cout << stuff1 << endl;
      cout << "+" << stuff2 << "+" << endl;
      cout << "| COMMAND : ";
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
      cout << stuff1 << endl;
      cout << "+" << stuff2 << "+" << endl;
      cout << "| COMMAND : ";
    }
  }
  return 0;
}