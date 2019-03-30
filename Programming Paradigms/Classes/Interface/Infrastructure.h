#include <string>
#include <iostream>


//Base Class
class Infrastructure{
private:
    std::string name;
    std::string location;
    std::string type;
    std::string use;
public:
    //all infrastructure have next characteristics: name, location, type, use
    void setBaseCharacteristics(const std::string n, const std::string l, const std::string t, const std::string u){
        name = n;
        location = l;
        type = t;
        use = u;
    }
    void getBaseCharacteristics(){
        std::cout << "Name : " << name << std::endl;
        std::cout << "Location : " << location << std::endl;
        std::cout << "Type : " << type << std::endl;
        std::cout << "Use : " << use << std::endl;
        std::cout << std::endl;
    }
};

//Interface for
class IDoorSecurity{
public:
    virtual void lockDoor() = 0;
    virtual void unlockDoor() = 0;
    virtual void doorState() = 0;
};

class Building : public Infrastructure, IDoorSecurity{
private:
    //buildings also have characteristics that are their own
    int floors = 0;
    bool locked = false;
public:
    //interface function implementation
    void lockDoor() override{
        std::cout << "Locking doors" << std::endl;
        locked = true;
    }
    void unlockDoor() override {
        std::cout << "Unlocking doors" << std::endl;
        locked = false;
    }
    void doorState() override {
        std::cout << "Locked : " << locked << std::endl;
        std::cout << std::endl;
    }
    //function for class
    void setFloors(int f){
        std::cout << "Setting floors" << std::endl;
        floors = f;
    }
    void showSize(){
        std::cout << "Floors : " << floors << std::endl;
        std::cout << std::endl;
    }
};

class Utilities : public Infrastructure, IDoorSecurity{
private:
    //Utilities have characteristics of their own
    std::string natural_res;
    bool energy;
    bool locked = false;
public:
    //interface function implementation
    void lockDoor() override {
        std::cout << "Locking doors" << std::endl;
        locked = true;
    }
    void unlockDoor() override {
        std::cout << "Unlocking doors" << std::endl;
        locked = false;
    }
    void doorState() override {
        std::cout << "Locked : " << locked << std::endl;
        std::cout << std::endl;
    }
    //special function for class
    void setNaturalRes(const std::string l){
        std::cout << "Setting Natural Resource" << std::endl;
        natural_res = l;
    }
    void showNaturalRes(){
        std::cout << "Resource Used : " << natural_res << std::endl;
        std::cout << std::endl;
    }

    void getEnergy(bool b){
        energy = b;
    }
    void isEnergy(){
        std::cout << "Produces Energy : " << energy << std::endl;
        std::cout << std::endl;
    }
};

//This class does not need a DoorSecurity interface
class Transportation : public Infrastructure{
private:
    //Transport also have characteristics that are their own
    int length;
    bool high_traffic;
public:
    void setLength(int l){
        std::cout << "Setting length" << std::endl;
        length = l;
    }
    void getLength(){
        std::cout << "Length : " << length << std::endl;
        std::cout << std::endl;
    }

    void setTraffic(bool b){
        std::cout << "Setting Traffic" << std::endl;
        high_traffic = b;
    }
    void showTraffic(){
        std::cout << "High Traffic : " << high_traffic << std::endl;
        std::cout << std::endl;
    }
};
