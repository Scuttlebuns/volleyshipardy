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
#include "/public/read.h"
#include "questions.h"
#include "players.h"
using namespace std;

bool jepHalfRound(double timeToBeat, chrono::duration<double> &elapsed, Question &tempQuestion,vector<Question> &question_db) {
	auto start = chrono::high_resolution_clock::now();
	cout << tempQuestion << endl;
	char input = read("Enter: A. B. C. D.\n");//FIXME vet !cin
	input = toupper(input);
	//if (!answer_question(tempQuestion, input)) return false;
	if(answer_question(tempQuestion, input) == "false") return false;
	else {
		auto end = chrono::high_resolution_clock::now();
		elapsed = end - start;
		return elapsed.count() < timeToBeat;
	}
}

void jepFullRound(Player &Player1, Player &Player2, vector<Question> &question_db) {
	double initialTimeToBeat = 100.0;
	chrono::duration<double> player1Time;
	chrono::duration<double> player2Time;

	cout << "Player1 Starts:" << endl;

	Question tempQuestion = random_question(question_db);

	bool player1 = jepHalfRound(initialTimeToBeat, player1Time, tempQuestion, question_db);

	if (player1) initialTimeToBeat = player1Time.count();
	cout << "Player1 was " << (player1 ? "Successful" : "Unsuccessful") << " which gives Player2 " << initialTimeToBeat << " seconds to win the round." << std::endl;

	bool player2 = jepHalfRound(initialTimeToBeat, player2Time, tempQuestion, question_db);

	if (player2 and player1) {
		player1 = false;
		cout << "Player2 completed the question " << fabs(player2Time.count() - player1Time.count()) << " seconds faster than Player1." << endl;
	}
	else if (player2) {
		cout << "Player2 successfully completed the question in " << player2Time.count() << " seconds." << endl;
	}
	else if (player1) {
		cout << "Player2 was unsuccessful. Player1 wins this round" << endl;
	}
	else {
		cout << "Neither player was successful." << endl;
	}
	if (player1) Player1.increment_score();
	if (player2) Player2.increment_score();
}
