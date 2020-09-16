//
//  Monster.hpp
//  32 Project 3
//
//  Created by Isaac Chettiath on 5/19/20.
//  Copyright © 2020 UCLA. All rights reserved.
//

#ifndef Monster_h
#define Monster_h

#include "Actor.h"
#include <string>
#include <queue>

class Weapon;

class Monster
: public Actor
{
public:
    enum Monsters {BOGEYMEN, GOBLINS, SNAKEWOMEN, DRAGONS};
    Monster(int row, int col, int health, int armor, int strength, int dexterity, int sleep, Weapon* weapon, Monsters type);
    virtual ~Monster();
    Monsters get_type();
    virtual std::string getName();
    virtual void move(Player* p, Dungeon* d);
    bool canSmell(Player* p);
    bool goblinPath(Player* p, Dungeon* d, int row, int col, int pRow, int pCol, int distance);
private:
    Monsters m_type;
    std::string m_name;
    std::queue<char> goblinMoves;
};

class Bogeymen
: public Monster
{
public:
    Bogeymen(int row, int col);
    virtual ~Bogeymen();
};

class Goblins
: public Monster
{
public:
    Goblins(int row, int col);
    virtual ~Goblins();
};

class Snakewomen
: public Monster
{
public:
    Snakewomen(int row, int col);
    virtual ~Snakewomen();
};

class Dragons
: public Monster
{
public:
    Dragons(int row, int col);
    virtual ~Dragons();
};

#endif
