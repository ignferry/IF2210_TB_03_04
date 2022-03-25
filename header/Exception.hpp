#ifndef __EXCEPTION_HPP__
#define __EXCEPTION_HPP__

#include <string>

using namespace std;

class Exception
{
public:
    virtual const string what() = 0;
};

class Non_Tool_QuantityException : public Exception {
    public:
        const string what();
};

class Tool_QuantityException : public Exception {
    public:
        const string what();
};

class Tool_DurabilityException : public Exception {
    public:
        const string what();
};

class Item_No_DurabilityException : public Exception {
    public:
        const string what();
};

class Item_No_QuantityException : public Exception {
    public:
        const string what();
};

class Item_No_VariantException : public Exception {
    public:
        const string what();
};

class NoSuchItemException : public Exception
{
private:
    string itemName;

public:
    NoSuchItemException(string itemName);
    const string what();
};

class SlotEmptyException : public Exception
{
private:
    string slotName;

public:
    SlotEmptyException(string slotName);
    const string what();
};

class OutOfInventoryBoundsException : public Exception
{
private:
    int index;

public:
    OutOfInventoryBoundsException(int index);
    const string what();
};

class OutOfCraftingBoundsException : public Exception
{
private:
    int index;

public:
    OutOfCraftingBoundsException(int index);
    const string what();
};

class InventoryFullException : public Exception
{
    const string what();
};

class CraftingSlotFillWithDifferentItem : public Exception
{
private:
    int index;

public:
    CraftingSlotFillWithDifferentItem(int index);
    const string what();
};

#endif