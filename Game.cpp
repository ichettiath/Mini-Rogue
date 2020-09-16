//
//  Game.cpp
//  32 Project 3
//
//  Created by Isaac Chettiath on 5/11/20.
//  Copyright © 2020 UCLA. All rights reserved.
//

#include "Game.h"
#include "utilities.h"
#include "Dungeon.h"
#include "Actor.h"
#include "Object.h"
#include <iostream>
#include <string>
#include <list>
#include "Monster.h"
using namespace std;

Game::Game()
{
    m_dungeon = new Dungeon(0);
    m_dungeon->createGrid();
    placePlayer();
}

void Game::placePlayer()
{
    //finds a spot on the grid that is empty and places a new player there
    int random_row;
    int random_col;
    do
    {
        random_row = randInt(1, 17);
        random_col = randInt(1, 69);
    } while (m_dungeon->getStatus(random_row, random_col) != Dungeon::EMPTY);
    m_dungeon->addPlayer(random_row, random_col);
}

//defines the functionality of the controls
void Game::play()
{
    m_dungeon->display();
    while (true)
    {
        if (m_dungeon->player()->get_health() <= 0)
        {
            cout << "You lose! " << endl << "press q to exit game" << endl;;
            while (getCharacter() != 'q')
            {}
            return;
        }
        char getMove = getCharacter();
        bool pauseGrid = false; //ensures that grid is not displayed when the inventory is opened
        m_dungeon->display();
        int r = m_dungeon->player()->get_Row();
        int c = m_dungeon->player()->get_Col();
        switch (getMove)
        {
            case 'q': //quits the game
                return;
            case ARROW_UP:
                r--;
                break;
            case ARROW_DOWN:
                r++;
                break;
            case ARROW_LEFT:
                c--;
                break;
            case ARROW_RIGHT:
                c++;
                break;
            case '>': //goes down the stairs
                if (r == m_dungeon->get_stairRow()+1 && c == m_dungeon->get_stairCol()+1)
                {
                    pauseGrid = true;
                    m_dungeon->add_levels();
                    m_dungeon->createGrid();
                    placePlayer();
                    m_dungeon->display();
                }
                break;
            case 'c': //boosts stats for testing purposes
                m_dungeon->player()->set_health(50);
                m_dungeon->player()->set_strength(9);
                m_dungeon->player()->set_maxHealth(50);
                break;
            case 'g': //picks up the idol
            if (r == m_dungeon->get_idolRow()+1 && c == m_dungeon->get_idolCol()+1)
            {
                cout << endl << "Congratulations, you won!" << endl << "press q to exit game." << endl;
                while (getCharacter() != 'q')
                {}
                return;
            }
            m_dungeon->pickUp(m_dungeon->findObject(r-1, c-1));
                break;
            case 'r': //opens scroll list
            {
                pauseGrid = true;
                m_dungeon->displayInventory();
                char r = getCharacter();
                m_dungeon->findScroll(r);
                m_dungeon->display();
                cout << endl << m_dungeon->getMessage() << endl;
                break;
            }
            case 'i': //displays inventory
                m_dungeon->displayInventory();
                getCharacter();
                break;
            case 'w': //opens weapon list
            {
                pauseGrid = true;
                m_dungeon->displayInventory();
                char b = getCharacter();
                m_dungeon->findWeapon(b);
                m_dungeon->display();
                cout << endl << m_dungeon->getMessage() << endl;
                break;
            }
            default:
                break;
        }
        if (!pauseGrid)
        {
            if (m_dungeon->getStatus(r, c) != Dungeon::WALL && m_dungeon->getStatus(r, c) != Dungeon::MONSTER)
            {
                m_dungeon->player()->move(getMove);
                m_dungeon->moveMonsters(m_dungeon->player(), m_dungeon);
                m_dungeon->display();
            }
            if (m_dungeon->getStatus(r, c) == Dungeon::MONSTER)
            {
                m_dungeon->attack(m_dungeon->player(), m_dungeon->findMonster(r-1, c-1));
                cout << endl << m_dungeon->getMessage() << endl;
                m_dungeon->moveMonsters(m_dungeon->player(), m_dungeon);
            }
            else
                m_dungeon->moveMonsters(m_dungeon->player(), m_dungeon);
        }
    }
}
