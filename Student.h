#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <istream>
#include "Subject.h"
#include "SubjectDB.h"

using namespace std;

class StudentSubject :public subject_class {

private:
	double score;

public:
	void setScore(double _score) {
		this->score = _score;
	}

	double getScore() {
		return this->score;
	}
};

class Student {
	string name;
	string id;
	int grade;
	int semester;
	int totalCredit;
	double gpa;
	vector <StudentSubject> subjectListStudent;

	void setPersonInfo();

	StudentSubject mapSubject(string list);
	int determineMajorType(string s);
	int determineSem(string s);

	bool checkEnd(string filename, string endword);
	bool isIn(string word, string* array, int size);


public:
	void get_input(subject_DB sub_db);
	void connectSignal(subject_DB sub_db);
	Student(string filename);
	void printSubjects();
	void calGpa();
	void remainCredit();
	void graduate();
	void recommendSubject();
};
