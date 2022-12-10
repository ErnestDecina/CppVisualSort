/*
Program Desc: Chooses what type of render
Author: Ernest John Decina
Date: 7 June 2022

Edited by:
Date:
*/


// Libraries
#include "render.h"

// Functions

// void render::update_frame(sf::RenderWindow& window, block* block, int size)
// Function Desc: draws the frame
// Parameter 1: Window pointer, gain window functions
// Parameter 2: Structure block pointer to main, gain data to struct block
// Parameter 3: amount of blocks to render
void render::draw_frame(sf::RenderWindow& window, block* block, int size)
{
    for (int i = 0; i < size; i++)
    {
        // Draw the shapes in the window
        window.draw(block[i].rectangle);

    }// End while
} // End void render::update_frame(sf::RenderWindow& window, block* block, int size)

// void render::update_frame(sf::RenderWindow& window, block* block, sf::Event* event)
// Func Desc: Updates the Frame within the function, and listens for any events
// Parameter 1: Window pointer, gain window functions
// Parameter 2: Structure block pointer to main, gain data to struct block
// Parameter 3: Event pointer to listen to any events during frame update
void render::update_frame(sf::RenderWindow& window, block* block, sf::Event* event)
{
    while (window.pollEvent(*event))
    {
        // Check if Window is closed
        if (event->type == sf::Event::Closed)
            window.close();

        // Check if ESCAPE key is pressed
        if (event->type == sf::Event::KeyPressed)
        {
            if (event->key.code == sf::Keyboard::Escape)
            {
                window.close();
            } // End if
        } // End if
    } // End While

    // Update FrameWindow pointer, gain window functions
    window.clear();
    render::draw_frame(window, block, NUM_BLOCKS);
    window.display();
} // End void render::update_frame(sf::RenderWindow&, block*, sf::Event*)



// Function Desc: Options of what type of render to produce
// Parameter 1: Window pointer, gain window functions.
// Parameter 2: Structure block pointer to main, gain data to struct block.
// Parameter 3: Character pointer, for sort options.
// Parameter 4: Boolean pointer, for checking if whats being rendered is a new sort.
// Parameter 5: Event pointer, just passing through function to be passed into another function.
void render::rendering_options(sf::RenderWindow& window, block* block, char * option, bool *new_sort, sf::Event *event)
{
    // Vars
    static int j = 0;
    static bool unsorted_render_status = true;
    static bool idle_render_status = false; 
    static bool sort_update = true;
    static bool sort_status = true;

    // Checking if this call contains a new sort to render
    if (*new_sort == true)
    {
        std::cout << "New sort being rendered" << std::endl;

        // Resetting all values to allow new sort render
        j = 0;
        unsorted_render_status = true;
  
        idle_render_status = false;
        sort_update = true;
        sort_status = true;
        *new_sort = false;
        
    } // End if


    // Rendering Options
    
    // Idle render
    if (idle_render_status == true)
    {
        draw_frame(window, block, NUM_BLOCKS);
        return;
    } // End if 

    // First Render Pass, showing unsorted array
    if (unsorted_render_status == true)
    {
        // Slow Rendering 
        Sleep(1);

        // Update Frame
        draw_frame(window, block, j);

        // Limit
        if (j < NUM_BLOCKS)
        {
            j++;
            return;
        } // End while

        // Reset Values
        unsorted_render_status = false;

    } // End if

    // Rendering Sort
    else
    {
        std::cout << "Starting Sort" << std::endl;

        switch (*option)
        {
            // Insertion Sort
            case '1':
            {
                sort_update = sort_algo::sort::insertion_sort(window, block, &sort_update, event);

                break;
            } // End Case

            // Bubble Sort
            case '2':
            {
                sort_update = sort_algo::sort::bubble_sort(window, block, &sort_update, event);

                break;
            } // End Case

            // Merge Sort
            case '3':
            {
                sort_status = sort_algo::sort::merge_sort::merge_split(window, block, &sort_update, 0, NUM_BLOCKS, event);
                sort_update = false;
                
                break;
            } // End Case
        } // End switch

            
        //  Output how to exit
        std::cout << "Finished Sort" << std::endl;
        std::cout << "" << std::endl;
        std::cout << "Press esc key in window to brought back to menu" << std::endl;
            
        // Reset Variables
        idle_render_status = true;
        j = 0;
        sort_update = false;
        sort_status = false;
    } // End if
} // End void render::rendering_options(sf::RenderWindow& window, block* block, char * option, bool *new_sort)
