#pragma once

#include "/public/read.h"
#include <vector>
#include <algorithm>
#include <sstream>
#include <random>
#include <string>
#include <cctype>
#include <compare>
using namespace std;


class Question{
	private:
		string question;
		string correctAnswer;
		vector<string> answer_db;
	public:
		//Cstors
		Question(){}
		Question(string new_question, string new_correctAnswer, vector<string> new_answer_db) : question(new_question), correctAnswer(new_correctAnswer), answer_db(new_answer_db) {} 

		//Getters
		string get_question() const { return question; }
		string get_correctAnswer() const { return correctAnswer; }
		vector<string> get_answer_db() const { return answer_db; }

		//Setters
		void set_question(string temp) { question = temp; }
		void set_correctAnswer(string temp) { correctAnswer = temp; }
		void set_answer_db(vector<string> temp) {answer_db = temp; }


		bool print_question(){
			bool retval = false;
			vector<string> answer_temp = answer_db;
			string q = question;
			size_t pos = q.find("\\n");
			while(pos != string::npos){
				q.replace(pos, 2, "\n");
				pos = q.find("\\n", pos + 1);
			}
			cout << q << endl;
			//unsigned seed = time(0);//FIXME include srand() in main
			default_random_engine g(time(0));
			shuffle(answer_temp.begin(), answer_temp.end(), g);
			char correctChar = 'z';
			for (size_t i = 0; i < answer_temp.size(); i++) {
				if(answer_temp.at(i) == correctAnswer) correctChar = static_cast<char>(i+65);
				cout << static_cast<char>(i + 65)  << ". " << answer_temp.at(i) << endl;
			}
			char input = read("Please enter A) B) C) D)\n");
			input = toupper(input);
			return retval = (correctChar == input) ? true : false;
		}

		friend bool operator==(const Question& lhs, const Question& rhs) {
			return (lhs.get_question() == rhs.get_question() &&
					lhs.get_correctAnswer() == rhs.get_correctAnswer() &&
					lhs.get_answer_db() == rhs.get_answer_db());
		}

	/*	friend auto operator<=>(const Question& lhs, const Question& rhs) {
			return tie(lhs.question,lhs.correctAnswer) <=> tie(rhs.question, rhs.correctAnswer);
		}
	*/

};
		 void load_questions (vector<Question> &question_db, string fileName = "questions.txt"){
			ifstream ins (fileName);
			if(!ins) cerr << "Error opening Questions file!\n";
			while(true){
				Question temp;
				vector<string> tempAnswers;
				string question = readline(ins);

				string answer1 = readline(ins);
				tempAnswers.push_back(answer1);

				string answer2 = readline(ins);
				tempAnswers.push_back(answer2);

				string answer3 = readline(ins);
				tempAnswers.push_back(answer3);

				string answer4 = readline(ins);
				tempAnswers.push_back(answer4);

				temp.set_question(question);
				temp.set_correctAnswer(answer1);
				temp.set_answer_db(tempAnswers);

				if(!ins) break;
				question_db.push_back(temp);

			}
		}

