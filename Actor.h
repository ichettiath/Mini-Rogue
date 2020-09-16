//
//  Actor.hpp
//  32 Project 3
//
//  Created by Isaac Chettiath on 5/11/20.
//  Copyright © 2020 UCLA. All rights reserved.
//

#ifndef Actor_h
#define Actor_h

#include <string>
#include <vector>
#include "Dungeon.h"
class Dungeon;
class Object;
class Weapon;

class Actor
{
public:
    Actor(int row, int col, int health, int armor, int strength, int dexterity, int sleep, Weapon* weapon);
    virtual ~Actor();
    int get_Row();
    int get_Col();
    void set_Row(int row);
    void set_Col(int col);
    int get_health();
    void set_health(int newHealth);
    void set_strength(int buff);
    void set_armor(int a);
    void set_dexterity(int d);
    void set_sleep(int sleep);
    int get_armor();
    int get_strength();
    int get_dexterity();
    int get_sleep();
    Weapon* get_weapon();
    virtual void move(char move);
    virtual std::string getName();
private:
    int curRow;
    int curCol;
    int m_health;
    int m_armor;
    int m_strength;
    int m_dexterity;
    int m_sleep;
    Weapon* m_weapon;
};

class Player
: public Actor
{
public:
    Player(int row, int col);
    virtual ~Player();
    virtual void move(char move);
    std::vector<Object*> getInventory();
    virtual std::string getName();
    void addInv(Object* o);
    void deleteInv(int i);
    int get_maxHealth();
    void set_maxHealth(int health);
private:
    std::vector<Object*> inventory;
    std::string m_name;
    int maxHealth = 20;
};


#endif
