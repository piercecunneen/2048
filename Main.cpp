/*
 * SemesterProject.cpp
 *
 *  Created on: Mar 23, 2015
 *      Author: piercecunneen
 */
// 	   Depth 1: 100 runs
//		Average Score = 2177.64
//		Average Max Tile = 176.34
//		Number of 1024s = 0
//		Number of 2048s = 0
//		Number of 4096s = 0
//
// 	   Depth 3: 100 runs
//		Average Score = 16093.7
//		Average Max Tile = 1125.12
//		Number of 1024s = 55
//		Number of 2048s = 22
//		Number of 4096s = 0
// 	   Depth 5: 100 runs
//		Average Score = 19976.5
//		Average Max Tile = 1400.32
//		Number of 1024s = 51
//		Number of 2048s = 41
//		Number of 4096s = 0

#include "Game.hpp"

using namespace std;
int main() {
	srand(time(NULL)); rand();
	double total_score(0), MaxTile(0);
	int Num_trials = 1, depth = 3;
	int num_2048s = 0, num_1024s = 0, num_4096s = 0;
	Gameboard board;
	for (int i = 0; i < Num_trials; ++i){
		board.Clear();
		char move = 'p';
		while (move != 'q'){
			board.InsertRandomPiece();
			board.display_gameboard(); cout << endl << endl;
			if (board.CanMove())
				if (depth == 1)
					move = ComputerMove(board);
				else
					move = ComputerMoveExpectimax(board, depth);
			else
				move = 'q';
			if (move != 'q'){
				board.Move(move);
			}
		}
		total_score += board.Get_score();
		if (board.MaxTile() == 1024){
			num_1024s += 1;
		}
		if (board.MaxTile() == 2048){
			num_2048s += 1;
		}
		else if (board.MaxTile() > 2048){
			num_4096s += 1;
		}
		MaxTile += board.MaxTile();


	}
	cout << "Average Score = " << total_score / Num_trials << endl;
	cout << "Average Max Tile = " << MaxTile / Num_trials << endl;
	cout << "Number of 1024s = " << num_1024s << endl;
	cout << "Number of 2048s = " << num_2048s << endl;
	cout << "Number of 4096s = " << num_4096s << endl;

	return 0;
}
