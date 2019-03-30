#include <iostream>
#include <string>

class Auditorium{
	private:
		int roomNo;
		std::string time;
	public:
		Auditorium(int i, std::string t) : roomNo(i), time(t) {}

		void changeAuditorium(int i, std::string t){
			roomNo = i;
			time = t;
		}
		
		void printAuditorium(){
			std::cout << "room number " << roomNo << std::endl;
			std::cout << "Time " << time << std::endl;
		}
};