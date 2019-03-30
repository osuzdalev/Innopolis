#include <iostream>
#include <vector>
#include "Schedule.h"

class University{
	private:
		std::vector<Student> students;
		std::vector<Assistant> assistants;
		std::vector<Instructor> instructors;
		std::vector<TeachingSchedule> schedules;
		std::vector<LectureCourse> courses;
	public:
		University(std::vector<Student> st, std::vector<Assistant> a, std::vector<Instructor> i, std::vector<LectureCourse> c, std::vector<TeachingSchedule> sd){
			
			students = st;
			assistants = a;
			instructors = i;
			courses = c;
			schedules = sd;
		}
		
		void printUniversity(){
			std::cout << "Students: " << std::endl;
			for (std::vector<Student>::iterator it = students.begin() ; it != students.end(); ++it){
				it->print();
				std::cout << std::endl << "---------------------------------------------------------" << std::endl;
			}
			
			std::cout << std::endl << "###################################################" << std::endl;
			
			std::cout << "Assistants: " << std::endl;
			for (std::vector<Assistant>::iterator it = assistants.begin() ; it != assistants.end(); ++it){
				it->printAssistant();
				std::cout << std::endl << "---------------------------------------------------------" << std::endl;
			}
			
			std::cout << std::endl << "###################################################" << std::endl;
			
			std::cout << "Instructors: " << std::endl;
			for (std::vector<Instructor>::iterator it = instructors.begin() ; it != instructors.end(); ++it){
				it->printInstructor();
				std::cout << std::endl << "---------------------------------------------------------" << std::endl;
			}
			
			std::cout << std::endl << "###################################################" << std::endl;
			
			std::cout << "Courses: " << std::endl;
			for (std::vector<LectureCourse>::iterator it = courses.begin() ; it != courses.end(); ++it){
				it->print();
				std::cout << std::endl << "---------------------------------------------------------" << std::endl;
			}
			
			std::cout << std::endl << "###################################################" << std::endl;
			
			std::cout << "Schedules: " << std::endl;
			for (std::vector<TeachingSchedule>::iterator it = schedules.begin() ; it != schedules.end(); ++it){
				it->printTeachingSchedule();
				std::cout << std::endl << "---------------------------------------------------------" << std::endl;
			}
		}
};