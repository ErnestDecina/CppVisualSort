/*
Library Desc: Contains all sorting functions that include window frame updates
Author: Ernest John Decina
Date: 31 May 2022
*/

// sort_algo.h
#pragma once

// Libraries 
#include "render.h"


namespace sort_algo
{
	class sort
	{
	public:
		static bool insertion_sort(sf::RenderWindow&, struct block*, bool*, sf::Event*);
		static bool bubble_sort(sf::RenderWindow&, struct block*, bool*, sf::Event*);

		// Merge Sort, requires 2 functions
		
		class merge_sort
		{
		public:
			static bool merge_split(sf::RenderWindow&, struct block*, bool*, int, int, sf::Event*);
			static void merge(sf::RenderWindow&, struct block*, bool*, int, int, int, sf::Event*);
		};
	};
} // End namespace sort_algo

