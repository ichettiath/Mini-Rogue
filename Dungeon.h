//
//  Dungeon.h
//  32 Project 3
//
//  Created by Isaac Chettiath on 5/11/20.
//  Copyright © 2020 UCLA. All rights reserved.
//

#ifndef Arena_h
#define Arena_h

#include "utilities.h"
#include <list>
#include <string>
class Monster;
class Actor;
class Player;
class Object;
class Scroll;
class Weapon;

class Dungeon
{
public:
    Dungeon(int level);
    void createGrid();
    void display();
    bool overlap(int row, int col, int height, int width);
    void addPlayer(int row, int col);
    enum Status {EMPTY, WALL, WEAPON, SCROLL, MONSTER, STAIRS, IDOL, PLAYER};
    Status getStatus(int row, int col);
    Player* player();
    int get_stairRow();
    int get_stairCol();
    int get_idolRow();
    int get_idolCol();
    void addMonsterList();
    void addObjectList();
    int get_levels();
    void add_levels();
    std::list<Monster*> getMonsterList();
    Actor* findMonster(int row, int col);
    Object* findObject(int row, int col);
    void pickUp(Object* object);
    void attack(Actor* attacker, Actor* defender);
    void displayInventory();
    std::string getMessage();
    void findScroll(char c);
    void readScroll(Scroll* s);
    void findWeapon(char c);
    void wieldWeapon(Weapon* w);
    void moveMonsters(Player* p, Dungeon* d);
private:
    struct Room
    {
        int row;
        int col;
        int height;
        int width;
    };
    char grid[18][70];
    char displayGrid[18][70];
    Player* m_player;
    int m_stairRow;
    int m_stairCol;
    int m_idolRow;
    int m_idolCol;
    std::list<Monster*> Monsters;
    std::list<Object*> Objects;
    int m_levels;
    std::string m_message;
};

#endif
