/*
Library Desc:
Author: Ernest John Decina
Date: 31 May 2022
*/

// render.h
#pragma once

// Libraries
#include "block.h"
#include "sort_algo.h"
#include <Windows.h>
#include <stdlib.h>
#include <time.h>
// 
namespace render
{
	void draw_frame(sf::RenderWindow&, struct block*, int);
	void update_frame(sf::RenderWindow&, struct block*, sf::Event*);
	void rendering_options(sf::RenderWindow&, struct block*, char*, bool *, sf::Event *);
}