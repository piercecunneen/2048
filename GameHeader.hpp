/*
 * Game.hpp
 *
 *  Created on: Mar 20, 2015
 *      Author: piercecunneen
 */

#ifndef HPP_GAME_HPP_
#define HPP_GAME_HPP_


#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cmath>
#include <numeric>
#include <unistd.h>
using namespace std;


class Gameboard {
private:
	vector <vector <int> > board_;
	int score_;
public:
	/*
	 * Initializes board_ as a 4 by 4 matrix of zeros  and sets score_ equal to zero
	 *
	 */
	Gameboard();

	/*
	 * sets value of each element in board_ to zero and sets score_ to zero
	 */
	void Clear();
	int Get_score(){
		return score_;
	}
	/*
	 * Inserts a 2 (90% of the time) or a 4 (10% of the time) into one of the openings at random
	 */
	void InsertRandomPiece ();

	/*
	 * returns True if there is an opening in the board for which a 2 or 4 can be inserted after a player makes a move
	 */
	bool CanInsert();

	/*
	 * returns True if a move can be made in a certain direction
	 * inputs: direction (type char)
	 */
	bool CanMove(char direction);

	/*
	 * returns True if a move can be made in any direction.
	 */
	bool CanMove();

	/*
	 * Makes a move in a certain direction.
	 *  Additionally, updates the game score every time two Tiles of equal value are combined, changing score_
	 *  inputs: direction (type char)
	 */
	void Move(char direction);

	/*
	 * displays the game board to the command window
	 */
	void display_gameboard ();
	//  bool is_zeros_left(vector <vector <int> >::iterator row, vector <int>::iterator col);

	/*
	 * Used in move function.
	 * Returns True if the elements in the rest of the row are zero from a certain index, starting at board_[row][column] and going left
	 * inputs: row (type int) and column (type int) of starting Tile
	 */
	bool is_zeros_left(int row, int column);
	// bool is_zeros_right(vector <vector <int> >::iterator row, vector <int>::iterator col);

	/*
	 * Used in move function.
	 * Returns True if the elements in the rest of the row are zero from a certain index, starting at board_[row][column] and going right
	 * inputs: row (type int) and column (type int) of starting Tile
	 */
	bool is_zeros_right(int row, int starting_column);
	//  bool is_zeros_up(vector <vector <int> >::iterator row, vector <int>::iterator col);

	/*
	 * Used in move function.
	 * Returns True if the elements in the rest of the column are zero from a certain index, starting at board_[row][column] and going up
	 * inputs: row (type int) and column (type int) of starting Tile
	 */
	bool is_zeros_up (int starting_row, int column);
	// bool is_zeros_down(vector <vector <int> >::iterator row, vector <int>::iterator col);


	/*
	 * Used in move function.
	 * Returns True if the elements in the rest of the column are zero from a certain index, starting at board_[row][column] and going down
	 * inputs: row (type int) and column (type int) of starting Tile
	 */
	bool is_zeros_down (int starting_row, int column);

	/*
	 * Used in Move function
	 * Returns True if in the inputted direction, two adjacent Tiles can combine
	 * Note: Tiles can combine if they are of equal values, or if one Tile is zero
	 * inputs: row (type int) and column (type int) of Tile that Move function is checking
	 */
	bool CanCombine(int row, int column, char direction);

	/*
	 * Checks whether the top row of the board has all non -zero tiles. If so, returns true
	 */
	bool TopRowFilled();

	/*
	 * Calculates the gradient score for the board, used to determine the board score for the 2048 AI
	 */
	double GradiantCalculator();

	/*
	 * returns the number of vertical and horizontal combinations that can be made by a board.
	 * Multiplies the vertical combination number by 5 in order to give them more weight when being used the determine the move for the AI
	 */
	double SmoothnessCalculator();

	/*
	 * Inserts a tile at a specified location in the board. Used for the expectimax algorithm
	 */
	void InsertTile(int row, int column);

	/*
	 * returns a vector that contains the indexes of all the openings in the board (i.e. where there is a zero Tile)
	 */
	vector <vector  <int> > Openings();

	/*
	 * returns true if the highest tile in the board is in the top left corner
	 */
	bool HighestTileInCorner();
	/*
	 * returns the value of the largest tile on the board
	 */
	int MaxTile();
};

/*
 * determines the direction the AI should choose to move at a depth of only 1. Thus, function
 * only looks at the 4 (or less) available moves and evaluates the board using the gradiant and smoothness heuristics
 * from the result of these four moves.
 *
 */
char ComputerMove(Gameboard board);


void Expectimax(Gameboard board, int depth, double & num1, double & num2, double & num3);

/*
 *
 *Creates four initial branches of expectimax search, then calls Expectimax function to complete rest of Expectimax algorithm
 */
char ComputerMoveExpectimax(Gameboard board, int depth);

#endif /* HPP_GAME_HPP_ */
