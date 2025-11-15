#pragma once
#include "Face.hpp"


/*
This is simple solver just to learn a little bit about numerical methods, multithreading, maybe gpu acceleration
It is not generic yet. Probably will be expanded to be possible to import external meshes in the future
Currently its gonna be 2D solver, with simple meshed
just flow with no energy equations yet
*/

struct Cell
{
    long id = 0;
    double volume = 0.0;
    std::array<long, 4> facesIds{};

    Cell(const long id_) : id(id_) {};
};