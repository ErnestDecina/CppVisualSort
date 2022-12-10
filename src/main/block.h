/*
Library Desc:
Author: Ernest John Decina
Date: 31 May 2022
*/

// block.h
#pragma once

// Libraries
#include "SFML/Graphics.hpp"
#include "program_properties.h"
#include <iostream>

// Structs
struct block
{
    // Creating a Reactangle shape.
    sf::RectangleShape rectangle;

    // Creating value of the block, will also determin size.
    unsigned int value = 0;
};

// Functions
namespace blocks
{
    struct block* create_blocks(void);
    void add_info_blocks(struct block*);
}