/*
Program Desc: Creates the window for the application && displays all the sorting
    Program Allows:
        User to pick which sort
        Turn on Vsync (Slows sort since sorting is linked to frame rate)
        Start sorting


Author: Ernest John Decina
Date: 25 May 2022

Edited by:
Date:
*/

// Header File
#include "main.h"

// Function Prototypes
void vsync_option(bool*);
void type_sort(char *);
void start_sort(void);
void main_game_loop(sf::RenderWindow &, struct block *, char *, bool *);
void clearing_memory(struct block*);

// Driver code
int main()
{
    // Vars
    char sort_option = ' ';
    bool new_sort = true;
    bool vsync = NULL;
    struct block* block = nullptr;

    // Creating Shape
    block = blocks::create_blocks();

    // Asking User to turn on Vsync
    vsync_option(&vsync);
 
    // Main Application Loop
    while (sort_option != '5')
    {
        // Reset Variables
        new_sort = true;

        // User input choosing type of sort
        type_sort(&sort_option);

        // Break out of while loop if 5 was chosen
        if (sort_option == '4')
            break;

        // User input to start sorting
        start_sort();

        // Adding Properties && Shuffling data
        blocks::add_info_blocks(block);

        // Creating Window
        sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_NAME);
        window.setVerticalSyncEnabled(vsync);

        // Main game loop
        main_game_loop(window, block, &sort_option, &new_sort);
    } // End while Loop

    // Clearing Memory
    clearing_memory(block);

    // User Output
    std::cout << "" << std::endl;
    std::cout << "Progam Closed" << std::endl;
    
    // End Program
    return 0;
} // End main

// Functions

// void vsync_option(bool*)
// Function Desc:
// Parameter 1: Boolean Pointer, allows use to change state  (true || false) from main
void vsync_option(bool *vsync)
{
    char option = ' ';
    bool menu_status = true;

    do
    {
        std::cout << "Vsync Options" << std::endl;
        std::cout << "Y: Slows sorting visual (depending on refresh rate) but limits GPU Usage" << std::endl;
        std::cout << "N: Faster Sorting but uses alot of GPU resources" << std::endl;
        std::cout << "Choose Option: ";
        std::cin >> option;

        switch (option)
        {
            // Vsync ON
            case 'Y':
            {
                *vsync = true;

                // Ending Loop
                menu_status = false;

                break;
            } // End Case 'Y'

            // Vsync OFF
            case 'N':
            {
                *vsync = false;

                // Ending Loop
                menu_status = false;

                break;
            } // End Case 'N;
            default:
            {
                std::cout << "Invalid Option" << std::endl;
                std::cout << "" << std::endl;
            } // End default case
        } // End switch
    } while (menu_status == true); // End do while
} // End void vsync_option(bool*)

// void type_sort(int *)
// Function Desc: Allows the user to choose type of sort to use
// Parameter 1: integer pointer, allows user to change option type from main
void type_sort(char* option)
{
    // Vars
    int menu_status = 1;

    do
    {
        std::cout << "" << std::endl;
        std::cout << "1. Insertion sort" << std::endl;
        std::cout << "2. Bubble sort" << std::endl;
        std::cout << "3. Merge sort" << std::endl;
        std::cout << "4. End Program" << std::endl;
        std::cout << "Choose Option: ";
        std::cin >> *option;

        switch (*option)
        {
            // Insertion Sort
            case '1':
            {
                std::cout << "Option Chosen: Insertion sort" << std::endl;
                std::cout << "" << std::endl;
                menu_status = 0;
                break;
            } // End Case

            // Bubble Sort
            case '2':
            {
                std::cout << "Option Chosen: Bubble sort" << std::endl;
                std::cout << "" << std::endl;
                menu_status = 0;
                break;
            } // End Case

            // Merge Sort
            case '3':
            {
                std::cout << "Option Chosen: Merge sort" << std::endl;
                std::cout << "" << std::endl;
                menu_status = 0;
                break;
            } // End Case

            // Ending Program
            case '4':
            {
                std::cout << "Option Chosen: End Program" << std::endl;
                std::cout << "" << std::endl;
                menu_status = 0;
                break;
            } // End Case

            default:
                std::cout << "Invalid Option" << std::endl;
                std::cout << "" << std::endl;
                break;
            } // End default
    } while (menu_status == 1); // End do while loop
} // End void type_sort(int *)

// int start_sort(void)
// Function Desc: Allows user input to start the sort
void start_sort(void)
{
    // Vars
    char start = '0';

    std::cout << "Enter 1 to start: ";
    std::cin >> start;

    while (start != '1')
    {
        // Printing Error Message
        std::cout << "Invalid Option" << std::endl << std::endl;

        std::cout << "Enter 1 to start: ";
        std::cin >> start;

        std::cout << "" << std::endl;
    } // End while

    std::cout << "" << std::endl;

} // End int start_sort(void);

// void main_game_loop(sf::RenderWindow &)
// Function Desc: Main Loop of the whole program, allows to redisplay menu and display window multiple times
// Parameter 1: Window pointer, gain window functions
// Parameter 2: Structure block pointer to main, gain data to struct block
// Parameter 3: Character pointer, used to identify whay type of sort to use
// Parameter 4: Boolean pointer to tell the program to render a new sort.
void main_game_loop(sf::RenderWindow & window, struct block * block, char* option, bool *new_sort)
{
    // Main game loop
    while (window.isOpen())
    {
        // Event Loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Check if Window is closed
            if (event.type == sf::Event::Closed)
                window.close();

            // Check if ESCAPE key is pressed
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                } // End if
            } // End if
        } // End While

        // Clear Frame
        window.clear();

        // Rendering process
        render::rendering_options(window, block, option, new_sort, &event);

        // Display
        window.display();

    } // End while
} // End void main_game_loop(sf::RenderWindow &)

// void clearing_memory(struct block*)
// Function Desc: Clearing memory before ending program.
// Parameter 1: Sturcture pointer, getting address to clear memory
void clearing_memory(struct block* block)
{
    std::cout << "Clearing Memory" << std::endl;
    delete[] block;
} // End void clearing_memory(struct block*);