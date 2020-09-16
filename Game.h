//
//  Game.h
//  32 Project 3
//
//  Created by Isaac Chettiath on 5/11/20.
//  Copyright © 2020 UCLA. All rights reserved.
//

#ifndef GAME_INCLUDED
#define GAME_INCLUDED

#include <vector>
class Dungeon;

class Game
{
public:
    Game();
    void placePlayer();
    void play();
    void addMonsterList();
private:
    Dungeon* m_dungeon;
};

#endif
