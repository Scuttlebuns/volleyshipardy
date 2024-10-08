#pragma once
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <algorithm>
#include <fstream>
#include <limits>
#include <chrono>
#include <utility>
#include <cmath>
#include "read.h"
#include "questions.h"
#include "players.h"
using namespace std;

bool jepHalfRound(double timeToBeat, chrono::duration<double> &elapsed, Question &tempQuestion,vector<Question> &question_db, Player &tempPlayer) {
	bigDialog("VolleyJeopardy");
	cout << "Welcome to VolleyJeopardy!" << endl;
	cout << tempPlayer.get_name()  << "'s turn" << endl;
	auto start = chrono::high_resolution_clock::now();
	cout << tempQuestion << endl;
	cout << "Enter: A. B. C. D." << endl;
	raw_on();
	int input = 0;
	while(true){
		input = toupper(quick_read());
		if(input == 'A' or input == 'B' or input == 'C' or input == 'D') break;
	}							  
	raw_off();
	if(answer_question(tempQuestion, input) == "false"){ 
		return false;
	}
	else {
		auto end = chrono::high_resolution_clock::now();
		elapsed = end - start;
		return elapsed.count() < timeToBeat;
	}
}

void jepFullRound(Player &Player1, Player &Player2, vector<Question> &question_db) {
	bigDialog("VolleyJeopardy");
	cout << "Welcome to VolleyJeopardy!" << endl;
	double initialTimeToBeat = 100.0;
	chrono::duration<double> player1Time;
	chrono::duration<double> player2Time;

	cout << "Player1 Starts:" << endl;

	Question tempQuestion = random_question(question_db);

	bool player1 = jepHalfRound(initialTimeToBeat, player1Time, tempQuestion, question_db, Player1);

	if (player1) initialTimeToBeat = player1Time.count();
	cout << "Player 1 was " << (player1 ? "Successful" : "Unsuccessful") << " which gives Player 2 " << initialTimeToBeat << " seconds to win the round." << std::endl;
	usleep(2'000'000);

	bool player2 = jepHalfRound(initialTimeToBeat, player2Time, tempQuestion, question_db, Player2);

	if (player2 and player1) {
		player1 = false;
		cout << "Player2 completed the question " << fabs(player2Time.count() - player1Time.count()) << " seconds faster than Player1." << endl;
		usleep(2'000'000);
	}
	else if (player2) {
		cout << "Player2 successfully completed the question in " << player2Time.count() << " seconds." << endl;
		usleep(2'000'000);
	}
	else if (player1) {
		cout << "Player2 was unsuccessful. Player1 wins this round" << endl;
		usleep(2'000'000);
	}
	else {
		cout << "Neither player was successful." << endl;
		usleep(2'000'000);
	}
	if (player1) Player1.set_turn(true);
	if (player2) Player2.set_turn(true);
}
