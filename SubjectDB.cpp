#include "SubjectDB.h"

void subject_DB::init_DB() {


	fstream in;
	string data;
	int i = 0, cnt = 1;

	in.open("studentdb.txt", std::ios::in);

	if (in) {
		subject_class sub;
		while (!in.eof()) {
			//������ ������ ���� : index, ����, �г�, �б�, ����, ������

			std::getline(in, data, ',');
			int flag = 0;

			switch (cnt % 6) {
			case 1:
				sub.setNumber(stoi(data));
				cnt++;
				break;

			case 2:
				if (data == "��������") {
					flag = 0;
				}
				else if (data == "�����ʼ�") {
					flag = 1;
				}
				else {
					flag = 2;
				}
				sub.setMajorInfo(flag);
				cnt++;
				break;

			case 3:
				sub.setGrade(stoi(data));
				cnt++;
				break;

			case 4:
				sub.setSemester(stoi(data));
				cnt++;
				break;

			case 5:
				sub.setCredit(stoi(data));
				cnt++;
				break;

			case 0:
				sub.setName(data);
				cnt++;
				subjectListDB.push_back(sub);
				break;

			}

		}

		totalLength = subjectListDB.size();
	}
	else {
		cout << "������ ã�� �� �����ϴ�!" << std::endl;
	}

	//for (int i = 0; i < 66; i++) {
	//	std::cout << i << "��° subject �Դϴ�." << std::endl;
	//	std::cout << "��ȣ:" << subjectArray[i].number << std::endl;
	//	std::cout << "����:" << subjectArray[i].majorInfo << std::endl;
	//	std::cout << "�г�:" << subjectArray[i].grade << std::endl;
	//	std::cout << "�б�:" << subjectArray[i].semester << std::endl;
	//	std::cout << "����:" << subjectArray[i].credit << std::endl;
	//	std::cout << ":" << subjectArray[i]->getNumber() << std::endl;
	//}



}

/*
method 	 1.��� ���� �ҷ�����
2.����ڷκ��� �̼��� ���� �Է¹ޱ�
3.�������� ���....
4.(�� �г⺰, �� �б⺰ �̼������� ����)  ���
*/
void subject_DB::get_comp_sub() {
	//���
	for (size_t i = 0; i < subjectListDB.size(); i++) {
		cout << "number :" << subjectListDB[i].getCredit() << endl;
		cout << "subject name :" << subjectListDB[i].getsub_name() << endl;
	}

	//����ڷκ��� �Է�
	string temp;
	int i = 0;
	cout << "> ";
	getline(std::cin, temp);
	do {
		if (temp[i] != ' ')
			subjectListDB[temp[i]].setSignal();
		i++;
	} while (temp[i] != '\0');
	//2 4 6 7 8 => split!

}

void subject_DB::cal_rest_credit() {
	int comp_credit = 0;
	for (size_t i = 0; i < subjectListDB.size(); i++) {
		if (subjectListDB[i].getSignal()) {
			comp_credit += subjectListDB[i].getCredit();
		}
	}
}

// find an
bool subject_DB::searchSubject(std::string subName)
{
	for (size_t i = 0; i < subjectListDB.size(); i++) {
		if (subjectListDB[i].getsub_name() == subName) {
			return true;
		}
	}
	return false;
}
