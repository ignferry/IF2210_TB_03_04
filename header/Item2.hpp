#ifndef _ITEM_HPP_
#define _ITEM_HPP_

#include <iostream>
using namespace std;

class Item {
    private:
        int ID;
        string Name;
        string Type;
        int Quantity;

    public:
        // Constructor
        Item();
        Item(int ID, string Name, string Type, int Quantity);

        // Setter Getter
        int getID() const;
        void setID(int id);

        string getName() const;
        void setName(string name);

        string getType() const;
        void setType(string type);
        
        int getQuantity() const;
        void setQuantity(int quantity);

        // Modifier
        void addQuantity(int quantity);
        void subtractQuantity(int quantity);

        // Comparison
        virtual bool operator==(const Item& item) = 0;
};

class Non_Tool : public Item {
    public:
        // Constructor
        Non_Tool();
        Non_Tool(int ID, string name, int Quantity);
        bool operator==(const Non_Tool& nt);
};

class Tool : public Item {
    private:
        int Durability;
    public:
        // Constructor
        Tool();
        Tool(int ID, string name, int Durability);

        // Setter Getter
        int getDurability() const;
        void setDurability(int quantity);

        // M0difier
        void addDurability(int durability);
        void subtractDurability(int durability);
        bool operator==(const Tool& t);
};

#endif