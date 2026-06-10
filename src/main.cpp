#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <random>

const int fractionAlive {2};
const int gridHeight {100};
const int gridWidth {100};
const float scale {10};

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

void displayGrid(const Array2d<int, gridHeight, gridWidth> grid, sf::RenderWindow& window){
	Array2d<int, gridHeight, gridWidth> newGrid = grid;
	for (int row = 0; row<gridHeight; row++){
		for (int col = 0; col<gridWidth; col++){
			// std::cout << "row: " << row << "  col: " << col << "  grid[row][col]: " << grid[row][col] << '\n';
			if (grid[row][col] == 1){
				sf::RectangleShape square({scale,scale});
				square.setPosition({static_cast<float>(col*scale),static_cast<float>(row*scale)});
				// square.setPosition({static_cast<float>(col),static_cast<float>(row)});
				square.setFillColor(sf::Color(255, 255, 255));
				window.draw(square);
			}
		}
	}
}

int main()
{
	sf::RenderWindow window( sf::VideoMode( { static_cast<unsigned int>(gridHeight*scale), static_cast<unsigned int>(gridWidth*scale) } ), "GameOfLife" );
	Array2d<int, gridHeight, gridWidth> grid = initGrid();
	// for(auto& row : grid){
	// 	for(auto& square: row){
	// 		std::cout << square;
	// 	}
	// 	std::cout << '\n';
	// }


	while ( window.isOpen() )
	{
		while ( const std::optional event = window.pollEvent() )
		{
			if ( event->is<sf::Event::Closed>() )
				window.close();
		}

		window.clear();
		displayGrid(grid, window);
		window.display();
		
	}
}
