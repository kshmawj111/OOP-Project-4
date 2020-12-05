#include "Student.h"
#include "Subject.h"
#include "SubjectDB.h"

#define MAX_SUB_LENGTH 150
#define COMMA_PER_LINE 8
#define MAX_CHOICE 5

bool Student::checkEnd(string filename, string endword) {
	if (filename.length() >= endword.length()) {
		return (0 == filename.compare(filename.length() - endword.length(), endword.length(), endword));
	}
	else {
		return false;
	}

}

// check if a word is in an array
bool Student::isIn(string word, string* array, int size = 10)
{
	for (int i = 0; i < size; i++) {
		if (word == array[i]) return true;

	}
	return false;
}


int Student::determineMajorType(string s)
{
	if (s == "전공기초") return 0;
	else if (s == "전공필수") return 1;
	else if (s == "복수전공") return 2;
	else if (s == "전공") return 2;
	else return 3;
}

int Student::determineSem(string s)
{
	if (s == "하계") return 1;
	else if (s == "동계") return 2;
	else return stoi(s);
}

StudentSubject Student::mapSubject(string list)
{
	vector <string> split;
	string buf;
	stringstream ss(list);
	enum major { base, required_major, major, other };

	while (getline(ss, buf, ',')) {
		split.push_back(buf);
	}

	StudentSubject sub;
	// 전공기초: 0 전공필수: 1 전공: 2, 교양: 3
	// "년도", "학기", "이수구분", "영역구분", "교과목-분반", "과목", "학점", "등급", "평점", "원어구분"
	sub.setSemester(determineSem(split[1]));
	sub.setMajorInfo(determineMajorType(split[2]));
	sub.setName(split[5]);
	sub.setCredit(stoi(split[6]));
	sub.setScore(stod(split[8]));
	return sub;
}

Student::Student(string filename) {
	fstream fs;
	char buf[MAX_SUB_LENGTH];
	string endword = ".csv";
	int numComma = 0;
	vector <string> temp;

	string excludeList[11] = { "년도", "학기", "이수구분", "영역구분", "교과목-분반", "과목",
		"학점", "등급", "평점", "원어구분", "졸 업 관 련 성 적 내 역" };

	if (checkEnd(filename, endword) == false) {
		// not csv file
		cout << "File " << filename << "is not csv file. Convert the file into csv or download it as csv.\n";
		exit(-1);
	}

	// setPersonInfo();

	fs.open(filename, ios::in);


	if (!fs) {
		// file not opened.
		cout << "File " << filename << "does not exist.\n";
		exit(-1);
	}

	while (!fs.eof()) {
		// 모든 라인 가져와서 저장
		fs.getline(buf, MAX_SUB_LENGTH);
		temp.push_back(buf);
	}

	// find vector starting with literal value. -> exclude them
	for (size_t i = 0; i < temp.size(); i++) {
		if (48 > temp[i][0] || temp[i][0] > 57) {
			temp.erase(temp.begin() + i);
			i = -1;

		}
	}

	// map the read data to subject type
	for (size_t i = 0; i < temp.size(); i++) {
		subjectListStudent.push_back(mapSubject(temp[i]));

	}
	fs.close();

}

void Student::setPersonInfo()
{
	cout << "    Name   >> ";
	cin >> name;
	cout << "     id    >> ";
	cin >> id;
	cout << "   Grade   >> ";
	cin >> grade;
	cout << " Semeseter >> ";
	cin >> semester;
}


void Student::printSubjects()
{
	for (size_t i = 0; i < subjectListStudent.size(); i++) {
		cout.width(30);
		cout << subjectListStudent[i].getsub_name() << ": ";
		cout.width(5);
		cout << subjectListStudent[i].getMajorInfo();
		cout.width(5);
		cout << subjectListStudent[i].getCredit();
		cout.width(5);
		cout << subjectListStudent[i].getScore() << endl;


	}
}

void Student::connectSignal(subject_DB sub_db)
{

	for (size_t i = 0; i < subjectListStudent.size(); i++) {
		if (sub_db.searchSubject(subjectListStudent[i].getsub_name())) {
			subjectListStudent[i].setSignal();
		}
	}

}

