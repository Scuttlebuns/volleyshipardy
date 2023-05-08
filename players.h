#pragma once

#include "/public/read.h"
#include <chrono>
#include <string>

using namespace std;

class Player{
	private:
		string name;
		int score;
		chrono::duration<double> time_taken;

	public:
	
	/*	Player(string name, int score = 0, chrono::duration<double> time_taken = 0.0){
			this->name = name;
			this->score = score;
			this->time_taken = time_taken;

		}*/
		Player() : name(""), score(0), time_taken(0.0){}
		Player(string name) : name(name), score(0), time_taken(0.0){}
		//Player(string new_name, int new_score, chrono::duration<double> new_time_taken) : name(new_name), score(new_score), time_taken(new_time_taken) {}

		string get_name() const {return name;}
		int get_score() const {return score;}
		chrono::duration<double> get_time_taken() const {return time_taken;}

		void set_name(string new_name) {name = new_name;}
		void set_score(int new_score) {score = new_score;}
		void set_time_taken(chrono::duration<double> new_time_taken) {time_taken = new_time_taken;}

		void increment_score() { score++;}
		void record_time(chrono::duration<double> time_taken) {this->time_taken += time_taken; }

};



	
