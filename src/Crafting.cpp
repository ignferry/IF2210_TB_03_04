#include "../header/Crafting.hpp"
#include <iostream>
#include <typeinfo>

using namespace std;

Crafting::Crafting()
{
    this->craftArr = new Item **[3];
    for (int i = 0; i < 3; i++)
    {
        this->craftArr[i] = new Item *[3];
        for (int j = 0; j < 3; j++)
        {
            this->craftArr[i][j] = nullptr;
        }
    }
    rowEff = 0;
    colEff = 0;
}

Crafting::Crafting(const Crafting &c)
{
    this->craftArr = new Item **[3];
    for (int i = 0; i < 3; i++)
    {
        this->craftArr[i] = new Item *[3];
        for (int j = 0; j < 3; j++)
        {
            this->craftArr[i][j] = c.craftArr[i][j];
        }
    }
    rowEff = c.rowEff;
    colEff = c.colEff;
}

Crafting::~Crafting()
{
    for (int i = 0; i < 3; i++)
    {
        delete[] this->craftArr[i];
    }
    delete[] this->craftArr;
}

void Crafting::checkRow()
{
    int row = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (this->craftArr[i][j] != NULL)
            {
                row++;
                break;
            }
        }
    }
    this->rowEff = row;
}

void Crafting::checkCol()
{
    int col = 0;
    for (int j = 0; j < 3; j++)
    {
        for (int i = 0; i < 3; i++)
        {
            if (this->craftArr[i][j] != NULL)
            {
                col++;
                break;
            }
        }
    }
    this->colEff = col;
}

int Crafting::getCol()
{
    return this->colEff;
}

int Crafting::getRow()
{
    return this->rowEff;
}

Item *Crafting::getItem(int row, int col)
{
    return this->craftArr[row][col];
}

bool Crafting::isSlotEmpty(int row, int col)
{
    return (this->craftArr[row][col] == NULL);
}

void Crafting::showCraftTable()
{
    string stuff5(75, ' ');
    cout << stuff5;
    for (int i = 0; i < 3; i++)
    {
        string stuff(24, '-');
        cout << "+" << stuff;
    }
    cout << "+" << endl;

    for (int i = 0; i < 3; i++)
    {
        cout << stuff5;
        for (int j = 0; j < 3; j++)
        {
            if (!this->isSlotEmpty(i, j))
            {
                cout << "|" << right << setw(16) << this->craftArr[i][j]->getName() << "/qty:" << left << setw(2) << this->craftArr[i][j]->getQuantity() << " ";
            }
            else
            {
                string stuff(22, ' ');
                cout << "| " << stuff << " ";
            }
        }
        cout << "|" << endl;
        cout << stuff5;
        for (int k = 0; k < 3; k++)
        {
            string stuff(24, '-');
            cout << "+" << stuff;
        }
        cout << "+" << endl;
    }
}

void Crafting::addItem(Item *I, int row, int col, int qty)
{
    if (row > 2 || row < 0 || col > 2 || col < 0)
    {
        throw new OutOfCraftingBoundsException(row * 3 + col);
    }
    if (I == nullptr)
    {
        this->craftArr[row][col] = nullptr;
    }
    else
    {
        if (isSlotEmpty(row, col))
        {
            this->craftArr[row][col] = I->deepCopy();
            this->craftArr[row][col]->addQuantity(qty - this->craftArr[row][col]->getQuantity());
        }
        else if (this->craftArr[row][col]->getName() == I->getName())
        {
            this->craftArr[row][col]->addQuantity(qty);
        }
        else
        {
            throw new CraftingSlotFillWithDifferentItem(row * 3 + col);
        }
    }
    this->checkCol();
    this->checkRow();
}

void Crafting::discardItem(int row, int col)
{
    delete craftArr[row][col];
    this->craftArr[row][col] = nullptr;
    this->checkCol();
    this->checkRow();
}

bool Crafting::operator==(Recipe r)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (this->craftArr[i][j] == NULL && r.getIngredientsAt(i, j) != "-")
            // SLOT CRAFTING TABLE KOSONG TETAPI SLOT RECIPE TIDAK KOSONG
            {
                return false;
            }
            else if (this->craftArr[i][j] != NULL && r.getIngredientsAt(i, j) == "-")
            // SLOT CRAFTING TABLE TIDAK KOSONG TETAPI SLOT RECIPE KOSONG
            {

                return false;
            }
            else if (this->craftArr[i][j] != NULL && r.getIngredientsAt(i, j) != "-") // SLOT CRAFTING TABLE DAN RECIPE TIDAK KOSONG
            {
                if (this->craftArr[i][j]->getVariant() != "-")
                // SLOT CRAFTING TABLE MEMILIKI VARIANT
                {
                    if (this->craftArr[i][j]->getVariant() != r.getIngredientsAt(i, j))
                    // MENGECEK VARIAN DARI SLOT CRAFTING TABLE DENGAN SLOT RECIPE DI KOLOM DAN BARIS YANG SESUAI
                    {
                        if (this->craftArr[i][j]->getName() != r.getIngredientsAt(i, j))
                        {
                            return false;
                        }
                    }
                }
                else if (this->craftArr[i][j]->getName() != r.getIngredientsAt(i, j))
                // SLOT CRAFTING TABLE TIDAK MEMILIKI VARIAN SEHINGGA YANG DICEK ADALAH NAMA ITEMNYA
                {
                    return false;
                }
            }
        }
    }
    return true;
}

