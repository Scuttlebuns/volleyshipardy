#include "/public/read.h"
#include "questions.h" 
#include "volley.h" 
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
	return RUN_ALL_TESTS();
	
	Player player1("Player 1");
	Player player2("Player 2");

	while (true){
		jepFullRound(player1, player2, question_db);
		if (player1.get_score() or player2.get_score()) break;
	}

}
