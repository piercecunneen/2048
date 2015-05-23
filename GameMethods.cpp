/*
 * game.cpp
 *
 *  Created on: Mar 20, 2015
 *      Author: piercecunneen
 */
#include "Game.hpp"

Gameboard::Gameboard (){
	board_.resize(4);
	for (int i = 0; i < 4; ++i){
		board_[i].resize(4);
		for (int j = 0; j < 4; ++j){
			board_[i][j] = 0;
		}
	}
	score_ = 0;
}
int Gameboard::MaxTile(){
	vector <vector <int> >::iterator iter;
	vector <int>::iterator iter2;
	int Max_tile = board_[0][0];
	for (iter = board_.begin(); iter != board_.end(); ++iter){
		for (iter2 = iter-> begin(); iter2 != iter -> end(); ++iter2){
			Max_tile = max(Max_tile, *iter2);

		}
	}
	return Max_tile;
}
void Gameboard::Clear(){
	for (int i = 0; i < 4; ++i){;
	for (int j = 0; j < 4; ++j){
		board_[i][j] = 0;
	}
	}
	score_ = 0;
}


void Gameboard::display_gameboard (){
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j){
			cout << board_[i][j] << "  ";
		}
		cout << endl;
	}
}
void Gameboard::InsertRandomPiece (){
	double random_value;
	int new_element;
	vector <vector <int> > zero_elements;
	vector <int> rand_vector;
	random_value = rand()/ (double) RAND_MAX;
	if (random_value <=.9){
		new_element = 2;
	}
	else{
		new_element = 4;
	}
	vector <int> m;
	for (int row = 0; row < 4; ++row) {
		for (int column = 0; column < 4; ++column){
			m.resize(0);
			if (board_[row][column] == 0) {
				m.push_back(row);
				m.push_back(column);
				zero_elements.push_back(m);
			}

		}
	}
	random_value = rand() % zero_elements.size();
	rand_vector = zero_elements[random_value];
	board_[rand_vector[0]][rand_vector[1]] = new_element;
}

bool Gameboard::CanInsert(){
	for (vector <vector <int> >::iterator it=board_.begin(); it != board_.end(); ++it){
		for (vector <int>::iterator iter2 = it-> begin(); iter2 != it->end(); ++iter2) {
			if (*iter2 == 0) {
				cout << "True" << endl;
				return true;
			}
		}
	}
	cout << "False" << endl;
	return false;
}

void Gameboard::Move(char direction) {
	int row, column, check = 0;
	char left = 'a', right = 'd', up = 'w';

	if (direction == left){
		row = 0;
		while (row <= 3){
			column = 0;
			while (column < 3){
				if (is_zeros_left(row, column +1)){
					break;
				}
				else {
					if (CanCombine(row, column, direction)){
						if (board_[row][column] == board_[row][column+1] && board_[row][column] != 0){
							check = 1;
							score_ += board_[row][column] * 2;
						}
						board_[row][column] = board_[row][column] + board_[row][column + 1];
						for (int j = column + 1; j < 3; ++j){
							board_[row][j] = board_[row][j+1];
						}
						board_[row][3] = 0;
						if (check){
							++column;
						}
						check = 0;
					}
					else
						++column;

				}
			}
			++row;
		}
	}
	else if (direction == right){
		row = 0;
		while (row <= 3){
			column = 3;
			while (column > 0){
				if (is_zeros_right(row, column -1)){
					break;
				}
				else {
					if (CanCombine(row, column, direction)){
						if (board_[row][column] == board_[row][column-1] && board_[row][column] != 0){
							check = 1;
							score_ += board_[row][column] * 2;
						}
						board_[row][column] = board_[row][column] + board_[row][column -1];
						for (int j = column - 1; j > 0; --j){
							board_[row][j] = board_[row][j-1];
						}
						board_[row][0] = 0;
						if (check){
							--column;
						}
						check = 0;
					}
					else
						--column;

				}
			}
			++row;

		}
	}
	else if (direction == up){
		column = 0;
		while (column <= 3){
			row = 0;
			while (row < 3){
				if (is_zeros_up(row +1, column)){
					break;
				}
				else {
					if (CanCombine(row, column, direction)){
						if (board_[row][column] == board_[row + 1][column] && board_[row][column] != 0){
							check = 1;
							score_ += board_[row][column] * 2;
						}
						board_[row][column] = board_[row][column] + board_[row + 1][column];
						for (int j = row + 1; j < 3; ++j){
							board_[j][column] = board_[j + 1][column];
						}
						board_[3][column] = 0;
						if (check){
							++row;
						}
						check = 0;
					}
					else
						++row;
				}
			}
			++column;

		}
	}

	else {
		column = 0;
		while (column <= 3){
			row = 3;
			while (row > 0){
				if (is_zeros_down(row - 1, column)){
					break;
				}
				else {
					if (CanCombine(row, column, direction)){
						if (board_[row][column] == board_[row][column] && board_[row - 1][column] != 0){
							check = 1;
							score_ += board_[row][column] * 2;
						}
						board_[row][column] = board_[row][column] + board_[row-1][column];
						for (int j = row - 1; j >0; --j){
							board_[j][column] = board_[j-1][column];
						}
						board_[0][column] = 0;
						if (check){
							--row;
						}
						check = 0;
					}
					else
						--row;

				}
			}
			++column;

		}
	}
}

