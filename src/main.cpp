#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <random>

const int fractionAlive {2};
const int gridHeight {100};
const int gridWidth {100};

template <typename T, std::size_t Row, std::size_t Col>
using Array2d = std::array<std::array<T, Col>, Row>;

Array2d<int, gridHeight, gridWidth> initGrid(){
	Array2d<int, gridHeight, gridWidth> grid {};

	std::mt19937 mt{std::random_device{}()};//initialise seed
	std::uniform_int_distribution zeroOrOne{0,1}; // creates random number generator for either 0 or 1
	
	for(auto& row : grid){
		for(auto& square: row){
			square = zeroOrOne(mt);
		}
	}
	return grid;
}

int main()
{
	sf::RenderWindow window( sf::VideoMode( { gridHeight*10, gridWidth*10 } ), "GameOfLife" );
	Array2d<int, gridHeight, gridWidth> grid = initGrid();
	for(auto& row : grid){
		for(auto& square: row){
			std::cout << square;
		}
		std::cout << '\n';
	}


	while ( window.isOpen() )
	{
		while ( const std::optional event = window.pollEvent() )
		{
			if ( event->is<sf::Event::Closed>() )
				window.close();
		}

		window.clear();
		//window.draw( shape );
		window.display();
		
	}
}
