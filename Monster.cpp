//
//  Monster.cpp
//  32 Project 3
//
//  Created by Isaac Chettiath on 5/19/20.
//  Copyright © 2020 UCLA. All rights reserved.
//
#include <string>
#include <iostream>
#include <cmath>
#include "Monster.h"
#include "Object.h"
#include "utilities.h"
#include "Dungeon.h"
using namespace std;
class Weapon;

Monster::Monster(int row, int col, int health, int armor, int strength, int dexterity, int sleep, Weapon* weapon, Monsters type)
: Actor(row, col, health, armor, strength, dexterity, sleep, weapon), m_type(type)
{
    if (type == GOBLINS)
        m_name = "the goblin";
    else if (type == SNAKEWOMEN)
        m_name = "the snakewoman";
    else if (type == DRAGONS)
        m_name = "the drgaon";
    else if (type == BOGEYMEN)
        m_name = "the bogeyman";
}

Monster::~Monster()
{}

bool Monster::canSmell(Player* p)
{
    int pRow = p->get_Row()-1;
    int pCol = p->get_Col()-1;
    int rowDistance = abs(get_Row() - pRow);
    int colDistance = abs(get_Col() - pCol);
    int totalDistance = rowDistance + colDistance;
    if (get_type() == Monster::SNAKEWOMEN)
    {
        if (totalDistance <= 3)
            return true;
        else
            return false;
    }
    else if (get_type() == Monster::BOGEYMEN)
    {
        if (totalDistance <= 5)
            return true;
        else
            return false;
    }
    else if (get_type() == Monster::DRAGONS)
    {
        if (totalDistance == 1)
            return true;
        else
            return false;
    }
    else
        return true;
}

void Monster::move(Player* p, Dungeon* d)
{
    if (!canSmell(p))
        return;
    //player coordinates:
    int pRow = p->get_Row()-1;
    int pCol = p->get_Col()-1;
    int r = get_Row();
    int c = get_Col();
    int rowDistance = r - pRow;
    int colDistance = c - pCol;
    //goblin movement is based differently than other monsters
    if (get_type() == Monsters::GOBLINS && !goblinMoves.empty())
    {
        char c = goblinMoves.front();
        if (goblinPath(p, d, r, c, pRow, pCol, 10))
        {
            if (c == ARROW_DOWN)
                r++;
            else if (c == ARROW_UP)
                r--;
            else if (c == ARROW_LEFT)
                c--;
            else if (c == ARROW_RIGHT)
                c++;
        }
        queue<char> empty;
        goblinMoves.swap(empty);
    }
    else
    {
        if (rowDistance < 0)
            r++;
        else if (rowDistance > 0)
            r--;
        else if (colDistance < 0)
            c++;
        else if (colDistance > 0)
            c--;
        if (d->getStatus(r+1, c+1) == Dungeon::Status::WALL)
            return;
    }
    if (r == pRow && c == pCol)
    {
        d->attack(this, p);
        cout << d->getMessage() << endl;
        return;
    }
    else
    {
        set_Row(r);
        set_Col(c);
    }
}

Monster::Monsters Monster::get_type()
{
    return m_type;
}

std::string Monster::getName()
{
    return m_name;
}

Bogeymen::Bogeymen(int row, int col)
: Monster(row, col, randInt(5, 10), 2, randInt(2, 3), randInt(2, 3), 0, new Weapon(Object::SHORT, 0, 0), BOGEYMEN)
{}

Goblins::Goblins(int row, int col)
: Monster(row, col, randInt(15, 20), 1, 3, 1, 0, new Weapon(Object::SHORT, 0, 0), GOBLINS)
{}

Snakewomen::Snakewomen(int row, int col)
: Monster(row, col, randInt(3, 6), 3, 2, 3, 0, new Weapon(Object::FANGS, 0, 0), SNAKEWOMEN)
{}
    
Dragons::Dragons(int row, int col)
: Monster(row, col, randInt(20, 25), 4, 4, 4, 0, new Weapon(Object::LONG, 0, 0), DRAGONS)
{}

Bogeymen::~Bogeymen()
{}

Goblins::~Goblins()
{}

//recursively finds a path between the goblin and the player and pushes the mpoves onto a queue
bool Monster::goblinPath(Player* p, Dungeon* d, int row, int col, int pRow, int pCol, int distance)
{
    if (distance < 1)
        return false;
    if (row == pRow && col == pCol)
        return true;
    if (row < pRow)
    {
        if (goblinPath(p, d, row+1, col, pRow, pCol, distance-1) && d->getStatus(row+1, col) != Dungeon::WALL && d->getStatus(row+1, col) != Dungeon::MONSTER)
        {
            goblinMoves.push(ARROW_DOWN);
            return true;
        }
    }
    if (row > pRow)
    {
        if (goblinPath(p, d, row-1, col, pRow, pCol, distance-1) && d->getStatus(row-1, col) != Dungeon::WALL && d->getStatus(row+1, col) != Dungeon::MONSTER)
        {
            goblinMoves.push(ARROW_UP);
            return true;
        }
    }
    if (col > pCol)
    {
        if (goblinPath(p, d, row, col-1, pRow, pCol, distance-1) && d->getStatus(row, col-1) != Dungeon::WALL && d->getStatus(row+1, col) != Dungeon::MONSTER)
        {
            goblinMoves.push(ARROW_LEFT);
            return true;
        }
    }
    if (col < pCol)
    {
        if (goblinPath(p, d, row, col+1, pRow, pCol, distance-1) && d->getStatus(row, col+1) != Dungeon::WALL && d->getStatus(row+1, col) != Dungeon::MONSTER)
        {
            goblinMoves.push(ARROW_RIGHT);
            return true;
        }
    }
    return false;
}

Snakewomen::~Snakewomen()
{}

Dragons::~Dragons()
{}


