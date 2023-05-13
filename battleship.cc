#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

const int BOARD_SIZE = 5;
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
		}

		void print() {
			cout << "  ";
			for (int i = 0; i < BOARD_SIZE; i++)
				cout << static_cast<char>(i + 65) << " ";
			cout << endl;

			for (int i = 0; i < BOARD_SIZE; i++) {
				cout << i << " ";
				for (int j = 0; j < BOARD_SIZE; j++) {
					cout << board.at(i).at(j) << " ";
				}
				cout << endl;
			}
		}

		bool placeShip(int row, int col, int size, bool horizontal) {
			if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE)
				return false;

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
			if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE)
				return false;

			if (board.at(row).at(col) == '#') {
				board.at(row).at(col)  = 'X';

				for (Ship& ship : ships) {
					if (!ship.isSunk()) {
						ship.add_hit();
						if (ship.isSunk())
							shipsRemaining--;
						break;
					}
				}
			} 
			else if (board.at(row).at(col) == '-') {
				board.at(row).at(col) = 'O';
			}

			return true;
		}

		bool gameOver() const {
			return shipsRemaining == 0;
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

void battleShipRound(Board &pBoard){
	
}

int main() {
	Board board;

	// Randomly place ships
	randomizeShips(board);

	// Game logic
	int row, col;
	while (!board.gameOver()) {
		board.print();

		cout << "Enter row and column to attack (0-" << BOARD_SIZE - 1 << "): ";
		cin >> row >> col;

		if (!board.attack(row, col)) {
			cout << "Invalid move! Try again." << endl;
		}
	}

	cout << "Congratulations! You have sunk all the ships!" << endl;

	return 0;
}

