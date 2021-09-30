// BioSphere.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "atom.h"
#include "map.h"
#include "gamecontroller.h"
#include "levels.h"
#include "rendering.h"
#include <type_traits>

int main(void)
{
    gc = new GameController();
    generateMap<13, 4>(gc->map, levels::test, levels::test_a);
    gc->initialized = true;

    auto* client = gc->createAtom<ClientMob>(1, 1);

    while (true)
    {
        std::cout << render(*client) << std::endl;

        Vector2i dir;
        switch (getchar())
        {
        case 'w':
            dir = { 0, -1 };
            break;

        case 'd':
            dir = { 1, 0 };
            break;

        case 's':
            dir = { 0, 1 };
            break;

        case 'a':
            dir = { -1, 0 };
            break;
        }
        getchar();
        client->move(make_step(*client, dir));
    }

}