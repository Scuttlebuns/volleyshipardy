#include "/public/read.h"
#include "questions.h" 
#include "volley.h" 
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
#include <random>
#include <unordered_map>
#include <chrono>
using namespace std;


int main(){
	srand(time(0));
	default_random_engine gen(time(0));
	vector<Question> question_db;
	load_questions(question_db);
	//default_random_engine g(time(0));
	//shuffle(question_db.begin(), question_db.end(), g);
	//cout << question_db.size() << endl;
/*	for(int i = 0; i < 5; i++){
		cout << boolalpha << (random_question(question_db) ? true : false) << endl;
	}*/
	Player player1("Player 1");
	Player player2("Player 2");

	while (true){
		jepFullRound(player1, player2, question_db);
		if (player1.get_score() or player2.get_score()) break;
	}

}
/*
   for(auto x : question_db) {
   auto input = read();
   auto start_time = chrono::steady_clock::now();
   bool correct = x.print_question();
   auto end_time = chrono::steady_clock::now();
   chrono::duration<double> time_taken = end_time - start_time;
   cout << boolalpha << x.print_question();
   cout << endl;

   if(correct){
   player1.increment_score();
   player1.record_time(time_taken);
   }
   else{
   player2.increment_score();
   player2.record_time(time_taken);
   }
   }
   player1Turn = false;
   cout << endl;
   */
