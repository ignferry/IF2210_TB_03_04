#ifndef _ITEM_HPP_
#define _ITEM_HPP_

#include <iostream>
using namespace std;
#define MAX_DURABILITY 10

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
        virtual ~Item();

        // Setter Getter
        int getID() const;
        void setID(int id);

        string getName() const;
        void setName(string name);

        string getType() const;
        void setType(string type);
        
        int getQuantity() const;
        virtual void setQuantity(int quantity) = 0;

        // Modifier
        virtual void addQuantity(int quantity) = 0;
        virtual void subtractQuantity(int quantity) = 0;

        // Comparison
        virtual bool operator==(const Item& item);
};

class Non_Tool : public Item {
    private:
        string Variant;
    public:
        // Constructor
        Non_Tool();
        Non_Tool(int ID, string name, int Quantity, string Variant);
        bool operator==(const Non_Tool& nt);
        virtual ~Non_Tool();

        // Setter Getter
        string getVariant() const;
        void setVariant(string Variant);

        // Modifier
        void setQuantity(int quantity);
        void addQuantity(int quantity);
        void subtractQuantity(int quantity);
};

class Tool : public Item {
    private:
        int Durability;
    public:
        // Constructor
        Tool();
        Tool(int ID, string name, int Durability);
        virtual ~Tool();

        // Setter Getter
        void setQuantity(int quantity);
        void addQuantity(int quantity);
        void subtractQuantity(int quantity);

        int getDurability() const;
        void setDurability(int durability);

        // Modifier
        void addDurability(int durability);
        void subtractDurability(int durability);
        bool operator==(const Tool& t);
};

#endif