void Student::calGpa()
{
	double totalaverage, majoraverage;
	double totalsum = 0, majorsum = 0;
	int totalcredit = 0, majorcredit = 0;

	for (size_t i = 0; i < subjectListStudent.size(); i++)
	{

		if (subjectListStudent[i].getSignal())
		{
			totalsum += subjectListStudent[i].getScore() * subjectListStudent[i].getCredit();
			totalcredit += subjectListStudent[i].getCredit();
		}
		else
		{
			totalsum += subjectListStudent[i].getScore() * subjectListStudent[i].getCredit();
			totalcredit += subjectListStudent[i].getCredit();
			majorsum += subjectListStudent[i].getScore() * subjectListStudent[i].getCredit();
			majorcredit += subjectListStudent[i].getCredit();
		}

	}

	totalaverage = totalsum / totalcredit;
	majoraverage = majorsum / majorcredit;

	std::cout << "전체 평점은 " << totalaverage << "입니다" << std::endl;
	std::cout << "전공 평점은 " << majoraverage << "입니다" << std::endl;
}

void Student::remainCredit()
{
	int remain = 86;
	int remain_base = 24;
	int remain_must = 16;

	for (size_t i = 0; i < subjectListStudent.size(); i++)
		if (subjectListStudent[i].getSignal() == 1) 
		{
			if(subjectListStudent[i].getMajorInfo() == 1 || subjectListStudent[i].getMajorInfo() == 2)
				remain -= subjectListStudent[i].getCredit();

			if(subjectListStudent[i].getMajorInfo() == 0)
				remain_base -= subjectListStudent[i].getCredit();

			if (subjectListStudent[i].getMajorInfo() == 1)
				remain_must -= subjectListStudent[i].getCredit();
		}

	std::cout << "들어야할 남은 전공 학점은 " << remain << "입니다." << std::endl;

	if (remain_base == 0)
	{
		std::cout << "들어야할 전공기초 과목이 없습니다" << std::endl;
	}
	else
	{
		std::cout << "들어야할 전공기초 과목명은 ";
		for (size_t i = 0; i < subjectListStudent.size(); i++)
			if (subjectListStudent[i].getSignal() == 1 && subjectListStudent[i].getMajorInfo() == 0)
			{
				std::cout << subjectListStudent[i].getsub_name();
			}
		std::cout << "입니다" << std::endl;
	}


	if (remain_base == 0)
	{
		std::cout << "들어야할 전공필수 과목이 없습니다" << std::endl;
	}
	else
	{
		std::cout << "들어야할 전공필수 과목명은 ";

		for (size_t i = 0; i < subjectListStudent.size(); i++)

			if (subjectListStudent[i].getSignal() == 0 && subjectListStudent[i].getMajorInfo() == 1)
			{
				std::cout << subjectListStudent[i].getsub_name() << " ";
			}
		std::cout << "입니다" << std::endl;
	}

}

void Student::get_input(subject_DB sub_db)
{
	int answer;
	connectSignal(sub_db);

	cout << "\n*-------------------------------*\n"
		"	1. 남은 학점 계산하기\n"
		"	2. 나의 총 평점 계산하기\n"
		"	3. 나는 언제쯤 졸업할까?\n"
		"	4. 들은 과목 리스트 보기\n"
		"	5. 과목 추천받기\n"
		"*-------------------------------*\n\n";

	do {
		cout << "번호 입력:";
		cin >> answer;

		if (answer <1 && answer > MAX_CHOICE)
			cout<< "다시 입력하세요"<<endl;

	}while (answer<1 && answer >MAX_CHOICE);

	switch (answer) {
	case(1):
		remainCredit();
		break;
	case(2):
		calGpa();
		break;
	case(3):
		graduate();
		break;
	case(4):
		printSubjects();
	case(5):
		recommendSubject();
	}


}

void Student::graduate()
{

}

void Student::recommendSubject()
{

}
