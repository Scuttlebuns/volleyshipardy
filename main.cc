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


/*
TEST(Test_question, GoodTest){
	EXPECT_EQ(answer_question(question_db.at(0), 'A', question_db), question_db.at(input - 65)); 
}

TEST(Test_question, BadTest){
	EXPECT_EQ(test_question(), "");
	EXPECT_EQ(test_question(), "");
	EXPECT_EQ(test_question(), "");
	EXPECT_EQ(test_question(), "");
}

TEST(Test_question, EdgeTest){
	EXPECT_EQ(test_question(), "");
	EXPECT_EQ(test_question(), "");
	EXPECT_EQ(test_question(), "");
	EXPECT_EQ(test_question(), "");
}	

*/
int main(){
//int main(int argc, char** argv){
//	testing::InitGoogleTest(&argc, argv);
	//Time Init
	srand(time(0));
	default_random_engine gen(time(0));
	//Question Database
	vector<Question> question_db;
	load_questions(question_db);
//	return RUN_ALL_TEST();
	
//	size_t questionIndex = rand() % question_db.size();
//	cout << question_db.at(questionIndex);
//	char userInput = read("ENTER A. B. C. D. \n");
//	cout << boolalpha << ((answer_question(question_db, userInput, questionIndex)) ? true : false) << endl;



	Player player1("Player 1");
	Player player2("Player 2");

	while (true){
		//cout << boolalpha << (random_question(question_db) ? true : false) << endl;
		//cout << endl;
		
		jepFullRound(player1, player2, question_db);
		if (player1.get_score() or player2.get_score()) break;
	}

}
