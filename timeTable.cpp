#include "timeTable.h"

void timetable::mapRecommendation(std::vector<double> recomm)
{
}

std::vector<subject_timetable> timetable::setTimetable()
{
	// 전진 소거법
	std::vector<timetable> *timetable[2]; // 대충 두개 동적 할다ㅣㅇ 됐다고 가정

	for (int i = 0; i < candiates.size(); i++) {
		int ttIndex = i % numberOfTimetable;

		if(timetable[ttIndex]->getCurrentGrade() < candiates[i].getMaxGrade())
		timetable[ttIndex].push_back(candiates[i]);
	}
}