bool Gameboard::is_zeros_left(int row, int starting_column){
	bool c(true);
	for (int i = starting_column; i <= 3; ++i){
		if ( board_[row][i] != 0) {
			c = false;
		}
	}
	return c;
}
//bool Gameboard::is_zeros_left(vector <vector <int> >::iterator row, vector <int>::iterator col){
//	for (vector <int>::iterator i = col; i != row-> end(); ++i){
//		if (*i != 0){
//			return false;
//		}
//	}
//	return true;
//}
bool Gameboard::is_zeros_right(int row, int starting_column){
	bool c(true);
	for (int i = starting_column; i >=0 ;--i ){
		if ( board_[row][i] != 0) {
			c = false;
		}
	}
	return c;
}
//bool is_zeros_right(vector <vector <int> >::iterator row, vector <int>::iterator col){
//	for (vector <int>:: i = col; i != )
//}
bool Gameboard::is_zeros_up(int starting_row, int column){
	bool c(true);
	for (int i = starting_row; i <= 3; ++i){
		if ( board_[i][column] != 0) {
			c = false;
		}
	}
	return c;
}
bool Gameboard::is_zeros_down(int starting_row, int column){
	bool c(true);
	for (int i = starting_row; i >= 0; --i){
		if ( board_[i][column] != 0) {
			c = false;
		}
	}
	return c;
}
bool Gameboard::CanCombine(int row, int column, char direction){
	int element = board_[row][column];
	switch (direction){
	case 'a':
		if (element != 0){
			if (board_[row][column + 1] == 0 || board_[row][column + 1] == element){
				return true;
			}
			else
				return false;
		}
		else {
			return true;
		}
	case 'd':
		if (element != 0){
			if (board_[row][column -1] == 0 || board_[row][column -1] == element){
				return true;
			}
			else
				return false;
		}
		else {
			return true;
		}
	case 'w':
		if (element != 0){
			if (board_[row+1][column] == 0 || board_[row+1][column] == element){
				return true;
			}
			else
				return false;
		}
		else {
			return true;
		}
	case 's':
		if (element != 0){
			if (board_[row-1][column] == 0 || board_[row-1][column] == element){
				return true;
			}
			else
				return false;
		}
		else {
			return true;
		}
	}
}

