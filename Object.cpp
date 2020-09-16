//
//  Object.cpp
//  32 Project 3
//
//  Created by Isaac Chettiath on 5/14/20.
//  Copyright © 2020 UCLA. All rights reserved.
//

#include <string>
#include "Object.h"
#include "utilities.h"

Object::Object(Objects type, int row, int col)
: m_type(type), m_row(row), m_col(col)
{
    if (type == MACE)
        m_name = "mace";
    else if (type == SHORT)
        m_name = "short sword";
    else if (type == LONG)
        m_name = "long sword";
    else if (type == ARMOR)
        m_name = "scroll of improve armor";
    else if (type == STRENGTH)
        m_name = "scroll of raise strength";
    else if (type == HEALTH)
        m_name = "scroll of of enhance health";
    else if (type == DEXTERITY)
        m_name = "scroll of enhance dexterity";
    else if (type == AXE)
        m_name = "magic axe";
    else if (type == FANGS)
        m_name = "magic fangs of sleep";
    else if (type == TELE)
        m_name = "scroll of teleportation";
}

Object::~Object()
{}

Object::Objects Object::getType()
{
    return m_type;
}

void Object::setType(Objects type)
{
    m_type = type;
}

int Object::getRow()
{
    return m_row;
}

int Object::getCol()
{
    return m_col;
}

std::string Object::getName()
{
    return m_name;
}

Weapon::Weapon(Objects type, int row, int col)
: Object(type, row, col)
{
    if (type == MACE)
    {
        m_damage = 2;
    }
    else if (type == SHORT)
    {
        m_damage = 2;
    }
    else if (type == LONG)
    {
        m_damage = 4;
        m_dexterity = 2;
    }
    else if (type == AXE)
    {
        m_damage = 5;
        m_dexterity = 5;
    }
    else if (type == FANGS)
    {
        m_damage = 2;
        m_dexterity = 3;
        m_sleeper = randInt(2, 6);
    }
}

Weapon::~Weapon()
{}

int Weapon::get_dexterity()
    {return m_dexterity;}

int Weapon::get_damage()
    {return m_damage;}

int Weapon::get_sleeper()
    {return m_sleeper;}

Scroll::Scroll(Objects type, int row, int col)
: Object(type, row, col)
{
    if (type == ARMOR)
        m_armor = randInt(1, 3);
    else if (type == STRENGTH)
        m_strength = randInt(1, 3);
    else if (type == HEALTH)
        m_health = randInt(3, 8);
    else if (type == DEXTERITY)
        m_dexterity = 1;
}

Scroll::~Scroll()
{}
