/*
Program Desc: Sorts Blocks in their correct position then renders them to the window
Author: Ernest John Decina
Date: 3rd June 2022

Edited by:
Date:
*/

// Libraries
#include "sort_algo.h"

// Functions
// 
// 
// void insertion_sort(sf::RenderWindow &, struct block *)
// Function Desc: Sorts blocks and updates the frame
// Parameter 1: Window pointer, gain window functions
// Parameter 2: structure block pointer to main, gain data to struct block
// Parameter 3: Boolean pointer to new_sort, check state of new_sort (true || false)
bool sort_algo::sort::insertion_sort(sf::RenderWindow& window, block* block, bool* new_sort, sf::Event* event)
{
    // Vars
    int i = 0;
    int j = 0;
    int key = 0;
    int rendering_status = 0;

    // Sorting (Insertion Sort)
    for (i = 0; i < NUM_BLOCKS; i++)
    {
        // Creating a key
        key = block[i].value;

        // Creating previous index
        j = i - 1;

        // Checking if andy value before key is smaller
        while (j >= 0 && block[j].value > key)
        {
            // Swapping Values
            block[j + 1].value = block[j].value;

            // Changing properties of the block when swapped
            block[j + 1].rectangle.setSize(sf::Vector2f(float(BLOCK_WIDTH), float(BLOCK_HEIGHT * block[j + 1].value)));
            block[j + 1].rectangle.setPosition(((j + 1) * 10) - BLOCK_WIDTH, WINDOW_HEIGHT - (BLOCK_HEIGHT * block[j + 1].value));

            // Creating swap highlight to track swapping
            block[j].rectangle.setFillColor(sf::Color(0, 250, 0));
            block[j + 1].rectangle.setFillColor(sf::Color(250, 250, 250));

            // Decrement down the array
            j = j - 1;

            // Update Frame
            render::update_frame(window, block, event);
        } // End while

        // Swapping Values
        block[j + 1].value = key;

        // Changing properties of the block when swapped
        block[j + 1].rectangle.setSize(sf::Vector2f(float(BLOCK_WIDTH), float(BLOCK_HEIGHT * block[j + 1].value)));
        block[j + 1].rectangle.setPosition(((j + 1) * 10) - BLOCK_WIDTH, WINDOW_HEIGHT - (BLOCK_HEIGHT * block[j + 1].value));

        // Changing block colour to white
        block[j + 1].rectangle.setFillColor(sf::Color(250, 250, 250));

        // Update Frame
        render::update_frame(window, block, event);
    } // End While

    return false;
} // End int sort_algo::sort::insertion_sort(sf::RenderWindow& window, block* block)

// bool sort_algo::sort::bubble_sort(sf::RenderWindow& window, block* block, bool *new_sort)
// Function Desc: Sorts the blocks using Insertion Sort
// Parameter 1: Window Address so we can use window function's within this function
// Parameter 2: Point to the array of blocks created in main
// Parameter 3: Boolean pointer to value of new_sort, telling the function if this call is the start of a new sort
bool sort_algo::sort::bubble_sort(sf::RenderWindow& window, block* block, bool *new_sort, sf::Event* event)
{  
    // Vars
    int i = 0;
    int j = 0;
    int key;

    // Bubble Sort
    for (i = 0; i < NUM_BLOCKS; i++)
    {
        for(j = 0; j < NUM_BLOCKS - i - 1; j++)
        {
            if (block[j].value > block[j + 1].value)
            {
                // Swapping Values
                key = block[j + 1].value;
                block[j + 1].value = block[j].value;

                // Changing properties of the block when swapped
                block[j + 1].rectangle.setSize(sf::Vector2f(float(BLOCK_WIDTH), float(BLOCK_HEIGHT * block[j + 1].value)));
                block[j + 1].rectangle.setPosition(((j + 1) * 10) - BLOCK_WIDTH, WINDOW_HEIGHT - (BLOCK_HEIGHT * block[j + 1].value));

                // Creating swap highlight to track swapping
                block[j].rectangle.setFillColor(sf::Color(0, 250, 0));
                block[j + 1].rectangle.setFillColor(sf::Color(250, 250, 250));

                // Update frame
                window.clear();
                render::draw_frame(window, block, NUM_BLOCKS);
                window.display();

                // Swapping Values
                block[j].value = key;

                // Changing properties of the block when swapped
                block[j].rectangle.setSize(sf::Vector2f(float(BLOCK_WIDTH), float(BLOCK_HEIGHT * block[j].value)));
                block[j].rectangle.setPosition(((j) * 10) - BLOCK_WIDTH, WINDOW_HEIGHT - (BLOCK_HEIGHT * block[j].value));

                // Changing block colour to white
                block[j].rectangle.setFillColor(sf::Color(250, 250, 250));

                // Update Frame
                render::update_frame(window, block, event);
            } // End if
        } // End For

        // Update Frame
        render::update_frame(window, block, event);
    } // End For

    return false;
} // End bool sort_algo::sort::bubble_sort(sf::RenderWindow& window, block* block, bool *new_sort)

