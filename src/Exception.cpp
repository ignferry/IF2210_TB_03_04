#include "../header/Exception.hpp"

const string Non_Tool_QuantityException::what()
{
    return "Jumlah item Non_Tool harus antara 0 s.d 64 (inklusif)";
}

const string Tool_QuantityException::what()
{
    return "Jumlah item Tool harus antara 0 s.d 1 (inklusif)";
}

const string Tool_DurabilityException::what()
{
    return "Durability item harus antara 0 s.d 10 (inklusif)";
}

const string Item_No_DurabilityException::what()
{
    return "Kelas Item tidak memiliki atribut Durability, adanya di kelas Tool";
}

const string Item_No_QuantityException::what()
{
    return "Kelas Item tidak memiliki atribut Quantity, adanya di kelas Non_Tool";
}

const string Item_No_VariantException::what()
{
    return "Kelas Item tidak memiliki atribut Variant, adanya di kelas Non_Tool";
}

NoSuchItemException::NoSuchItemException(string itemName)
{
    this->itemName = itemName;
}

const string NoSuchItemException::what()
{
    return "Tidak ada item dengan nama " + this->itemName + " dalam permainan ini\n";
}

SlotEmptyException::SlotEmptyException(string slotName)
{
    this->slotName = slotName;
}

const string SlotEmptyException::what()
{
    return "Slot " + slotName + " kosong\n";
}

OutOfInventoryBoundsException::OutOfInventoryBoundsException(int index)
{
    this->index = index;
}

const string OutOfInventoryBoundsException::what()
{
    return "Tidak ada slot inventory I" + to_string(this->index) + ". Slot yang tersedia adalah I0-I26\n";
}

OutOfCraftingBoundsException::OutOfCraftingBoundsException(int index)
{
    this->index = index;
}

const string OutOfCraftingBoundsException::what()
{
    return "Tidak ada slot crafting C" + to_string(this->index) + ". Slot yang tersedia adalah C0-C8\n";
}

const string InventoryFullException::what()
{
    return "Ruang inventory tidak cukup untuk mengeksekusi command\n";
}

CraftingSlotFillWithDifferentItem::CraftingSlotFillWithDifferentItem(int index)
{
    this->index = index;
}

const string CraftingSlotFillWithDifferentItem::what()
{
    return "Slot C" + to_string(this->index) + " sudah berisi item lain\n";
}

CraftingSlotEmpty::CraftingSlotEmpty(int index)
{
    this->index = index;
}

const string CraftingSlotEmpty::what()
{
    return "Slot C" + to_string(this->index) + " kosong\n";
}