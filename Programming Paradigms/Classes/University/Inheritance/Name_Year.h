#include <iostream>

class Year{
	private:
		std::string year;
	public:
		Year(){}
		Year(std::string y){
			year = y;
		}
		void setYear(std::string y){
			year = y;
		}
		void printYear(){
			std::cout << "Year " << year << std::endl;
		}	
};

class Name{
	protected:
		std::string givenName;
		std::string familyName;
	public:
		Name(){}
		
		Name(std::string n1, std::string n2){
			givenName = n1;
			familyName = n2;
		}
		
		void setName(std::string n1, std::string n2){
			givenName = n1;
			familyName = n2;
		}
		
		void printName(){
			std::cout << "Given Name " << givenName << std::endl;
			std::cout << "Family Name " << familyName << std::endl;
		}
};