#ifndef _Exce_H_
#define _Exce_H_

#include <iostream>
#include <exception>

class ItemException {
    protected:
        virtual const char* what() = 0;
};

// class Item_TypeException : public ItemException {
//     public:
//         const char* what(){
//             return "Hanya ada 2 tipe item : \"TOOL\" atau \"NONTOOL\"";
//         }
// };

class Non_Tool_QuantityException : public ItemException {
    public:
        const char* what(){
            return "Jumlah item Non_Tool harus antara 0 s.d 64 (inklusif)";
        }
};

class Tool_QuantityException : public ItemException {
    public:
        const char* what(){
            return "Jumlah item Tool harus antara 0 s.d 1 (inklusif)";
        }
};

class Tool_DurabilityException : public ItemException {
    public:
        const char* what(){
            return "Durability item harus antara 0 s.d 10 (inklusif)";
        }
};

class Item_No_DurabilityException : public ItemException {
    public:
        const char* what(){
            return "Kelas Item tidak memiliki atribut durability, adanya di kelas Tool";
        }
};

class Item_No_QuantityException : public ItemException {
    public:
        const char* what(){
            return "Kelas Item tidak memiliki atribut Quantity, adanya di kelas Non_Tool";
        }
};

class Item_No_VariantException : public ItemException {
    public:
        const char* what(){
            return "Kelas Item tidak memiliki atribut Variant, adanya di kelas Non_Tool";
        }
};

#endif