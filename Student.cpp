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
	if (s == "��������") return 0;
	else if (s == "�����ʼ�") return 1;
	else if (s == "��������") return 2;
	else if (s == "����") return 2;
	else return 3;
}

int Student::determineSem(string s)
{
	if (s == "�ϰ�") return 1;
	else if (s == "����") return 2;
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
	// ��������: 0 �����ʼ�: 1 ����: 2, ����: 3
	// "�⵵", "�б�", "�̼�����", "��������", "������-�й�", "����", "����", "���", "����", "�����"
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

	string excludeList[11] = { "�⵵", "�б�", "�̼�����", "��������", "������-�й�", "����",
		"����", "���", "����", "�����", "�� �� �� �� �� �� �� ��" };

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
		// ��� ���� �����ͼ� ����
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

	std::cout << "��ü ������ " << totalaverage << "�Դϴ�" << std::endl;
	std::cout << "���� ������ " << majoraverage << "�Դϴ�" << std::endl;
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

	std::cout << "������ ���� ���� ������ " << remain << "�Դϴ�." << std::endl;

	if (remain_base == 0)
	{
		std::cout << "������ �������� ������ �����ϴ�" << std::endl;
	}
	else
	{
		std::cout << "������ �������� ������� ";
		for (size_t i = 0; i < subjectListStudent.size(); i++)
			if (subjectListStudent[i].getSignal() == 1 && subjectListStudent[i].getMajorInfo() == 0)
			{
				std::cout << subjectListStudent[i].getsub_name();
			}
		std::cout << "�Դϴ�" << std::endl;
	}


	if (remain_base == 0)
	{
		std::cout << "������ �����ʼ� ������ �����ϴ�" << std::endl;
	}
	else
	{
		std::cout << "������ �����ʼ� ������� ";

		for (size_t i = 0; i < subjectListStudent.size(); i++)

			if (subjectListStudent[i].getSignal() == 0 && subjectListStudent[i].getMajorInfo() == 1)
			{
				std::cout << subjectListStudent[i].getsub_name() << " ";
			}
		std::cout << "�Դϴ�" << std::endl;
	}

}

void Student::get_input(subject_DB sub_db)
{
	int answer;
	connectSignal(sub_db);

	cout << "\n*-------------------------------*\n"
		"	1. ���� ���� ����ϱ�\n"
		"	2. ���� �� ���� ����ϱ�\n"
		"	3. ���� ������ �����ұ�?\n"
		"	4. ���� ���� ����Ʈ ����\n"
		"	5. ���� ��õ�ޱ�\n"
		"*-------------------------------*\n\n";

	do {
		cout << "��ȣ �Է�:";
		cin >> answer;

		if (answer <1 && answer > MAX_CHOICE)
			cout<< "�ٽ� �Է��ϼ���"<<endl;

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
