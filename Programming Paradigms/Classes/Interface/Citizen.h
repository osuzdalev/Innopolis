#include <string>
#include <iostream>

//Base Class
class Person{
private:
    std::string name;
    std::string sex;
    int age;
public:
    void setBaseCharacteristics(const std::string n, const std::string s, int a) {
        name = n;
        sex = s;
        age = a;
    }
    void getBaseCharacteristics(){
        std::cout << "Name : " << name << std::endl;
        std::cout << "Sex : " << sex << std::endl;
        std::cout << "Age : " << age << std::endl;
        std::cout << std::endl;
    }
};

//Interface for working people
class IWork{
public:
    virtual void workOn() = 0;
    virtual void workOff() = 0;
    virtual void getStat() = 0;
};

//Interface for non-working people
class IVisit{
public:
    virtual void visitOn() = 0;
    virtual void visitOff() = 0;
    virtual void getStat() = 0;
};

//implementation of a person who works
class BusDriver : public Person, IWork{
    bool working = false;
    //particular variable for class
    bool bus_state = true;
public:
    //Interface functions implementation
    void workOn() override {
        std::cout << "Starting work" << std::endl;
        working = true;
    }
    void workOff() override {
        std::cout << "Stopping work" << std::endl;
        working = false;
    }
    void getStat() override {
        std::cout << "Working Status : " << working << std::endl;
        std::cout << std::endl;
    }
    //Special function for class
    void getBusState(){
        std::cout << "Bus State : " << bus_state << std::endl;
        std::cout << std::endl;
    }
};

class Teacher : public Person, IWork{
    bool working = false;
    //particular variable for class
    std::string course;
public:
    //General working functions implementation
    void workOn() override {
        std::cout << "Starting work" << std::endl;
        working = true;
    }
    void workOff() override {
        std::cout << "Stopping work" << std::endl;
        working = false;
    }
    void getStat() override {
        std::cout << "Working Status : " << working << std::endl;
        std::cout << std::endl;
    }
    //Special function for class
    void setCourse(const std::string s){
        std::cout << "Setting course" << std::endl;
        course = s;
    }
    void getCourse(){
        std::cout << "Course : " << course << std::endl;
        std::cout << std::endl;
    }
};

//tourists  do not work, they visit
class Tourist : public Person, IVisit{
private:
    bool status = false;
public:
    void visitOn() override {
        std::cout << "Starting visit" << std::endl;
        status = true;
    }
    void visitOff() override {
        std::cout << "Stopping visit" << std::endl;
        status = false;
    }
    void getStat() override {
        std::cout << "Visiting : " << status << std::endl;
        std::cout << std::endl;
    }
};
