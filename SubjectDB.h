#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Subject.h"

using namespace std;

/*
   method 	 1.모든 과목 불러오기
			 2.사용자로부터 이수한 과목 입력받기
			 3.남은학점 계산....
			 4.(각 학년별, 각 학기별 이수가능한 과목)  출력
*/


class subject_DB {
private:
	vector <subject_class> subjectListDB;
	/*int number;
	int majorInfo; //전공기초: 0 전공필수: 1 전공: 2
	int grade; //1학년: 1 2학년:2
	int semester; // 1학기: 1 2학기: 2
	int credit;
	std::string sub_name; //교과목 이름*/
	unsigned int totalLength = 0;

public:
	void init_DB();
	void get_comp_sub();
	void cal_rest_credit();
	void sub_print();
	bool searchSubject(std::string subName);


};

