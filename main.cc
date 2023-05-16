#include "read.h"
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

//Looks good, just need to make a bit more progress, since the project is due tomorrow
// - Alex~

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
	EXPECT_EQ(answer_question(test_db.at(0), 'a'), "true");
	EXPECT_EQ(answer_question(test_db.at(1), 'b'), "false");
	EXPECT_EQ(answer_question(test_db.at(2), 'c'), "false");
	EXPECT_EQ(answer_question(test_db.at(3), 'd'), "false");
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

	cout << ("Press '0' for debug mode\n (Press anything else to startgame)\n");
	int x = -10;
	cin >> x;
	if (x == 0) return RUN_ALL_TESTS();

		//Init Plaers, and Boards
		Player player1("Player 1");
		Board p1Board;
		randomizeShips(p1Board);
		Player player2("Player 2");
		Board p2Board;
		randomizeShips(p2Board);

		while (!p1Board.gameOver() or !p2Board.gameOver()){
			jepFullRound(player1, player2, question_db);
			if (player1.get_turn()){
				battleshipTurn(p2Board, player1);
			}
			else if (player2.get_turn()){
				battleshipTurn(p1Board, player2);
			}
		}
}

