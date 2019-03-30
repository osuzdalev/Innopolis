/*
Write your implementation of Range class template, with the following template
parameters:
1. The type of range {int,char,...}
2. Range lower bound (LB), i.e. LB<=range_value
3. Range upper bound (UB), i.e. range_value<=UB

The class Range should include the following constructors:
1. Constructor that initializes range from the variable of type T
2. Copy constructor

In both cases verify that the value lies within the specified range

The class Range should overload the following operators:
1. = (for variables of base types, such as {int,char,...}, and other Range
      objects with the same boundaries)
2. + (for variables of base types, such as {int,char,...}, and other Range
      objects with the same boundaries. This should create a new Range object)
3. - (for variables of base types, such as {int,char,...}, and other Range
      objects with the same boundaries. This should create a new Range object)
4. += (for variables of base types, such as {int,char,...}, and other Range
      objects with the same boundaries. Call an exception in case of going out
      of range)
5. -= (for variables of base types, such as {int,char,...}, and other Range
      objects with the same boundaries. Call an exception in case of going out
      of range)
6. ++ (increment Range variable by one. Call an exception in case of going out
      of range)
7. -- (decrement Range variable by one. Call an exception in case of going out
      of range)
8. < (for comparing two objects of type Range)
9. > (for comparing two objects of type Range)
10. Casting to long, int, double

The class Range should implement the following methods:
1. bool valid(): indicates that the value is within the specified range
2. T getVal(): returns the value of the Range

In the case when the value is out of range during the instantiation process
or after arithmetical operations, throw std::runtime_error("Relevant message")

Testing of your implementation will be done by calling the variations of the
following expressions:
      Range<int,L,U> a(value)
      a+b
      a-b
      a++
      b--
      a+=b
      b-=4
      a<b
      (long)b
*/
#include <iostream>

using namespace std;

template <typename T, T leftBorder, T rightBorder>
class Range{
	private:
		T value;
		Range(){}
	public:
		void isvalid(void){
			if (value<leftBorder || value>rightBorder)
				throw std::runtime_error("value out of boudaries");
		}
		//standard constructor
		Range(T v){
			value = v;
			isvalid();
		}
		Range(const Range &range){
			value = range.value;
		}
		
		Range operator = (Range Range1){
			value = Range1.value;
			Range<T, leftBorder, rightBorder> xx(value); 
			return xx;
		}
		
		//overloading + operator
		friend Range operator + (Range &Range1, Range &Range2){
			Range<T, leftBorder, rightBorder> Range3(0);
			Range3.value = Range1.value + Range2.value;
			Range3.isvalid();
			return Range3;
		}
		//overloading - operator
		friend Range operator - (Range &Range1, Range &Range2){
			Range<T, leftBorder, rightBorder> Range3(0);
			Range3.value = Range1.value - Range2.value;
			Range3.isvalid();
			return Range3;
		}
		//Prefix increment operator
		Range& operator ++ (void){
			value++;
			isvalid();
			return *this;
		}
		//Postfix increment operator
		Range& operator++(int){
			value++;
			isvalid();
			return *this;
		}
		//Prefix decrement operator
		Range& operator -- (void){
			value--;
			isvalid();
			return *this;
		}
		//Postfix decrement operator
		Range& operator--(int){
			value--;
			isvalid();
			return *this;
		}

		Range& operator += (Range& Range){
			value += Range.value;
			isvalid();
			return *this;
		}

		Range& operator -= (Range Range){
			value -= Range.value;
			isvalid();
			return *this;
		}
		//to isvalid value
		Range getval(){
			return value;
		}
		
		operator int(){
			return (int) value;
		}
		operator long(){
			return (long) value;
		}
		operator double(){
			return (double) value;
		}
		
		bool operator < (Range& Range){
			return value < Range.value;
		}
		bool operator > (Range& Range){
			return value > Range.value;
		}
};