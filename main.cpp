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
#include "./header/Exception.hpp"

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
    try
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
        if (inventorySlotID.at(0) == 'I')
        {
          inventory.discard(inventorySlotID, itemQty);
        }
        else
        {
          cout << "Masukan inventory slot ID tidak valid" << endl;
        }
      }
      else if (command == "MOVE")
      {
        string slotSrc;
        int slotQty;
        cin >> slotSrc >> slotQty;
        int slotInt = stoi(slotSrc.substr(1, slotSrc.length()));
        if (inventory.isEmptySlot(slotInt))
        {
          throw new SlotEmptyException(slotSrc);
        }
        string target;
        int row, col;
        if (slotSrc[0] == 'I')
        {
          for (int i = 0; i < slotQty; i++)
          {
            cin >> target;
            int targetInt = stoi(target.substr(1, target.length()));
            if (target.at(0) == 'I')
            {
              inventory.move(slotSrc, target);
            }
            else if (target.at(0) == 'C')
            {
              int qty;
              cin >> qty;
              row = (targetInt) / 3;
              col = (targetInt) % 3;
              craftTable.addItem(inventory.get_items()[slotInt], row, col, qty);
              cout << qty << " " << inventory.get_items()[slotInt]->getName() << " berhasil ditambahkan ke Crafting Table slot ke-" << target[1] - '0' << endl;
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
            else
            {
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
        if (inventorySlotID.at(0) == 'I')
        {
          inventory.use(inventorySlotID);
        }
        else
        {
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
            craftTable.substractQtyCraftTable();
            inventory.give(a.getFirst(), a.getSecond(), itemList);
          }
          else
          {
            cout << "Tidak ada item yang dapat dibuat sesuai Crafting Table!" << endl;
          }
        }
      }
      else if (command == "MULTIPLECRAFT")
      {
        Pair<string, int> a = recipeList.searchCraftableItem(craftTable);
        int qty = 0;
        if (a.getFirst() != "NONE")
        {
          qty++;
          craftTable.substractQtyCraftTable();
          Pair<string, int> b = recipeList.searchCraftableItem(craftTable);
          while (a.getFirst() == b.getFirst())
          {
            qty++;
            craftTable.substractQtyCraftTable();
            b = recipeList.searchCraftableItem(craftTable);
          }

          inventory.give(a.getFirst(), a.getSecond() * qty, itemList);
        }
        else
        {
          cout << "Tidak ada item yang dapat dibuat sesuai Crafting Table!" << endl;
        }
      }
      else if (command == "HELP")
      {
        cout << "1. SHOW" << endl;
        cout << "2. GIVE <ITEM_NAME> <ITEM_QTY>" << endl;
        cout << "3. DISCARD <INVENTORY_SLOT_ID> <ITEM_QTY>" << endl;
        cout << "4. MOVE <INVENTORY_SLOT_ID> N <CRAFTING_SLOT_ID_1> <ITEM_QTY_1> <CRAFTING_SLOT_ID_2> <ITEM_QTY_2> ... <CRAFTING_SLOT_ID_N> <ITEM_QTY_N>" << endl;
        cout << "5. MOVE <INVENTORY_SLOT_ID_SRC> 1 <INVENTORY_SLOT_ID_DEST>" << endl;
        cout << "6. MOVE <CRAFTING_SLOT_ID> 1 <INVENTORY_SLOT_ID>" << endl;
        cout << "7. USE <INVENTORY_SLOT_ID>" << endl;
        cout << "8. CRAFT" << endl;
        cout << "9. MULTIPLECRAFT" << endl;
        cout << "10. EXPORT <NAMA_FILE>" << endl;
        cout << "11. EXIT" << endl;
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
        cout << "Masukkan command HELP untuk melihat daftar command yang ada dalam program ini" << endl;
      }
    }
    catch (Exception *e)
    {
      cout << e->what();
    }
    cout << stuff1 << endl;
    cout << "+" << stuff2 << "+" << endl;
    cout << "| COMMAND : ";
  }
  return 0;
}