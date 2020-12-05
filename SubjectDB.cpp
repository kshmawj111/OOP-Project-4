#include "SubjectDB.h"

void subject_DB::init_DB() {


	fstream in;
	string data;
	int i = 0, cnt = 1;

	in.open("studentdb.txt", std::ios::in);

	if (in) {
		subject_class sub;
		while (!in.eof()) {
			//들어오는 데이터 순서 : index, 구분, 학년, 학기, 학점, 교과목

			std::getline(in, data, ',');
			int flag = 0;

			switch (cnt % 6) {
			case 1:
				sub.setNumber(stoi(data));
				cnt++;
				break;

			case 2:
				if (data == "전공기초") {
					flag = 0;
				}
				else if (data == "전공필수") {
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
		cout << "파일을 찾을 수 없습니다!" << std::endl;
	}

	//for (int i = 0; i < 66; i++) {
	//	std::cout << i << "번째 subject 입니다." << std::endl;
	//	std::cout << "번호:" << subjectArray[i].number << std::endl;
	//	std::cout << "구분:" << subjectArray[i].majorInfo << std::endl;
	//	std::cout << "학년:" << subjectArray[i].grade << std::endl;
	//	std::cout << "학기:" << subjectArray[i].semester << std::endl;
	//	std::cout << "학점:" << subjectArray[i].credit << std::endl;
	//	std::cout << ":" << subjectArray[i]->getNumber() << std::endl;
	//}



}

/*
method 	 1.모든 과목 불러오기
2.사용자로부터 이수한 과목 입력받기
3.남은학점 계산....
4.(각 학년별, 각 학기별 이수가능한 과목)  출력
*/
void subject_DB::get_comp_sub() {
	//출력
	for (size_t i = 0; i < subjectListDB.size(); i++) {
		cout << "number :" << subjectListDB[i].getCredit() << endl;
		cout << "subject name :" << subjectListDB[i].getsub_name() << endl;
	}

	//사용자로부터 입력
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