// Merge Sort
bool sort_algo::sort::merge_sort::merge_split(sf::RenderWindow& window, block* block, bool* new_sort, int first, int last, sf::Event *event)
{
    // Vars
    int *mid = new int;
    *mid = 0;

    // Check if the sub arrays have reached a size of 1
    if (first >= last)
        return false;

    else
    {
        // Calculating the middle value
        *mid = first + (last - first) / 2;

        // Split bottom half
        sort_algo::sort::merge_sort::merge_split(window, block, new_sort, first, *mid, event);

        // Split top half
        sort_algo::sort::merge_sort::merge_split(window, block, new_sort, (*mid) + 1, last, event);

        // Merge the arrays back together
        sort_algo::sort::merge_sort::merge(window, block, new_sort, first, *mid, last, event);
    } // End else

    // Clear Memory
    delete mid;

    return false;
} // End void sort_algo::sort::merge_sort::merge_split(block*)

void sort_algo::sort::merge_sort::merge(sf::RenderWindow& window, block* block, bool* new_sort, int first, int mid, int last, sf::Event *event)
{
    // Vars
    int i = 0;
    int j = 0;
    int h = 0;

    int size_L_subarray = 0;
    int size_R_subarray = 0;

    // Calculating Size of subarrays
    size_L_subarray = mid - first + 1;
    size_R_subarray = last - mid;

    // Creating temp subarrays
    unsigned int* left_subarray = new unsigned int[size_L_subarray];
    unsigned int* right_subarray = new unsigned int[size_R_subarray];

    // Putting data into subarrays
    for (i = 0; i < size_L_subarray; i++)
        left_subarray[i] = block[first + i].value;

    for (j = 0; j < size_R_subarray; j++)
        right_subarray[j] = block[mid + j + 1].value;

    // Creating index's
    i = 0;
    j = 0;
    h = first ;

    // 
    while (i < size_L_subarray && j < size_R_subarray)
    {
        if (left_subarray[i] <= right_subarray[j])
        {
            // Swap Values
            block[h].value = left_subarray[i];

            // Change Properties of Blocks
            // Changing properties of the block when swapped
            block[h].rectangle.setSize(sf::Vector2f(float(BLOCK_WIDTH), float(BLOCK_HEIGHT * block[h].value)));
            block[h].rectangle.setPosition(((h - 1) * 10) - BLOCK_WIDTH, WINDOW_HEIGHT - (BLOCK_HEIGHT * block[h].value));

            // Creating swap highlight to track swapping
            block[h].rectangle.setFillColor(sf::Color(0, 250, 0));
            block[i].rectangle.setFillColor(sf::Color(250, 250, 250));

            // Update Frame
            render::update_frame(window, block, event);

            // Increment
            i++;
        } // End if

        else
        {
            // Swap Values
            block[h].value = right_subarray[j];

            // Change Properties of Blocks
            // Changing properties of the block when swapped
            block[h].rectangle.setSize(sf::Vector2f(float(BLOCK_WIDTH), float(BLOCK_HEIGHT * block[h].value)));
            block[h].rectangle.setPosition(((h - 1) * 10) - BLOCK_WIDTH, WINDOW_HEIGHT - (BLOCK_HEIGHT * block[h].value));

            // Creating swap highlight to track swapping
            block[h].rectangle.setFillColor(sf::Color(0, 250, 0));
            block[j].rectangle.setFillColor(sf::Color(250, 250, 250));

            // Update Frame
            render::update_frame(window, block, event);

            j++;
        } // End else

        // Changing block colour to white
        block[h].rectangle.setFillColor(sf::Color(250, 250, 250));

        h++;
    } // End while

    while (i < size_L_subarray)
    {
        // Swap Values
        block[h].value = left_subarray[i];

        // Change Properties of Blocks
        // Changing properties of the block when swapped
        block[h].rectangle.setSize(sf::Vector2f(float(BLOCK_WIDTH), float(BLOCK_HEIGHT * block[h].value)));
        block[h].rectangle.setPosition(((h - 1) * 10) - BLOCK_WIDTH, WINDOW_HEIGHT - (BLOCK_HEIGHT * block[h].value));

        // Creating swap highlight to track swapping
        block[h].rectangle.setFillColor(sf::Color(0, 250, 0));
        block[i].rectangle.setFillColor(sf::Color(250, 250, 250));

        // Update Frame
        render::update_frame(window, block, event);

        // Changing block colour to white
        block[h].rectangle.setFillColor(sf::Color(250, 250, 250));

        // Update Frame
        render::update_frame(window, block, event);

        i++;
        h++;
    } // End while

    while (j < size_R_subarray)
    {
        // Swap Values
        block[h].value = right_subarray[j];

        // Change Properties of Blocks
        // Changing properties of the block when swapped
        block[h].rectangle.setSize(sf::Vector2f(float(BLOCK_WIDTH), float(BLOCK_HEIGHT * block[h].value)));
        block[h].rectangle.setPosition(((h - 1) * 10) - BLOCK_WIDTH, WINDOW_HEIGHT - (BLOCK_HEIGHT * block[h].value));

        // Creating swap highlight to track swapping
        block[h].rectangle.setFillColor(sf::Color(0, 250, 0));
        block[j].rectangle.setFillColor(sf::Color(250, 250, 250));

        // Update Frame
        render::update_frame(window, block, event);

        // Changing block colour to white
        block[h].rectangle.setFillColor(sf::Color(250, 250, 250));

        // Update Frame
        render::update_frame(window, block, event);

        j++;
        h++;

    } // End while

    // Clear Memory
    delete[] left_subarray;
    delete[] right_subarray;
} // End void sort_algo::sort::merge_sort::merge(sf::RenderWindow& window, block* block, bool* new_sort, int first, int mid, int last, sf::Event *event)
