#include "../header/Crafting.hpp"
#include <iostream>

using namespace std;

Crafting::Crafting()
{
    this->craftArr = new Item *[3];
    for (int i = 0; i < 3; i++)
    {
        this->craftArr[i] = new Item[3];
    }
    rowEff = 0;
    colEff = 0;
}

Crafting::Crafting(const Crafting &c)
{
    this->craftArr = new Item *[3];
    for (int i = 0; i < 3; i++)
    {
        this->craftArr[i] = c.craftArr[i];
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
            if (this->craftArr[i][j].getName() != "")
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
            if (this->craftArr[i][j].getName() != "")
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

bool Crafting::isSlotEmpty(int row, int col)
{
    return (this->craftArr[row][col].getName() == "");
}

void Crafting::showCraftTable()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (this->isSlotEmpty(i, j))
            {
                cout << "["
                     << "C " << i * 3 + j << "] ";
            }
            else
            {
                cout << "[" << this->craftArr[i][j].getName() << "] ";
            }
        }
        cout << endl;
    }
}

void Crafting::addItem(Item I, int row, int col)
{
    this->craftArr[row][col] = I;
    this->checkCol();
    this->checkRow();
}

void Crafting::discardItem(int row, int col)
{
    Item *I = new Item();
    this->craftArr[row][col] = *I;
    this->checkCol();
    this->checkRow();
}

bool Crafting::operator==(Recipe r)
{
    bool flag = true;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (this->craftArr[i][j].getName() != r.getIngredientsAt(i, j))
            {
                flag = false;
            }
        }
    }
    return flag;
}

bool Crafting::checkTranslation(Recipe r, int ver, int hor)
{
    Crafting tes;

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
            tes.addItem(this->craftArr[i][j], i + ver, j + hor);
        }
    }
    return tes == r;
}

bool Crafting::checkSimetri(Recipe r)
{
    Crafting tes;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            tes.addItem(this->craftArr[i][2 - j], i, j);
        }
    }

    return tes == r;
}

bool Crafting::configurationCheck(Recipe r)
{
    if (this->checkSimetri(r))
    {
        return true;
    }
    else
    {
        int maxVer = 3 - r.getRow();
        int maxHor = 3 - r.getCol();

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