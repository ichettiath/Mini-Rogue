//
//  Actor.cpp
//  32 Project 3
//
//  Created by Isaac Chettiath on 5/11/20.
//  Copyright © 2020 UCLA. All rights reserved.
//
#include <iostream>
#include <string>
#include <vector>
#include "Actor.h"
#include "utilities.h"
#include "Object.h"

Actor::Actor(int row, int col, int health, int armor, int strength, int dexterity, int sleep, Weapon* weapon)
: curRow(row), curCol(col), m_health(health), m_armor(armor), m_strength(strength), m_dexterity(dexterity), m_sleep(sleep), m_weapon(weapon)
{}

Actor::~Actor()
{}

void Actor::set_Row(int row)
    { curRow = row; }

void Actor::set_Col(int col)
    { curCol = col; }

int Actor::get_Row()
    {return curRow;}

int Actor::get_Col()
    {return curCol;}

int Actor::get_health()
    {return m_health;}

void Actor::set_health(int newHealth)
    {m_health = newHealth;}

int Actor::get_armor()
    {return m_armor;}

int Actor::get_strength()
    {return m_strength;}

int Actor::get_dexterity()
    {return m_dexterity;}

int Actor::get_sleep()
    {return m_sleep;}

void Actor::set_sleep(int sleep)
    {m_sleep = sleep;}

Weapon* Actor::get_weapon()
    {return m_weapon;}

Player::Player(int row, int col)
: Actor(row, col, 20, 2, 2, 2, 0, new Weapon(Object::SHORT, 0, 0)), m_name("player")
{
    inventory.emplace_back(new Weapon(Weapon::SHORT,0,0));
}

Player::~Player()
{}

void Player::move(char move)
{
    if (get_sleep() > 0)
    {
        set_sleep(get_sleep() - 1);
        return;
    }
    switch(move)
    {
        case ARROW_DOWN:
            set_Row(get_Row()+1);
            break;
        case ARROW_UP:
           set_Row(get_Row()-1);
            break;
        case ARROW_LEFT:
           set_Col(get_Col()-1);
            break;
        case ARROW_RIGHT:
           set_Col(get_Col()+1);
            break;
    }
}

std::vector<Object*> Player::getInventory()
{
    return inventory;
}

std::string Player::getName()
{
    return m_name;
}

void Actor::set_strength(int buff)
{
    m_strength = buff;
}

void Actor::set_armor(int a)
{
    m_armor = a;
}

void Actor::set_dexterity(int d)
{
    m_dexterity = d;
}

void Player::addInv(Object* o)
{
    inventory.emplace_back(o);
}

void Player:: deleteInv(int i)
{
    inventory.erase(inventory.begin()+i);
}

void Actor::move(char move)
{}

std::string Actor::getName()
{
    return "";
}

int Player::get_maxHealth()
{
    return maxHealth;
}
void Player::set_maxHealth(int health)
{
    maxHealth = health;
}
