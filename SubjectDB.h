#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Subject.h"

using namespace std;

/*
   method 	 1.��� ���� �ҷ�����
			 2.����ڷκ��� �̼��� ���� �Է¹ޱ�
			 3.�������� ���....
			 4.(�� �г⺰, �� �б⺰ �̼������� ����)  ���
*/


class subject_DB {
private:
	vector <subject_class> subjectListDB;
	/*int number;
	int majorInfo; //��������: 0 �����ʼ�: 1 ����: 2
	int grade; //1�г�: 1 2�г�:2
	int semester; // 1�б�: 1 2�б�: 2
	int credit;
	std::string sub_name; //������ �̸�*/
	unsigned int totalLength = 0;

public:
	void init_DB();
	void get_comp_sub();
	void cal_rest_credit();
	void sub_print();
	bool searchSubject(std::string subName);


};

