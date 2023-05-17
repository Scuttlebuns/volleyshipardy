#pragma once
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include "interactions.h"
using namespace std;

const int BOARD_SIZE = 7;
const int NUM_SHIPS = 3;
const vector<int> SHIP_SIZES = {3,2,1};

class Ship {
	private:
		int size;
		int hits;
	public:
		Ship(int size) : size(size), hits(0) {}

		bool isSunk() const {
			return hits == size;
		}

		void add_hit() {
			hits++;
		}

};

class Board {
	private:
		vector<vector<char>> board;
		vector<Ship> ships;
		int shipsRemaining;
	public:
		Board() {
			board = vector<vector<char>>(BOARD_SIZE, vector<char>(BOARD_SIZE, '-'));
			shipsRemaining = NUM_SHIPS;
		
			for(int i = 0; i < NUM_SHIPS; i++){
				Ship ship(SHIP_SIZES.at(i));
				ships.push_back(ship);
			}
		}

		char getPosition(int row, int col) const { return board.at(row).at(col); }

		int getShipsRemaining() const { return shipsRemaining; }

		void print() {
			cout << "\t";
			for (int i = 0; i < BOARD_SIZE; i++)
				cout << MAGENTA <<  i << "\t" << RESET;
			cout << endl;
			cout << endl;

			for (int i = 0; i < BOARD_SIZE; i++) {
				cout << MAGENTA <<  static_cast<char>(i+65) << "\t" << RESET;
				for (int j = 0; j < BOARD_SIZE; j++) {
					if (board.at(i).at(j) == '#') cout << CYAN << '-' << "\t" << RESET; //ships
					else if(board.at(i).at(j) == 'O') cout << BOLDWHITE << board.at(i).at(j)  << "\t" << RESET; //misses
					else if(board.at(i).at(j) == 'X') cout << BOLDRED << board.at(i).at(j)  << "\t" << RESET; // hits
					else cout << CYAN << board.at(i).at(j) << "\t" << RESET; //ocean
				}
				cout << endl;
				cout << endl;
			}
		}
		/*
		   void print() {
		   cout << "  ";
		   for (int i = 0; i < BOARD_SIZE; i++)
		   cout << i << " ";
		   cout << endl;

		   for (int i = 0; i < BOARD_SIZE; i++) {
		   cout << static_cast<char>(i+65) << " ";
		   for (int j = 0; j < BOARD_SIZE; j++) {
		   if (board.at(i).at(j) == '#') cout << '-' << " ";
		   else cout << board.at(i).at(j) << " ";
		   }
		   cout << endl;
		   }
		   }
		   */

		bool placeShip(int row, int col, int size, bool horizontal) {
			if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE) return false;
			if (horizontal) {
				if (col + size > BOARD_SIZE)
					return false;

				for (int i = col; i < (col + size); i++) {
					if (board.at(row).at(i) != '-')
						return false;
				}

				for (int i = col; i < (col + size); i++) {
					board.at(row).at(i) = '#';
				}
			} 
			else {
				if (row + size > BOARD_SIZE)
					return false;

				for (int i = row; i < row + size; i++) {
					if (board.at(i).at(col) != '-')
						return false;
				}

				for (int i = row; i < (row + size); i++) {
					board.at(i).at(col) = '#';
				}
			}
			return true;
		}

		bool attack(int row, int col) {
			if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE) return false;
			if (board.at(row).at(col) == 'X' or board.at(row).at(col) == 'O') return false;
			if (board.at(row).at(col) == '#') {
				board.at(row).at(col)  = 'X';

				for (Ship& ship : ships) {
					if (!ship.isSunk()) {
						ship.add_hit();
						if (ship.isSunk()){
							shipsRemaining--;
						}
						break;
					}
				}
			} 
			else if (board.at(row).at(col) == '-') {
				board.at(row).at(col) = 'O';
			}
			return true;
		}

		int gameOver() const {
			return shipsRemaining;
		}

};

void randomizeShips(Board& board) {
	srand(time(0)); // Seed the random number generator with current time

	for (int i = 0; i < NUM_SHIPS; i++) {
		bool placed = false;

		while(!placed){
			int row = rand() % BOARD_SIZE;
			int col = rand() % BOARD_SIZE;
			bool horizontal = rand() % 2 == 0;

			placed = board.placeShip(row, col, SHIP_SIZES.at(i), horizontal);

		}
	}
}

void battleshipTurn(Board &playerBoard, Player &player){
	bigDialog("BATTLESHIP");
	int turns = 3;

	while (turns > 0){
		bigDialog("BATTLESHIP");
		cout << "Welcome to battleship!, you have 3 chances to hit the enemy ships!" << endl;
		cout << player.get_name() << " turn!" << endl;
		cout << turns << " turns remaining " << endl;
		char row = 'Z';
		int col = 100;

		playerBoard.print();
		cout << "Enter (ROW, COL) to attack: ";

		while (true) {
			try {
				if (!(cin >> row >> col)) {
					throw runtime_error("Invalid input! Enter (ROW COL) to attack.");
				}

				//clears buffer;
				cin.ignore(numeric_limits<streamsize>::max(), '\n');

				row = toupper(row);
				if ((row >= 'A' && row <= 'G') && (col >= 0 && col <= 6)) {
					break;
				} 
				else {
					throw runtime_error("Invalid input! Enter (ROW COL) to attack.");
				}
			} catch (const exception& e) {
				cout << e.what() << endl;
				cout << "Please try again." << endl;

				//clears buffer
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
		}

		int iRow = static_cast<int>(row-65);
		if (!playerBoard.attack(iRow, col)) {
			cout << "INVALID MOVE, try again!" << endl;
			usleep(2'000'000);
		}
		else if (playerBoard.getPosition(iRow, col) == 'X'){
			cout << "HIT" << endl;
			usleep(2'000'000);
			turns--;
		}
		else {
			cout << "MISS" << endl;
			usleep(2'000'000);
			turns--;
		}
	}
	clearscreen();
	movecursor(0,0);
	bigDialog("BATTLESHIP");
	cout << "Round concluded!" << endl;
	playerBoard.print(); //prints board on turn 3
	usleep(2'000'000);
	player.set_turn(false);
}
