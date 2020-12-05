#pragma once
#include <iostream>
#include <string>

class subject_class {

private:
	int sub_number;
	int sub_majorInfo; //��������: 0 �����ʼ�: 1 ����: 2
	int sub_grade; //1�г�: 1 2�г�:2
	int sub_semester; // 1�б�: 1 2�б�: 2
	int sub_credit;
	bool signal = false;
	std::string sub_name; //������ �̸�

public:
	subject_class() {
		sub_number = 0;
		sub_majorInfo = 0;
		sub_grade = 0;
		sub_semester = 0;
		sub_credit = 0;
	}
	subject_class(int number, int majorInfo, int grade, int semester, int credit, std::string str) {
		this->sub_number = number;
		this->sub_majorInfo = majorInfo;
		this->sub_grade = grade;
		this->sub_semester = semester;
		this->sub_credit = credit;
		sub_name = str;
	}

	// setter
	void setNumber(int number) {
		this->sub_number = number;
	}
	void setMajorInfo(int majorInfo) {
		this->sub_majorInfo = majorInfo;
	}
	void setGrade(int grade) {
		this->sub_grade = grade;
	}
	void setSemester(int semester) {
		this->sub_semester = semester;
	}
	void setCredit(int credit) {
		this->sub_credit = credit;
	}
	void setName(std::string str) {
		this->sub_name = str;
	}
	void setSignal() {
		this->signal = true;
	}

	// getter
	int getNumber() {
		return this->sub_number;
	}
	int getMajorInfo() {
		return this->sub_majorInfo;
	}
	int getGrade() {
		return this->sub_grade;
	}
	int getSemester() {
		return this->sub_semester;
	}
	int getCredit() {
		return this->sub_credit;
	}
	bool getSignal() {
		return this->signal;
	}

	std::string getsub_name() {
		return this->sub_name;
	}

};