bool Gameboard::CanMove(char direction){
	switch (direction){
	case 'a':
		//		for (int i = 0; i < 4; ++i){
		//			for (int j = 1; j < 4; ++j){
		for (vector <vector <int> >::iterator iter1 = board_.begin(); iter1 != board_.end(); ++iter1){
			for (vector <int>::iterator iter2 = iter1 -> begin() + 1; iter2 != iter1 -> end(); ++iter2){
				//				if ((board_[i][j-1] == 0 && board_[i][j] != 0) || (board_[i][j-1] == board_[i][j] && board_[i][j] != 0))
				if ((*(iter2 -1) == 0 && *iter2 != 0) || (*(iter2-1) == *iter2 && *iter2 != 0)){
					return true;
				}
			}
		}
		break;
	case 'd':
		//		for (int i = 0; i < 4; ++i){
		//			for (int j = 2; j > -1; --j){
		for (vector <vector <int> >::iterator iter1 = board_.begin(); iter1 != board_.end(); ++iter1){
			for (vector <int>::iterator iter2 = iter1 -> end() - 1; iter2 != iter1 -> begin(); --iter2){
				//				if ((board_[i][j+1] == 0 && board_[i][j] != 0) || (board_[i][j+1] == board_[i][j] && board_[i][j] != 0))
				if ((*(iter2 +1) != 0 && *iter2 == 0) || ((*(iter2+1) == *iter2) && (*(iter2 + 1) != 0)))
					return true;
			}
		}
		break;
	case 'w':
		for (int i = 1; i < 4; ++i){
			for (int j = 0; j < 4; ++j){
				// for (vector <vector <int> >::iterator iter1 = board_.begin() + 1; iter1 != board_.end(); ++iter1){
				//	for (vector <int>::iterator iter2 = iter1 -> begin(); iter2 != iter1 -> end(); iter2){

				if ((board_[i-1][j] == 0 && board_[i][j] != 0) || (board_[i-1][j] == board_[i][j] && board_[i][j] != 0))
					return true;
			}
		}
		break;
	case 's':
		for (int i = 2; i > -1; --i){
			for (int j = 0; j < 4; ++j){
				if ((board_[i+1][j] == 0 && board_[i][j] != 0) || (board_[i+1][j] == board_[i][j] && board_[i][j] != 0))
					return true;
			}
		}
		break;
	}
	return false;
}
bool Gameboard::CanMove(){
	// for (int i = 0; i < 4; ++i){
	// 	for (int j = 1; j < 4; ++j){
	for (vector <vector <int> >::iterator iter1 = board_.begin(); iter1 != board_.end(); ++iter1){
		for (vector <int>::iterator iter2 = iter1 -> begin() + 1; iter2 != iter1 -> end(); ++iter2){
			// if ((board_[i][j-1] == 0 && board_[i][j] != 0) || (board_[i][j-1] == board_[i][j] && board_[i][j] != 0))
			if ((*(iter2 -1) == 0 && *iter2 != 0) || (*(iter2-1) == *iter2 && *iter2 != 0)){
				return true;
			}
		}
	}
	// for (int i = 0; i < 4; ++i){
	// 	for (int j = 2; j > -1; --j){
	for (vector <vector <int> >::iterator iter1 = board_.begin(); iter1 != board_.end(); ++iter1){
		for (vector <int>::iterator iter2 = iter1 -> end() - 1; iter2 != iter1 -> begin(); --iter2){
			// 		if ((board_[i][j+1] == 0 && board_[i][j] != 0) || (board_[i][j+1] == board_[i][j] && board_[i][j] != 0))
			if ((*(iter2) == 0 && *(iter2-1) != 0) || (*(iter2-1) == *iter2 && *iter2 != 0))
				return true;
		}
	}
	for (int i = 1; i < 4; ++i){
		for (int j = 0; j < 4; ++j){
			if ((board_[i-1][j] == 0 && board_[i][j] != 0) || (board_[i-1][j] == board_[i][j] && board_[i][j] != 0))
				return true;
		}
	}

	for (int i = 2; i > -1; --i){
		for (int j = 0; j < 4; ++j){
			if ((board_[i+1][j] == 0 && board_[i][j] != 0) || (board_[i+1][j] == board_[i][j] && board_[i][j] != 0))
				return true;
		}
	}

	return false;
}
vector< vector <int> > Gameboard::Openings(){
	vector <vector < int> > openings;
	for (int i = 0; i < 4; ++i){
		for (int j = 0; j < 4; ++j){
			if (board_[i][j] == 0){
				vector <int> new_vec;
				new_vec.push_back(i); new_vec.push_back(j);
				openings.push_back(new_vec);
			}
		}
	}
	return openings;

}
void Gameboard:: InsertTile(int row, int column){
	double num = rand()/ (double) RAND_MAX;
	if (num <=.9){
		board_[row][column] = 2;
	}
	else{
		board_[row][column] = 4;
	}
}
double Gameboard:: GradiantCalculator(){
	vector <vector <double> > grad1;
	grad1.resize(4);

	for (int i = 0; i < 4; ++i){
		grad1.resize(4);
		for (int j = 0; j < 4; ++j){
			// element = pow(2,3 - i - j);
			int element = 3-i-j;
			grad1[i].push_back(element);

		}
	}
	double sum1(0);
	for (int i = 0; i < 4; ++i){
		for (int j = 0; j < 4; ++j){
			sum1 = sum1 + grad1[i][j] * board_[i][j];

		}
	}
	return sum1;
}

