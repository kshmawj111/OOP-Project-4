#include "timeTable.h"

void timetable::mapRecommendation(std::vector<double> recomm)
{
}

std::vector<subject_timetable> timetable::setTimetable()
{
	// ���� �ҰŹ�
	std::vector<timetable> *timetable[2]; // ���� �ΰ� ���� �Ҵ٤Ӥ� �ƴٰ� ����

	for (int i = 0; i < candiates.size(); i++) {
		int ttIndex = i % numberOfTimetable;

		if(timetable[ttIndex]->getCurrentGrade() < candiates[i].getMaxGrade())
		timetable[ttIndex].push_back(candiates[i]);
	}
}
