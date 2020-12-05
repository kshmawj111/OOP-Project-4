/* 
* 
* 한 학기를 구조체로 만들어 놓고 남은 학기 만큼 만들어 놓기]
* 과목 배열을 만들어서
* 최대 학점 멤버 변수
* 과목 
*  
* 
*/
#pragma once
#include "Subject.h"
#include <vector>

// class for one timetable subject
class subject_timetable : private subject_class
{
	double weight; // 가중치 변수


public:
	void setWeight(int yearDifference, int timetableWeight, double recommendIndex); // 학년차 등을 통해 가중치를 설정함d
	double getWeights() { return weight; }

};

// class for whole timetable
class timetable
{
public:
	// void set 학년, 학기 ~ 필요
	void setMaxGrade(int _maxGrade) { maxGrade = _maxGrade; }
	void setCurrentGrade(int _current) { currentGrade = _current; }

	int getMaxGrade() { return maxGrade; }
	int getCurrentGrade() { return currentGrade; }

private:

	std::vector<subject_class> candiates; // 시간표에 들어갈 과목들. 가중치를 다들 가지고 있게됨 각 시간표 객체마다
	// 최종 타임테이블을 고려해서 출력할 때 사용할 배열을 만들어야 하는가? 아니면 그냥 subject_timetable에서 시그널로 표시해 둬도 괜찮은가?

	void mapRecommendation(std::vector<double> recomm); // 전달받은 추천 과목을 매핑하는 함수

	void getPlan(); // 사용자에게서 몇학점씩 남은 학기를 듣고 싶은지 입력 받음 
	// -> Student 구조체에서 인터페이스랑 연계해서 하는게 맞는거 같음. 인풋 처리를 Student 객체에서 하는걸로??

	std::vector<subject_timetable> setTimetable(); // 지금 생각은 여러 조합의 과목을 넣어서 가중치가 최대가 되는 조합을 최종 시간표로 채택할 생각. 
	// 두 가지 안이 있는데 하나는 최대 가중치가 한 학기에 몰빵 나머지는 적당한 가중치의 평균이 되도록 조절

	int numberOfTimetable; 
	int year;
	int sem;
	int maxGrade;
	int currentGrade;
	std::vector<subject_timetable> table;
};
