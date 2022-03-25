#include "../header/Exception.hpp"

NoSuchItemException::NoSuchItemException(string itemName) {
    this->itemName = itemName;
}

const string NoSuchItemException::what() {
    return "Tidak ditemukan item dengan nama " + this->itemName + "\n";
}

SlotEmptyException::SlotEmptyException(string slotName) {
    this->slotName = slotName;
}

const string SlotEmptyException::what() {
    return "Slot " + slotName + " kosong\n";
}

OutOfInventoryBoundsException::OutOfInventoryBoundsException(int index) {
    this->index = index;
}

const string OutOfInventoryBoundsException::what() {
    return "Tidak ada slot inventory I" + to_string(this->index) + ". Slot yang tersedia adalah I0-I26\n";
}

OutOfCraftingBoundsException::OutOfCraftingBoundsException(int index) {
    this->index = index;
}

const string OutOfCraftingBoundsException::what() {
    return "Tidak ada slot crafting C" + to_string(this->index) + ". Slot yang tersedia adalah C0-C8\n";
}

const string InventoryFullException::what() {
    return "Ruang inventory tidak cukup untuk mengeksekusi command\n";
}