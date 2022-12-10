/*
Program Desc: Gives the blocks values in order then shuffles them randomly, then sets the shape size, position and colour
Author: Ernest John Decina
Date: 3rd June 2022

Edited by:
Date:
*/

// Libraries
#include "block.h"

// Functions

// struct block* create_blocks(void);
// Function Desc: Creates the blocks to display for the program
struct block* blocks::create_blocks(void)
{
    // Putting structured data on the heap instead of stack
    return new struct block[NUM_BLOCKS + 1];
} // End struct block* create_blocks(void);

void blocks::add_info_blocks(block* block)
{
    // Vars
    int i = 0;
    int j = 0;
    int t = 0;

    // Adding information into block structures
    for (int k = 1; k < NUM_BLOCKS; k++)
    {
        block[k].value = k;
    } // End for

    // Creating Seed 
    srand(time(NULL));

    // Shuffling number values
    std::cout << "Randomizing array" << std::endl;

    if (NUM_BLOCKS > 1)
    {
        for (i = 1; i < NUM_BLOCKS; i++)
        {
            j = i + rand() / (RAND_MAX / (NUM_BLOCKS - i) + 1);
            t = block[j].value;
            block[j].value = block[i].value;
            block[i].value = t;
        } // End for
    } // End if

    // Adding properties to the blocks
    // size, position & colour
    for (int h = 1; h < NUM_BLOCKS; h++)
    {
        // Setting size of block
        block[h].rectangle.setSize(sf::Vector2f((BLOCK_WIDTH), (BLOCK_HEIGHT * block[h].value)));

        // Moving block in position 
        block[h].rectangle.setPosition((h * 10) - BLOCK_WIDTH , WINDOW_HEIGHT - (BLOCK_HEIGHT * block[h].value));

        // Change Color of Shape
        block[h].rectangle.setFillColor(sf::Color(250, 250, 250));
        block[h].rectangle.setOutlineThickness(BLOCK_OUTLINE);
        block[h].rectangle.setOutlineColor(sf::Color(0, 0, 0));
    } // End for

} // End void blocks::add_info_blocks(block* block)
