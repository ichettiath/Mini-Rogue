//
//  Dungeon.cpp
//  32 Project 3
//
//  Created by Isaac Chettiath on 5/11/20.
//  Copyright © 2020 UCLA. All rights reserved.
//
#include <iostream>
#include <list>
#include <string>
#include "Dungeon.h"
#include "utilities.h"
#include "Actor.h"
#include "Monster.h"
#include "Game.h"
#include "Object.h"
using namespace std;

Dungeon::Dungeon(int level)
: m_levels(level)
{}

void Dungeon::createGrid()
{
    Monsters.clear();
    Objects.clear();
    int NumberOfRooms = randInt(4, 5);
    vector<Room> rooms(NumberOfRooms);
    //initalizes the grid block
    for (int k = 0; k < 18; k++)
    {
        for (int i = 0; i < 70; i++)
        {
            grid[k][i] = '#';
        }
    }
    //creates the rooms
    for (int a = 0; a < NumberOfRooms; a++)
    {
        rooms[a].width = randInt(11, 15);
        rooms[a].height = randInt(6, 8);
        rooms[a].row = randInt(1, 18-rooms[a].height-1);
        rooms[a].col = randInt(1, 70-rooms[a].width-1);
        while (overlap(rooms[a].row, rooms[a].col, rooms[a].height, rooms[a].width))
        {
            rooms[a].width = randInt(10, 15);
            rooms[a].height = randInt(4, 8);
            rooms[a].row = randInt(1, 18-rooms[a].height-1);
            rooms[a].col = randInt(1, 70-rooms[a].width-1);
        }
        for (int b = rooms[a].row; b < rooms[a].row + rooms[a].height; b++)
        {
            for (int i = rooms[a].col; i < rooms[a].col + rooms[a].width; i++)
                grid[b][i] = ' ';
        }
    }
    //creates the cooridors connecting the rooms
    for (int c = 0; c < NumberOfRooms-1; c++)
    {
        int middleRow1 = rooms[c].row + (rooms[c].height / 2);
        int middleRow2 = rooms[c+1].row + (rooms[c+1].height / 2);
        int middleCol1 = rooms[c].col + (rooms[c].width / 2);
        int middleCol2 = rooms[c+1].col + (rooms[c+1].width / 2);
        if (middleCol1 <= middleCol2 && middleRow1 <= middleRow2)
        {
            for (int d = 0; d < middleCol2-middleCol1+1; d++)
            {
                grid[middleRow1][d+middleCol1] = ' ';
            }
            for (int e = 0; e < middleRow2-middleRow1; e++)
            {
                grid[middleRow2-e][middleCol2] = ' ';
            }
        }
        if (middleCol1 <= middleCol2 && middleRow1 > middleRow2)
        {
            for (int f = 0; f < middleCol2-middleCol1+1; f++)
            {
                grid[middleRow1][f+middleCol1] = ' ';
            }
            for (int g = 0; g < middleRow1-middleRow2; g++)
            {
                grid[middleRow2+g][middleCol2] = ' ';
            }
        }
        if (middleCol1 > middleCol2 && middleRow1 <= middleRow2)
           {
            for (int h = 0; h < middleCol1-middleCol2+1; h++)
            {
                grid[middleRow2][h+middleCol2] = ' ';
            }
            for (int i = 0; i < middleRow2-middleRow1; i++)
            {
                grid[middleRow1+i][middleCol1] = ' ';
            }
        }
        if (middleCol1 > middleCol2 && middleRow1 > middleRow2)
        {
            for (int j = 0; j < middleCol1-middleCol2+1; j++)
            {
                grid[middleRow2][j+middleCol2] = ' ';
            }
            for (int k = 0; k < middleRow1-middleRow2; k++)
            {
                grid[middleRow1-k][middleCol1] = ' ';
            }
        }
    }
    if (get_levels() < 4)
    {
        do
        {
        m_stairRow = randInt(1, 17);
        m_stairCol = randInt(1, 69);
        } while (grid[m_stairRow][m_stairCol] != ' ');
        grid[m_stairRow][m_stairCol] = '>';
    }
    if (get_levels() == 4)
    {
        do
        {
        m_idolRow = randInt(1, 17);
        m_idolCol = randInt(1, 69);
        } while (grid[m_idolRow][m_idolCol] != ' ');
        grid[m_idolRow][m_idolCol] = '&';
    }
    addMonsterList();
    addObjectList();
}

bool Dungeon::overlap(int row, int col, int height, int width)
{
    for (int k = row-2; k < row + height+2; k++)
    {
        for (int i = col-2; i < col + width+2; i++)
        {
            if (grid[k][i] == ' ')
                return true;
        }
    }
    return false;
}

