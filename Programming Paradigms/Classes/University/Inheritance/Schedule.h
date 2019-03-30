#include <iostream>
#include <vector>
#include "Lecture.h"

enum Days { SUNDAY, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY };

class TeachingDay{
	private:
		std::vector<Lecture> lectures;
		Days m_id;
	public:
		TeachingDay(std::vector<Lecture> v){
			lectures = v;
		}

		void printTeachingDay()
		{
			for(std::vector<Lecture>::iterator it = lectures.begin() ; it != lectures.end(); ++it){
				it->printLecture();
			}
		}
};

class TeachingWeek{
	private:
		std::vector<TeachingDay> week;
	public:
		TeachingWeek(std::vector<TeachingDay> w){
			week = w;
		}
		void printTeachingWeek()
		{
			for (std::vector<TeachingDay>::iterator it = week.begin() ; it != week.end(); ++it){
				it->printTeachingDay();
			}
		}
};

class TeachingSchedule{
	private:
		std::vector<TeachingWeek> schedule;
	public:
		TeachingSchedule(std::vector<TeachingWeek> sched){
			schedule = sched;
		}
		void printTeachingSchedule(){
			for(std::vector<TeachingWeek>::iterator it = schedule.begin(); it != schedule.end(); ++it){
				it->printTeachingWeek();
			}
		}
};