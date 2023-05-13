#include "/public/read.h"
#include "/public/colors.h"
#include <string>
#include <vector>
using namespace std;

const auto [ROWS,COLS] = get_terminal_size();

void print_screen(){}

void dialog(string toPrint) {
	clearscreen();
	movecursor(ROWS/2, (COLS - toPrint.size()) / 2);
	//system(("echo " + toPrint + " | lolcat").c_str());
	cout << toPrint << endl;
}
