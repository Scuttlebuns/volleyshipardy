#pragma once
#include "read.h"
#include "colors.h"
#include <string>
#include <vector>
using namespace std;

const auto [ROWS, COLS] = get_terminal_size();

void printBorder() {
	for (int i = 0; i < COLS; i++) {
		cout << GREEN << "=" << RESET;
	}
	cout << endl;

	for (int i = 0; i < ROWS - 2; i++) {
		cout << GREEN << " " << RESET;
		for (int j = 0; j < COLS - 2; j++) {
			cout << " ";
		}
		cout << GREEN << " " << RESET << endl;
	}

	for (int i = 0; i < COLS; i++) {
		cout << GREEN << "=" << RESET;
	}
	cout << endl;
}

void dialog(string toPrint) {
	//clearscreen();
//	movecursor(ROWS/2, (COLS - toPrint.size()) / 2);
	system(("echo " + toPrint + " | lolcat").c_str());
	cout << toPrint << endl;
}

void bigDialog(string toPrint) {
	clearscreen();
	movecursor(0,0);
	system(("echo " + toPrint + " | figlet | lolcat").c_str());
}

void raw_on(){
	set_raw_mode(true);
	show_cursor(false);
}

void raw_off(){
	set_raw_mode(false);
	show_cursor(true);
}
