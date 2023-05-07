#include "/public/read.h"
#include "questions.h" 
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
#include <random>
#include <unordered_map>
#include <chrono>
using namespace std;

//srand(time(0));
default_random_engine gen(time(0));
vector<Question> question_db;

int main(){
	load_questions(question_db);
	default_random_engine g(time(0));
	shuffle(question_db.begin(), question_db.end(), g);
	cout << question_db.size() << endl;

//	question_db.at(3).print_question();
	for(auto x : question_db) {
		auto input = read();
		cout << boolalpha << x.print_question();
		cout << endl;
	}

	//cout << "hi" << endl;

}