void Dungeon::display()
{
    clearScreen();
    char prev = grid[m_player->get_Row()-1][m_player->get_Col()-1];
    
    for (int l = 0; l < 18; l++)
    {
        for (int m = 0; m < 70; m++)
        {
            displayGrid[l][m] = grid[l][m];
        }
    }
    //displays the objects on the grid
    for (list<Object*>::iterator it = Objects.begin(); it != Objects.end(); it++)
    {
        if ((*it)->getType() == Object::MACE || (*it)->getType() == Object::SHORT || (*it)->getType() == Object::LONG)
            displayGrid[(*it)->getRow()][(*it)->getCol()] = ')';
        else
            displayGrid[(*it)->getRow()][(*it)->getCol()] = '?';
    }
    //displays the monsters on the grid
    for (list<Monster*>::iterator it = Monsters.begin(); it != Monsters.end(); it++)
    {
        if ((*it)->get_type() == Monster::BOGEYMEN)
            displayGrid[(*it)->get_Row()][(*it)->get_Col()] = 'B';
        else if ((*it)->get_type() == Monster::GOBLINS)
            displayGrid[(*it)->get_Row()][(*it)->get_Col()] = 'G';
        else if ((*it)->get_type() == Monster::SNAKEWOMEN)
            displayGrid[(*it)->get_Row()][(*it)->get_Col()] = 'S';
        else if ((*it)->get_type() == Monster::DRAGONS)
            displayGrid[(*it)->get_Row()][(*it)->get_Col()] = 'D';
    }
    //displays the player on the grid
    displayGrid[m_player->get_Row()-1][m_player->get_Col()-1] = '@';
    for (int l = 0; l < 18; l++)
    {
        for (int m = 0; m < 70; m++)
        {
            cout << displayGrid[l][m];
        }
        cout << endl;
    }
    grid[m_player->get_Row()-1][m_player->get_Col()-1] = prev;
    cout << "Dungeon Level: " << get_levels() << ", Hit points: " << m_player->get_health() << ", Armor: " << m_player->get_armor() << " Strength: " << m_player->get_strength() << ", Dexterity: " << m_player->get_dexterity() << endl;
}

void Dungeon::addPlayer(int row, int col)
{
    m_player = new Player(row, col);
}

Dungeon::Status Dungeon::getStatus(int row, int col)
{
    if (grid[row-1][col-1] == '#')
        return WALL;
    else if (grid[row-1][col-1] == ')')
        return WEAPON;
    else if (displayGrid[row-1][col-1] == 'B' || displayGrid[row-1][col-1] == 'D' || displayGrid[row-1][col-1] == 'G' || displayGrid[row-1][col-1] == 'S')
        return MONSTER;
    else if (grid[row-1][col-1] == '?')
        return SCROLL;
    else if (grid[row-1][col-1] == '>')
        return STAIRS;
    else if (grid[row-1][col-1] == '&')
        return IDOL;
    else if (grid[row-1][col-1] == '@')
        return PLAYER;
    else
        return EMPTY;
}

Player* Dungeon::player()
{
    return m_player;
}

int Dungeon::get_stairRow()
{
    return m_stairRow;
}
int Dungeon::get_stairCol()
{
    return m_stairCol;
}

int Dungeon::get_idolRow()
{
    return m_idolRow;
}
int Dungeon::get_idolCol()
{
    return m_idolCol;
}

int Dungeon::get_levels()
{
    return m_levels;
}

void Dungeon::add_levels()
{
    m_levels++;
}

list<Monster*> Dungeon::getMonsterList()
{
    return Monsters;
}

Actor* Dungeon::findMonster(int row, int col)
{
    for (list<Monster*>::iterator it = Monsters.begin(); it != Monsters.end(); it++)
    {
        if ((*it)->get_Row() == row && (*it)->get_Col() == col)
            return (*it);
    }
    return 0;
}

Object* Dungeon::findObject(int row, int col)
{
    for (list<Object*>::iterator it = Objects.begin(); it != Objects.end(); it++)
    {
        if ((*it)->getRow() == row && (*it)->getCol() == col)
            return (*it);
    }
    return 0;
}