bool Crafting::checkTranslation(Recipe r, int ver, int hor)
// VER BERARTI MENGGESER SETIAP ITEM DI SLOT SECARA VERTIKAL, POSITIF KEATAS DAN NEGATIF KEBAWAH
// HOR BERARTI MENGGESER SETIAP ITEM DI SLOT SECARA HORIZONTAL, POSITIF KEKANAN DAN NEGATIF KEKIRI
{
    Crafting tes; // MEMBUAT DUMMY CRAFTING TABLE

    for (int i = 0; i < 3; i++)
    {
        if (i + ver < 0 || i + ver > 2)
        {
            continue;
        }
        for (int j = 0; j < 3; j++)
        {
            if (j + hor < 0 || j + hor > 2)
            {
                continue;
            }
            // JIKA i+VER DAN j+HOR TERDEFINISI MAKA AKAN DICOPY KE DUMMY
            tes.addItem(this->craftArr[i][j], i + ver, j + hor, 1);
        }
    }
    return tes == r;
    // MENGEMBALIKAN BOOLEAN KESAMAAN TRANSLASI CRAFTING TABLE DENGAN RECIPE
}

bool Crafting::checkSimetri(Recipe r)
{
    Crafting tes;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            tes.addItem(this->craftArr[i][2 - j], i, j, 1);
            // MENCERMINKAN SETIAP ITEM DI CRAFTING TABLE DENGAN DI DUMMYNYA
        }
    }
    // MELAKUKAN PENGECEKAN TERHADAP SEMUA KEMUNGKINAN TRANSLASI DARI MIRROR CRAFTING TABLE
    int maxVer = 3 - this->getRow();
    int maxHor = 3 - this->getCol();
    for (int i = -1 * maxVer; i <= maxVer; i++)
    {
        for (int j = -1 * maxHor; j <= maxHor; j++)
        {
            if (tes.checkTranslation(r, i, j))
            {
                return true;
            }
        }
    }
    return false;
}

bool Crafting::configurationCheck(Recipe r)
// MENGECEK SEMUA KEMUNGKINAN KONFIGURASI DARI CRAFTING TABLE
// BAIK SIMETRINYA MAUPUN TRANSLASINYA DENGAN RECIPE
{
    if (this->checkSimetri(r))
    {
        return true;
    }
    else
    {
        int maxVer = 3 - this->getRow();
        int maxHor = 3 - this->getCol();

        for (int i = -1 * maxVer; i <= maxVer; i++)
        {
            for (int j = -1 * maxHor; j <= maxHor; j++)
            {
                if (this->checkTranslation(r, i, j))
                {
                    return true;
                }
            }
        }
    }
    return false;
}

bool Crafting::isAllTool()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (this->craftArr[i][j] != NULL && this->craftArr[i][j]->getType() != "TOOL")
            // SLOT CRAFTING TABLE TIDAK KOSONG DAN TIPENYA BUKAN TOOL
            {
                return false;
            }
        }
    }
    return true;
}

string Crafting::isAllTheSameTool()
{
    if (this->isAllTool())
    {
        string temp = "";
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (this->craftArr[i][j] != NULL && temp == "")
                // SLOT CRAFTING TABLE TIDAK KOSONG DAN TEMP MASIH none
                {
                    temp = this->craftArr[i][j]->getName();
                }
                else if (this->craftArr[i][j] != NULL && temp != "")
                // SLOT CRAFTING TABLE TIDAK KOSONG DAN TEMP SUDAH TIDAK NONE
                // DILAKUKAN PENGECEKAN NAMA ITEM DI SLOT DENGAN TEMP
                {
                    if (temp != this->craftArr[i][j]->getName())
                    {
                        return "";
                    }
                }
            }
        }
        return temp;
    }
    return "";
}

int Crafting::durabilitySum()
{
    int sum = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (this->craftArr[i][j] != NULL && this->craftArr[i][j]->getType() == "TOOL")
            {
                sum += this->craftArr[i][j]->getDurability();
            }
        }
    }
    return sum;
}

void Crafting::substractQtyCraftTable()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (this->craftArr[i][j] != NULL)
            {
                this->craftArr[i][j]->addQuantity(-1);
                if (this->craftArr[i][j]->getQuantity() == 0)
                {
                    this->discardItem(i, j);
                }
            }
        }
    }
}