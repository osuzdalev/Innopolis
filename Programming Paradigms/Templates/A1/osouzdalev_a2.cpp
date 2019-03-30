#include <iostream>

using namespace std;

//function template printing out an array of any type
template <typename T>
void print_array(T* array, int size){
	for ( int i = 0; i<size; i++){
		cout << array[i] << ' ';
	}
	cout << endl;
}

//function from lecture slide reformated to a template
template < typename T >
void alignArray ( T* array, int size, T barrier ){
	for ( int i=0; i<size; i++ )
	{
		if ( array[i] < barrier ) array[i] += 2;
		else if ( array[i] > barrier ) array[i] -= 2; 
	}
	print_array(array, 5);
	cout << endl;
}

//creating a class 'List'
class List{
	double value;
	public:
		List(){
			value = 0;
		}
		List(double val){
			value = val;
		}
		// overloading all the necessary operators
			bool operator > (List& list){
				return value > list.value;
			}
			bool operator < (List& list){
				return value < list.value;
			}
			double operator += (const double &foo){
				return value = value + foo;
			}
			double operator -= (const double &foo){
				return value = value - foo;
			}
			double operator = (const double &foo){
				return value = foo;
			}

			//adding the possibility to print out the object
			friend ostream& operator << (ostream& os, const List& object);
};

//adding the possibility to print out the object
ostream& operator << (ostream& os, const List& object)  
{  
	os << object.value;  
	return os;
}

int main() {
	//Test 1 with type 'int'
	//barrier is 2
	int lst[5] = {0, 1, 2, 3, 4};
	print_array(lst, 5);
	alignArray(lst, 5, 2);
	
	//Test 2 with type 'char'
	//barrier is 'f'
	char lst_2[5] = {'a', 'b', 'c', 'd', 'e'};
	print_array(lst_2, 5);
	alignArray(lst_2, 5, 'f');
	
	//Test 3 with type 'UDT'
	//barrier = 2
	List obj_list[5] = {0, 1, 2, 3, 4}, barrier = 2;
	print_array(obj_list, 5);
	alignArray(obj_list, 5, barrier);
}