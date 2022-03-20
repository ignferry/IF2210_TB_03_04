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
            this->craftArr[i][j] = NULL;
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

bool Crafting::isSlotEmpty(int row, int col)
{
    return (this->craftArr[row][col] == NULL);
}

void Crafting::showCraftTable()
{
    for (int i = 0; i < 3; i++)
    {
        string stuff(24, '-');
        cout << "+" << stuff;
    }
    cout << "+" << endl;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (!this->isSlotEmpty(i, j))
            {
                cout << "|" << right << setw(16) << this->craftArr[i][j]->getName() << setw(8) << " ";
            }
            else
            {
                string stuff(22, ' ');
                cout << "| " << stuff << " ";
            }
        }
        cout << "|" << endl;
        for (int k = 0; k < 3; k++)
        {
            string stuff(24, '-');
            cout << "+" << stuff;
        }
        cout << "+" << endl;
    }
}

void Crafting::addItem(Item *I, int row, int col)
{
    this->craftArr[row][col] = I;
    this->checkCol();
    this->checkRow();
}

void Crafting::discardItem(int row, int col)
{
    this->craftArr[row][col] = NULL;
    this->checkCol();
    this->checkRow();
}

bool Crafting::operator==(Recipe r)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (this->craftArr[i][j] == NULL && r.getIngredientsAt(i, j) != "")
            {
                return false;
            }
            else if (this->craftArr[i][j] != NULL && r.getIngredientsAt(i, j) == "")
            {
                return false;
            }
            else if (this->craftArr[i][j] != NULL && r.getIngredientsAt(i, j) != "")
            {
                if (this->craftArr[i][j]->getVariant() != "")
                {
                    if (this->craftArr[i][j]->getVariant() != r.getIngredientsAt(i, j))
                    {
                        return false;
                    }
                }
                else if (this->craftArr[i][j]->getName() != r.getIngredientsAt(i, j))
                {
                    return false;
                }
            }
        }
    }
    return true;
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

    int maxVer = 3 - this->getRow();
    int maxHor = 3 - this->getCol();
    for (int i = -1 * maxVer; i <= maxVer; i++)
    {
        for (int j = -1 * maxHor; j <= maxHor; j++)
        {
            // cout << i << " " << j << endl;
            if (tes.checkTranslation(r, i, j))
            {
                return true;
            }
        }
    }
    return false;
}

bool Crafting::configurationCheck(Recipe r)
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
                // cout << i << " " << j << endl;
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
            {
                return false;
            }
        }
    }
    return true;
}

bool Crafting::isAllTheSameTool()
{
    if (this->isAllTool())
    {
        string temp = "none";
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (this->craftArr[i][j] != NULL && temp == "none")
                {
                    temp = this->craftArr[i][j]->getName();
                }
                else if (this->craftArr[i][j] != NULL && temp != "none")
                {
                    if (temp != this->craftArr[i][j]->getName())
                    {
                        return false;
                    }
                }
            }
        }
        return true;
    }
    return false;
}