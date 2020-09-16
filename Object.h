//
//  Object.h
//  32 Project 3
//
//  Created by Isaac Chettiath on 5/14/20.
//  Copyright © 2020 UCLA. All rights reserved.
//

#ifndef Object_h
#define Object_h

#include <string>

class Object
{
public:
    enum Objects {MACE, SHORT, LONG, ARMOR, STRENGTH, HEALTH, DEXTERITY, AXE, FANGS, TELE};
    Object(Objects type, int row, int col);
    virtual ~Object();
    Objects getType();
    void setType(Objects type);
    int getRow();
    int getCol();
    std::string getName();
private:
    Objects m_type;
    int m_row;
    int m_col;
    std::string m_name;
};

class Weapon
: public Object
{
public:
    Weapon(Objects type, int row, int col);
    virtual ~Weapon();
    int get_dexterity();
    int get_damage();
    int get_sleeper();
private:
    int m_damage;
    int m_dexterity;
    int m_sleeper;
};

class Scroll
: public Object
{
public:
    Scroll(Objects type, int row, int col);
    virtual ~Scroll();
private:
    int m_armor;
    int m_strength;
    int m_health;
    int m_dexterity;
};

#endif 
