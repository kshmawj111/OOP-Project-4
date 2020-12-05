/* 
* 
* �� �б⸦ ����ü�� ����� ���� ���� �б� ��ŭ ����� ����]
* ���� �迭�� ����
* �ִ� ���� ��� ����
* ���� 
*  
* 
*/
#pragma once
#include "Subject.h"
#include <vector>

// class for one timetable subject
class subject_timetable : private subject_class
{
	double weight; // ����ġ ����


public:
	void setWeight(int yearDifference, int timetableWeight, double recommendIndex); // �г��� ���� ���� ����ġ�� ������d
	double getWeights() { return weight; }

};

// class for whole timetable
class timetable
{
public:
	// void set �г�, �б� ~ �ʿ�
	void setMaxGrade(int _maxGrade) { maxGrade = _maxGrade; }
	void setCurrentGrade(int _current) { currentGrade = _current; }

	int getMaxGrade() { return maxGrade; }
	int getCurrentGrade() { return currentGrade; }

private:

	std::vector<subject_class> candiates; // �ð�ǥ�� �� �����. ����ġ�� �ٵ� ������ �ְԵ� �� �ð�ǥ ��ü����
	// ���� Ÿ�����̺��� ����ؼ� ����� �� ����� �迭�� ������ �ϴ°�? �ƴϸ� �׳� subject_timetable���� �ñ׳η� ǥ���� �ֵ� ��������?

	void mapRecommendation(std::vector<double> recomm); // ���޹��� ��õ ������ �����ϴ� �Լ�

	void getPlan(); // ����ڿ��Լ� �������� ���� �б⸦ ��� ������ �Է� ���� 
	// -> Student ����ü���� �������̽��� �����ؼ� �ϴ°� �´°� ����. ��ǲ ó���� Student ��ü���� �ϴ°ɷ�??

	std::vector<subject_timetable> setTimetable(); // ���� ������ ���� ������ ������ �־ ����ġ�� �ִ밡 �Ǵ� ������ ���� �ð�ǥ�� ä���� ����. 
	// �� ���� ���� �ִµ� �ϳ��� �ִ� ����ġ�� �� �б⿡ ���� �������� ������ ����ġ�� ����� �ǵ��� ����

	int numberOfTimetable; 
	int year;
	int sem;
	int maxGrade;
	int currentGrade;
	std::vector<subject_timetable> table;
};
