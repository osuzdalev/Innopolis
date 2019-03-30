#include <iostream>
#include "Auditorium.h"
#include "LectureC_People.h"

class Lecture{
	private:
		LectureCourse * lecture;
		Auditorium * room;
	public:
		Lecture(LectureCourse lc, Auditorium a){
			room = &a;
			lecture = &lc;
		}
		void printLecture(){
			lecture->print();
			room->printAuditorium();
		}
};