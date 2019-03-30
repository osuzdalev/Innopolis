#include <iostream>

using namespace std;

class Box{
	public:
		double length;
		double breadth;
		double width;
};

int main() {
	Box Box1;
	Box Box2;
	double volume = 0.0;
	
	Box1.length = 5.0;
	Box1.breadth = 5.0;
	Box1.width = 5.0;
	
	Box2.length = 3.0;
	Box2.breadth = 3.0;
	Box2.width = 3.0;
	
	cout << Box2.width << endl;
	
	volume = Box1.length * Box1.breadth * Box1.width;
	cout << "Volume of Box1 : " << volume << endl;
	
	volume = Box2.length * Box2.breadth * Box2.width;
	cout << "Volume of Box2 : " << volume << endl;
	
	return 0;
}