void Expectimax(Gameboard board, int depth, double & num1, double & num2, double & num3){
	if (depth == 1){
		double temp = 1;
		double grad1 = board.GradiantCalculator();
		if (grad1 > 1){
			temp = grad1;
		}

		temp *= pow(1.1, board.SmoothnessCalculator() *.5);
		num1 += temp;
	}
	else if (depth % 2 != 0){
		vector <vector <int> >openings = board.Openings();
		for (int i = 0; i < openings.size(); ++i){
			Gameboard new_board = board;
			new_board.InsertTile(openings[i][0], openings[i][1]);
			Expectimax(new_board, depth-1, num1, num2, num3);
		}

	}



	else {
		char left = 'a', right = 'd', down = 's', up = 'w';
		Gameboard left_board = board, right_board = board, down_board = board, up_board = board;
		left_board.Move(left); right_board.Move(right);up_board.Move(up); down_board.Move(down);
		bool DidMove = false;
		if (board.CanMove(left)){
			Expectimax(left_board, depth-1, num1, num2, num3);
			DidMove = true;

		}
		if (board.CanMove(right)){
			Expectimax(right_board, depth-1, num1, num2, num3);
			DidMove = true;

		}
		if (board.CanMove(up)){
			Expectimax(up_board, depth-1, num1, num2,num3);
			DidMove = true;

		}
		if (board.CanMove(down)){
			Expectimax(down_board, depth-1, num1, num2, num3);
			DidMove = true;

		}
		//		if (!DidMove)
		//			num1 *= .85;
	}

}

bool Gameboard::HighestTileInCorner(){
	int corner = board_[0][0];
	int max_element;
	for (vector< vector <int> >::iterator it = board_.begin(); it != board_.end(); ++it){
		for(vector <int>::iterator iter2 = it-> begin(); iter2 != it -> end(); ++iter2 ){
			max_element = max(*iter2, max_element);
		}
	}
	if (max_element == corner){
		return true;
	}
	else
		return false;
}
char ComputerMove(Gameboard board){
	Gameboard left_copy = board , right_copy = board, up_copy = board, down_copy = board;
	int left_score(0), right_score(0), up_score(0), down_score(0), max_score = 0;
	char left = 'a', right = 'd', up = 'w', down = 's';
	left_copy.Move('a'); right_copy.Move('d'); up_copy.Move('w'); down_copy.Move('s');
	if (board.CanMove(left)){
		left_score = left_copy.GradiantCalculator();
	}
	if (board.CanMove(right)){
		right_score = right_copy.GradiantCalculator();
	}
	if (board.CanMove(up)){
		up_score = up_copy.GradiantCalculator();
	}
	if (board.CanMove(down)){
		down_score = down_copy.GradiantCalculator();
	}
	max_score = left_score;
	if (right_score > max_score){
		max_score = right_score;
	}
	if (up_score > max_score){
		max_score = up_score;
	}
	if (down_score > max_score){
		max_score = down_score;
	}
	if (max_score == left_score){
		return left;
	}
	else if (max_score ==right_score){
		return right;
	}
	else if (max_score == up_score){
		return up;
	}
	else if (max_score == down_score){
		return down;
	}
	else{
		return 'q';
	}
}