void Dungeon::attack(Actor* attacker, Actor* defender)
{
    if (attacker->get_sleep() > 0)
    {
        attacker->set_sleep(attacker->get_sleep() - 1);
        return;
    }
    int damagePoints = randInt(0, attacker->get_strength() + attacker->get_weapon()->get_damage() - 1);
    int attackerPoints = attacker->get_dexterity() + attacker->get_weapon()->get_dexterity();
    int defenderPoints = defender->get_dexterity() + defender->get_armor();
    std::string animation;
    if (attacker->get_weapon()->getType() == Object::SHORT || attacker->get_weapon()->getType() == Object::LONG)
        animation = " slashes ";
    else if (attacker->get_weapon()->getType() == Object::MACE)
        animation = " swings ";
    else if (attacker->get_weapon()->getType() == Object::AXE)
        animation = " chops ";
    else if (attacker->get_weapon()->getType() == Object::FANGS)
        animation = " strikes ";
    if (randInt(1, attackerPoints) >= randInt(1, defenderPoints))
    {
        defender->set_health(defender->get_health()-damagePoints);
        if (defender->get_health() <= 0)
        {
            m_message = attacker->getName() + " slashes " + attacker->get_weapon()->getName() + " at " + defender->getName() + " dealing a final blow.";
            int r = defender->get_Row();
            int c = defender->get_Col();
            if (defender->getName() == "the bogeyman")
            {

                int chance = randInt(1, 10);
                if (chance == 1)
                    Objects.emplace_back(new Weapon(Object::AXE, r, c));
            }
            else if (defender->getName() == "the snakewoman")
            {

                int chance = randInt(1, 3);
                if (chance == 1)
                    Objects.emplace_back(new Weapon(Object::FANGS, r, c));
            }
            else if (defender->getName() == "the goblin")
            {
                int chance  = randInt(1, 6);
                if (chance == 1)
                    Objects.emplace_back(new Weapon(Object::FANGS, r, c));
                else if (chance == 2)
                    Objects.emplace_back(new Weapon(Object::AXE, r, c));
            }
            else if (defender->getName() == "the dragon")
            {
                int chance = randInt(1, 5);
                switch (chance)
                {
                    case 1:
                        Objects.emplace_back(new Weapon(Object::TELE, r, c));
                    case 2:
                        Objects.emplace_back(new Weapon(Object::STRENGTH, r, c));
                    case 3:
                        Objects.emplace_back(new Weapon(Object::HEALTH, r, c));
                    case 4:
                        Objects.emplace_back(new Weapon(Object::DEXTERITY, r, c));
                    case 5:
                        Objects.emplace_back(new Weapon(Object::ARMOR, r, c));
                }
            }
            list<Monster*>::iterator it = Monsters.begin();
            while (it != Monsters.end())
            {
                if (*it == defender)
                {
                    Monsters.erase(it);
                    break;
                }
                it++;
            }
        }
        else
            m_message = attacker->getName() + " slashes " + attacker->get_weapon()->getName() + " at " + defender->getName() + " and hits.";
    }
    else
        m_message = attacker->getName() + " slashes " + attacker->get_weapon()->getName() + " at " + defender->getName() + " and misses. ";
    if (attacker->get_weapon()->getType() == Object::FANGS)
    {
        int chance = randInt(1, 5);
        if (chance == 1)
        {
            defender->set_sleep(defender->get_sleep() + defender->get_weapon()->get_sleeper());
            m_message += defender->getName() + " has been put to sleep.";
        }
    }
}

void Dungeon::addMonsterList()
{
    int numMonsters = randInt(2, 5*(get_levels()+1)+1);
    for (int i = 0; i < numMonsters; i++)
    {
        int rand = randInt(0,3);
        int row;
        int col;
        do
        {
        row = randInt(1, 17);
        col = randInt(1, 69);
        } while (getStatus(row+1, col+1) != Dungeon::EMPTY);
        switch(rand)
        {
            case Monster::DRAGONS:
                if (get_levels() >= 3)
                {
                    Monsters.emplace_back(new Dragons(row, col));
                    break;
                }
            case Monster::GOBLINS:
                Monsters.emplace_back(new Goblins(row, col));
                break;
            case Monster::BOGEYMEN:
                if (get_levels() >= 2)
                {
                    Monsters.emplace_back(new Bogeymen(row, col));
                    break;
                }
            case Monster::SNAKEWOMEN:
                Monsters.emplace_back(new Snakewomen(row, col));
                break;
        }
    }
}

void Dungeon::addObjectList()
{
    int numObjects = randInt(2, 3);
    for (int i = 0; i < numObjects; i++)
    {
        int rand = randInt(0, 6);
        int row;
        int col;
        do
        {
        row = randInt(1, 17);
        col = randInt(1, 69);
        }while (getStatus(row+1, col+1) != Dungeon::EMPTY);
        switch(rand)
        {
            case Object::MACE:
                Objects.emplace_back(new Weapon(Object::MACE, row, col));
                break;
            case Object::SHORT:
                Objects.emplace_back(new Weapon(Object::SHORT, row, col));
                break;
            case Object::LONG:
                Objects.emplace_back(new Weapon(Object::LONG, row, col));
                break;
            case Object::ARMOR:
                Objects.emplace_back(new Scroll(Object::ARMOR, row, col));
                break;
            case Object::HEALTH:
                Objects.emplace_back(new Scroll(Object::STRENGTH, row, col));
                break;
            case Object::STRENGTH:
                Objects.emplace_back(new Scroll(Object::HEALTH, row, col));
                break;
            case Object::DEXTERITY:
                Objects.emplace_back(new Scroll(Object::DEXTERITY, row, col));
                break;
            default:
                break;
        }
    }
}

