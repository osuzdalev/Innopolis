#include <iostream>
#include "Infrastructure.h"
#include "Citizen.h"

int main() {

    //creating a Building
    Building bank;
    //basic functions
    bank.setBaseCharacteristics("Bank", "3rd Street", "Node", "Money");
    bank.getBaseCharacteristics();
    //Interface functions
    bank.doorState();
    bank.lockDoor();
    bank.doorState();
    //special functions
    bank.setFloors(5);
    bank.showSize();

    //Creating a Utility
    Utilities dam;
    //basic functions
    dam.setBaseCharacteristics("Dam", "Up main Raiver", "Node", "Produce energy");
    dam.getBaseCharacteristics();
    //Interface functions
    dam.lockDoor();
    dam.doorState();
    dam.unlockDoor();
    dam.doorState();
    //special functions
    dam.setNaturalRes("Water");
    dam.showNaturalRes();
    dam.getEnergy(true);
    dam.isEnergy();

    //Creating a Transport
    Transportation metro;
    //basic functions
    metro.setBaseCharacteristics("Metro", "City Center", "Edge", "Sub terran transport");
    metro.getBaseCharacteristics();
    //special functions
    metro.setLength(8);
    metro.getLength();
    metro.setTraffic(true);
    metro.showTraffic();

    //Creating a Worker (BusDriver)
    BusDriver Pablos;
    //basic functions
    Pablos.setBaseCharacteristics("Pablos", "Male", 25);
    Pablos.getBaseCharacteristics();
    //Interface functions
    Pablos.workOn();
    Pablos.getStat();
    Pablos.workOff();
    Pablos.getStat();
    //special functions
    Pablos.getBusState();

    //Creating a Worker (Teacher)
    Teacher Elena;
    //basic functions
    Elena.setBaseCharacteristics("Elena", "Female", 22);
    Elena.getBaseCharacteristics();
    //Interface functions
    Elena.workOn();
    Elena.getStat();
    Elena.workOff();
    Elena.getStat();
    //special functions
    Elena.setCourse("English");
    Elena.getCourse();

    //Creating a Tourist
    Tourist Julia;
    //basic functions
    Julia.setBaseCharacteristics("Julia", "Female", 23);
    Julia.getBaseCharacteristics();
    //special functions
    Julia.visitOn();
    Julia.getStat();
    Julia.visitOff();
    Julia.getStat();

    return 0;
}