char ComputerMoveExpectimax(Gameboard board, int depth){
	Gameboard left_copy = board , right_copy = board, up_copy = board, down_copy = board;
	double left_score(0), right_score(0), up_score(0), down_score(0), max_score = 1;
	char left = 'a', right = 'd', up = 'w', down = 's';
	bool check(false);
	left_copy.Move('a'); right_copy.Move('d'); up_copy.Move('w'); down_copy.Move('s');

	if (board.CanMove(left)){
		check = true;
		double num1 = 0, num2 = 0, num3 = 0;
		Expectimax(left_copy, depth, num1, num2, num3);
		left_score = num1 + num2 + num3;
		if (left_copy.HighestTileInCorner()){
			left_score = pow(left_score, 3);
		}


	}
	if (board.CanMove(right)){
		double num1 = 0, num2 = 0, num3 = 0;
		Expectimax(right_copy, depth, num1, num2, num3);
		right_score= num1 + num2 +num3;
		if (right_copy.HighestTileInCorner()){
			right_score = pow(right_score, 3);
		}

	}
	if (board.CanMove(up)){
		double num1 = 0, num2 = 0, num3=0;
		Expectimax(up_copy, depth, num1, num2, num3);
		up_score = num1 + num2 + num3;
		if (up_copy.HighestTileInCorner()){
			up_score = pow(up_score, 3);
		}


	}
	if (board.CanMove(down)){
		double num1 = 0, num2 = 0, num3 = 0;
		Expectimax(down_copy, depth, num1, num2, num3);
		down_score = num1 + num2 + num3;
		if (down_copy.HighestTileInCorner()){
			down_score = pow(down_score, 3);
		}

	}



	//	if (right_score > max_score){
	//		max_score = right_score;
	//	}
	//	if (up_score >= max_score){
	//		max_score = up_score;
	//	}
	//	if (down_score > max_score){
	//		max_score = down_score;
	//	}

	max_score = max(max_score, left_score);
	max_score = max(max_score, right_score);
	max_score = max(max_score , down_score);
	max_score = max(max_score , up_score);

	if (max_score == left_score){
//		cout<< "Left" << endl;
		return left;
	}
	else if (max_score == right_score){
//		cout << "right" <<endl;
		return right;
	}
	else if (max_score == up_score){
//		cout << "Up"<< endl;
		return up;
	}
	else if (max_score == down_score){
//		cout << "Down" << endl;
		return down;
	}
	else{
//		cout << "Game over" << endl;
		return 'q';
	}
}

bool Gameboard::TopRowFilled(){
	for (vector <int>::iterator it= board_[0].begin(); it != board_[0].end(); ++it ){
		if (*it == 0){
			return false;
		}
	}
	return true;

}
double Gameboard::SmoothnessCalculator(){
	double horizontal_combinations = 0, vertical_combinations = 0;
	for (vector <vector <int> >::iterator row = board_.begin(); row != board_.end(); ++row){
		for (vector <int>::iterator column = row-> begin(); column != row-> end() - 1; ++column){
			if (*column == *column+1 && *column != 0){
				horizontal_combinations += 1;
			}
		}
	}
	for (int col = 0; col < 4; ++col){
		for (int row = 0; row < 3; ++row){
			if (board_[row][col] == board_[row+1][col] && board_[row][col] != 0){
				vertical_combinations += 1;
			}
		}
	}
	return horizontal_combinations + vertical_combinations * 5;
}