void Dungeon::pickUp(Object* object)
{
    player()->addInv(object);
    Objects.remove(object);
}

void Dungeon::displayInventory()
{
    clearScreen();
    cout << endl << "Inventory:" << endl;
    char c = 'a';
    for (int i = 0; i < m_player->getInventory().size(); i++)
    {
        cout << "     " << c << ". " << m_player->getInventory()[i]->getName() << endl;
        c++;
    }
}

string Dungeon::getMessage()
{
    return m_message;
}

void Dungeon::readScroll(Scroll* s)
{
    if (s->getType() == Object::STRENGTH)
        m_player->set_strength(m_player->get_strength() + randInt(1, 3));
    else if (s->getType() == Object::ARMOR)
        m_player->set_armor(m_player->get_armor() + randInt(1, 3));
    else if (s->getType() == Object::HEALTH)
    {
        m_player->set_health(m_player->get_health() + randInt(3, 8));
        if (m_player->get_health() > m_player->get_maxHealth())
        {
            m_player->set_health(m_player->get_maxHealth());
        }
    }
    else if (s->getType() == Object::DEXTERITY)
        m_player->set_dexterity(m_player->get_dexterity() + 1);
    else if (s->getType() == Object::TELE)
    {
        int random_row;
        int random_col;
        do
        {
            random_row = randInt(1, 17);
            random_col = randInt(1, 69);
        } while (getStatus(random_row, random_col) != Dungeon::EMPTY);
        m_player->set_Row(random_row);
        m_player->set_Col(random_col);
    }
}

void Dungeon::findScroll(char c)
{
    if (m_player->getInventory().size() > 25)
    {
        m_message = "Your knapsack is full; you can't pick that up.";
        return;
    }
    //ensures a valid item is being selected
    int convert = c -'a';
    if (convert < 0 || convert > 25 || convert > m_player->getInventory().size())
        return;
    int i;
    for (i = 0; i < convert; i++)
        ;
    Weapon* w = dynamic_cast<Weapon*>(m_player->getInventory()[i]);
    if (w != nullptr)
    {
        m_message = "You cannot read " + w->getName();
        return;
    }
    Scroll* s = dynamic_cast<Scroll*>(m_player->getInventory()[i]);
    if (s != nullptr)
    {
        readScroll(s);
        m_message = "You read a scroll called  " + s->getName();
        if (s->getType() == Object::TELE)
            m_message += "\nYou feel your body wrenched in space and time.";
        else if (s->getType() == Object::STRENGTH)
            m_message += "\nYour muscles bulge.";
        else if (s->getType() == Object::ARMOR)
            m_message += "\nYour armor glows blue.";
        else if (s->getType() == Object::HEALTH)
            m_message += "\nYou feel your heart beating stronger.";
        else if (s->getType() == Object::DEXTERITY)
            m_message += "\nYou feel like less of a klutz.";
        m_player->deleteInv(i);
    }
}

void Dungeon::wieldWeapon(Weapon* w)
{
    if (w->getType() == Weapon::SHORT)
        m_player->get_weapon()->setType(Weapon::SHORT);
    else if (w->getType() == Weapon::LONG)
        m_player->get_weapon()->setType(Weapon::LONG);
    else if (w->getType() == Weapon::MACE)
        m_player->get_weapon()->setType(Weapon::MACE);
    else if (w->getType() == Weapon::AXE)
        m_player->get_weapon()->setType(Weapon::AXE);
    else if (w->getType() == Weapon::FANGS)
        m_player->get_weapon()->setType(Weapon::FANGS);
}

void Dungeon::findWeapon(char c)
{
    int convert = c -'a';
    //ensures a valid item is being selected
    if (convert < 0 || convert > 25 || convert > m_player->getInventory().size())
        return;
    int i;
    for (i = 0; i < convert; i++)
        ;
    Scroll* s = dynamic_cast<Scroll*>(m_player->getInventory()[i]);
    if (s != nullptr)
    {
        m_message = "You cannot wield " + s->getName();
        return;
    }
    Weapon* w = dynamic_cast<Weapon*>(m_player->getInventory()[i]);
    if (w != nullptr)
    {
        wieldWeapon(w);
        m_message = "You are wielding a " + w->getName();
    }
}

void Dungeon::moveMonsters(Player* p, Dungeon* d)
{
    for (list<Monster*>::iterator it = Monsters.begin(); it != Monsters.end(); it++)
        (*it)->move(p, d);
}
