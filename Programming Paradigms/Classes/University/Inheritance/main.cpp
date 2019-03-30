#include <iostream>
#include <random>
#include <vector>
#include <string>
#include "University.h"

using namespace std;

vector<string> names,lnames;

int getrand(int c,int y=0){
	return rand()%c+y;
}

int main(){
	//Start with instructors
	Instructor Aziz("Aziz", "Oud"), Zouev("Evgueni", "Zouev"), Kapitonov("Alexander", "Kapitonov");
	Assistant A("a", "A"), B("b", "B"), C("c", "C"), D("d", "D"), E("e", "E");
	
	//making TA vectors for Courses
	std::vector<Assistant> math_TA;
	math_TA.push_back(A);
	math_TA.push_back(B);
	
	std::vector<Assistant> mpp_TA;
	mpp_TA.push_back(C);
	mpp_TA.push_back(D);
	
	std::vector<Assistant> robotics_TA;
	robotics_TA.push_back(E);
	
	//defining LectureCourses
	LectureCourse Mathematics("Mathematics", Aziz, math_TA, "BS2", true);
	LectureCourse MPP("MPP", Zouev, mpp_TA, "BS2", true);
	LectureCourse Robotics("Robotics", Kapitonov, robotics_TA, "BS2", true);
	
	//Assigning courses to Instructors and Assitants
	std::vector<LectureCourse> c_aziz;
	c_aziz.push_back(Mathematics);
	Aziz.assignLectureCourse(c_aziz);
	
	std::vector<LectureCourse> c_zouev;
	c_zouev.push_back(MPP);
	Zouev.assignLectureCourse(c_zouev);
	
	std::vector<LectureCourse> c_kapitonov;
	c_kapitonov.push_back(Robotics);
	Kapitonov.assignLectureCourse(c_kapitonov);
	
	std::vector<LectureCourse> c_A;
	c_A.push_back(Mathematics);
	A.assignLectureCourse(c_A);
	
	std::vector<LectureCourse> c_B;
	c_B.push_back(Mathematics);
	B.assignLectureCourse(c_B);
		
	std::vector<LectureCourse> c_C;
	c_C.push_back(MPP);
	C.assignLectureCourse(c_C);
		
	std::vector<LectureCourse> c_D;
	c_D.push_back(MPP);
	D.assignLectureCourse(c_D);
	
	std::vector<LectureCourse> c_E;
	c_E.push_back(Robotics);
	E.assignLectureCourse(c_E);
	
	
	//defining Auditoriums
	Auditorium a101(101, "0900"), a201(201, "1100"), a301(301, "1500");
	
	//defining Lectures
	Lecture L1(Mathematics, a101), L2(MPP, a201), L3(Robotics, a301);
	
	//Lecture vectors for Teaching Days
	std::vector<Lecture> l_monday;
	l_monday.push_back(L1);
	l_monday.push_back(L2);
	l_monday.push_back(L3);
	
	std::vector<Lecture> l_thursday;
	l_thursday.push_back(L1);
	l_thursday.push_back(L2);
	
	//defining teaching days
	TeachingDay Monday(l_monday), Thursday(l_thursday);
	
	//Teaching Days vector for Teaching Weeks
	std::vector<TeachingDay> days;
	days.push_back(Monday);
	days.push_back(Thursday);
	
	//defining Teaching Weeks
	TeachingWeek Week1(days), Week2(days), Week3(days), Week4(days);
	
	//Teaching Week vectors for Schedules
	std:: vector<TeachingWeek> weeks;
	weeks.push_back(Week1);
	weeks.push_back(Week2);
	weeks.push_back(Week3);
	weeks.push_back(Week4);
	
	TeachingSchedule Schedule_1(weeks);
	
	//Course vector for Students
	std::vector<LectureCourse> courses;
	courses.push_back(Mathematics);
	courses.push_back(MPP);
	courses.push_back(Robotics);
	
	//Defining Students
	Student Oleg("Oleg", "Souzdalev", "BS2", courses), Alex("Alex", "Karavaev", "BS2", courses), Rami("Rami", "Al-Naim", "BS2", courses);
	
	//Student vector for University
	std::vector<Student> students;
	students.push_back(Oleg);
	students.push_back(Alex);
	students.push_back(Rami);
	
	//Instructor vector for Univeristy
	std::vector<Instructor> instructors;
	instructors.push_back(Aziz);
	instructors.push_back(Zouev);
	instructors.push_back(Kapitonov);
	
	//Assistant vector for University
	std::vector<Assistant> assistants;
	assistants.push_back(A);
	assistants.push_back(B);
	assistants.push_back(C);
	assistants.push_back(D);
	assistants.push_back(E);
	
	//All LectureCourse vector for Univeristy already done for Students (line 108)
	
	//Schedule vector for University
	std::vector<TeachingSchedule> schedule;
	schedule.push_back(Schedule_1);
	
	University Innopolis(students, assistants, instructors, courses, schedule);
	Innopolis.printUniversity();
	
	//innopolis.printUniversity(); //Will not compute because too big ...
}