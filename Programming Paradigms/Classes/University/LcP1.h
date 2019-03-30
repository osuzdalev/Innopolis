#include <iostream>
#include <vector>
#include "Name_Year.h"

class LectureCourse; //forward-declaring (used in classes Instructor/Assistant)

//level 0: there cannot be a course without a teacher
class Instructor{
	protected:
		Name name;
		std::vector<LectureCourse> courses;
	public:
		Instructor(std::string n1, std::string n2){
			name.setName(n1, n2);
		}
		void assignLectureCourse(std::vector<LectureCourse> v){
			courses = v;
		}
		
		//print declaration
		void printInstructor();
		
		void printInstructorName(){
			name.printName();
		}
};

//level 0: Instructor can come with a pair of TAs
class Assistant{
	private:
		Name name;
		std::vector<LectureCourse> courses;
	public:
		Assistant(std::string n1, std::string n2){
			name.setName(n1, n2);
		}
		void assignLectureCourse(std::vector<LectureCourse> v){
			courses = v;
		}
		
		//print declaration
		void printAssistant();
		void printAssistantName(){
			name.printName();
		}
};

//Level 1: Course can only exits once there is an Instructor and some Assistants
class LectureCourse{
	private:
		std::string title;
		Year year;
		Instructor * instructor;
		std::vector<Assistant> assistants;
		bool core;
		bool elective;
	public:
		LectureCourse(std::string s, Instructor i, std::vector<Assistant> assist, std::string y, bool c){
			title = s;
			instructor = &i;
			assistants = assist;
			year.setYear(y);
			core = c;
			elective = !c;
		}
		
		void print(){
			std::cout << "Title " << title << std::endl;
			year.printYear();
			std::cout << "Instructor " << std::endl;
			instructor->printInstructorName();
			std::cout << "Assistants " << std::endl;
			for(std::vector<Assistant>::iterator it = assistants.begin() ; it != assistants.end(); ++it){
				it->printAssistantName();
			}
			std::cout << "Core " << core << std::endl;
			std::cout << "Elective " << elective << std::endl;
		}
		
		void printCourseName(){
			std::cout << "Title " << title << std::endl;
		}
		
};

//Instructor print definition
void Instructor::printInstructor(){
	name.printName();
	for(std::vector<LectureCourse>::iterator it = courses.begin() ; it != courses.end(); ++it){
		it->printCourseName();
	}
}

//Assistant print definition
void Assistant::printAssistant(){
	name.printName();
	for(std::vector<LectureCourse>::iterator it = courses.begin() ; it != courses.end(); ++it){
		it->printCourseName();
	}
}

//level 2: Student without a course is nonsense, can only exist once there is one
class Student{
	private:
		Name name;
		Year year;
		std::vector<LectureCourse> courses;
	public:
		Student(){}
		Student(std::string n1, std::string n2, std::string y, std::vector<LectureCourse> lc){
			name.setName(n1, n2);
			year.setYear(y);
			courses = lc;
		}
		void print(){
			name.printName();
			for(std::vector<LectureCourse>::iterator it = courses.begin() ; it != courses.end(); ++it){
				it->print();
			}
		}
		void printStudentName(){
			name.printName();
		}
};