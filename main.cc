#include "/public/read.h"
#include "questions.h" 
#include "volley.h" 
#include "battleship.h"
#include <gtest/gtest.h>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
#include <random>
#include <unordered_map>
#include <chrono>
using namespace std;
//Global test_vector for GTest
vector<Question> test_db;

//GOOGLE TEST:
//Good Test
TEST(answer_question, GoodTest){
	EXPECT_EQ(answer_question(test_db.at(0), 'A'), "true");
	EXPECT_EQ(answer_question(test_db.at(1), 'B'), "false");
	EXPECT_EQ(answer_question(test_db.at(2), 'C'), "false");
	EXPECT_EQ(answer_question(test_db.at(3), 'D'), "false");
	EXPECT_EQ(answer_question(test_db.at(4), 'A'), "true");
	EXPECT_EQ(answer_question(test_db.at(5), 'A'), "true");
	EXPECT_EQ(answer_question(test_db.at(10), 'B'), "false");
	EXPECT_EQ(answer_question(test_db.at(20), 'D'), "false");
	EXPECT_EQ(answer_question(test_db.at(30), 'C'), "false");
	EXPECT_EQ(answer_question(test_db.at(40), 'A'), "true");
	EXPECT_EQ(answer_question(test_db.at(50), 'A'), "true");

}
//Bad Test
TEST(answer_question, BadTest){
	EXPECT_EQ(answer_question(test_db.at(0), 'r'), "ERROR: BAD INPUT!");
	EXPECT_EQ(answer_question(test_db.at(1), 'j'), "ERROR: BAD INPUT!");
	EXPECT_EQ(answer_question(test_db.at(2), '?'), "ERROR: BAD INPUT!");
	EXPECT_EQ(answer_question(test_db.at(3), '%'), "ERROR: BAD INPUT!");
	EXPECT_EQ(answer_question(test_db.at(4), '_'), "ERROR: BAD INPUT!");
	EXPECT_EQ(answer_question(test_db.at(5), 'z'), "ERROR: BAD INPUT!");
	EXPECT_EQ(answer_question(test_db.at(50), '6'), "ERROR: BAD INPUT!");
}

//Edge Cases
TEST(answer_question, EdgeTests){
	EXPECT_EQ(answer_question(test_db.at(0), 'a'), "ERROR: BAD INPUT!");
	EXPECT_EQ(answer_question(test_db.at(1), 'b'), "ERROR: BAD INPUT!");
	EXPECT_EQ(answer_question(test_db.at(2), 'c'), "ERROR: BAD INPUT!");
	EXPECT_EQ(answer_question(test_db.at(3), 'd'), "ERROR: BAD INPUT!");
	EXPECT_EQ(answer_question(test_db.at(4), 'F'), "ERROR: BAD INPUT!");
	EXPECT_EQ(answer_question(test_db.at(5), '@'), "ERROR: BAD INPUT!");
	EXPECT_EQ(answer_question(test_db.at(50), 'A'), "true");
}

//int main(){
int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	vector<Question> question_db;
	//Time Init
	srand(time(0));
	default_random_engine gen(time(0));
	//Question Database
	load_questions(question_db);
	char x = read("Press 'D' for debug mode\n (Press anything else to startgame)\n");
	if (x == 'D') return RUN_ALL_TESTS();

	//Init Plaers, and Boards
	Player player1("Player 1");
	Board p1Board;
	randomizeShips(p1Board);
	Player player2("Player 2");
	Board p2Board;
	randomizeShips(p2Board);

	while (!p1Board.gameOver() or !p2Board.gameOver()){
		jepFullRound(player1, player2, question_db);
		if (player1.get_score()){
			cout << "Welcome to battleship!, you have 3 chances to hit the enemy ships!" << endl;
			int turns = 3;
			while(turns > 0){
				char row = 'Z';
				int col = 0;
				p2Board.print();
				cout << "Enter (ROW, COL to attack: ";
				cin >> row >> col;
				int iRow = static_cast<int>(row - 65);
				if(!p2Board.attack(iRow, col)) { 
					cout << "INVAILD MOVE, try again!" << endl;
				}
				else if(p2Board.getPosition(iRow, col) == '#') cout << "HIT" << endl;
				else cout << "MISS" << endl;
				turns--;
				cout << turns << " remain." << endl;
			}
		}
	}

}

