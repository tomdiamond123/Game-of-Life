#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <random>

const int fractionAlive {2};
const int gridHeight {100};
const int gridWidth {100};
const float scale {10};


using intGameGrid = std::array<std::array<int, gridHeight>, gridWidth>;

intGameGrid initGrid(){
	intGameGrid grid {};

	std::mt19937 mt{std::random_device{}()};//initialise seed
	std::uniform_int_distribution zeroOrOne{0,1}; // creates random number generator for either 0 or 1
	
	for(auto& row : grid){
		for(auto& square: row){
			square = zeroOrOne(mt);
		}
	}
	return grid;
}

void displayGrid(const intGameGrid grid, sf::RenderWindow& window){
	for (int row {0}; row<gridHeight; row++){
		for (int col {0}; col<gridWidth; col++){
			if (grid[row][col] == 1){
				sf::RectangleShape square({scale,scale});
				square.setPosition({static_cast<float>(col*scale),static_cast<float>(row*scale)});
				square.setFillColor(sf::Color(255, 255, 255));
				window.draw(square);
			}
		}
	}
}

intGameGrid updateBoardByRules(intGameGrid grid){
	intGameGrid newGrid {grid};

	for (int row{0}; row<gridHeight; row++){
		for (int col{0}; col<gridWidth; col++){
			int numAlive {0};

			for (int diffRow{-1}; diffRow<=1; diffRow++){
				for (int diffCol{-1}; diffCol<=1; diffCol++){
					if (diffRow == 0 && diffCol == 0){
						continue;
					}
					//finds neighbour (% allows loop across screen, +gridHeight/gridWidth forces positive numbers)
					int neighbour {grid[((row+diffRow) + gridHeight) % gridHeight][((col+diffCol) + gridHeight) % gridWidth]};
					
					if (neighbour == 1){
						numAlive += 1;
					}
				}
			}

			if (numAlive < 2 || numAlive > 3){
				newGrid[row][col] = 0;
			} 
			else if(numAlive == 3){
				newGrid[row][col] = 1;
			} 
			else if(numAlive == 2){
				newGrid[row][col] = grid[row][col];
			}
		}
	}

	return newGrid;
}

int main()
{
	sf::RenderWindow window( sf::VideoMode( { static_cast<unsigned int>(gridHeight*scale), static_cast<unsigned int>(gridWidth*scale) } ), "GameOfLife" );
	window.setFramerateLimit(10);
	intGameGrid grid = initGrid();

	while ( window.isOpen() )
	{
		while ( const std::optional event = window.pollEvent() )
		{
			if ( event->is<sf::Event::Closed>() )
				window.close();
		}

		grid = updateBoardByRules(grid);
		window.clear();
		displayGrid(grid, window);
		window.display();
		
	}
}
