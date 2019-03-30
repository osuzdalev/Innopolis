// Push/pop stack program to learn pointers through linked lists

#include <iostream>

using namespace std;

class Node{
	int value;
	Node *previous;
	public:
		//constructor 1
		Node(){
			value = 0;
			previous = 0;
		}
		//constructor 2
		Node(int V, Node *prv){
			value = V;
			previous = prv;
		}
		//function which returns a pointer, in that case: previous node
		Node *getprv(){
			return previous;
		}
		//function which returns value
		int getval(){
			return value;
		}
};

class Stack{
	int size;
	Node *top;
	public:
		Stack(){
			size = 0;
			top = 0;
		}
		
		int get_top_value(){
			return top->getval();
		}
	
		void pop(){
			Node *x = top;
			top = top->getprv();
			delete(x);
		}
		
		void push(int val){
			Node *X = new Node(val, top);
			top = X;
		}
		
		void clear(){
			while (top != 0){
				pop();
			}
		}
};

int main() {
	Stack stack_1;
	int i;
	for (i=0; i<10; i++){
		stack_1.push(i);
	}
	stack_1.pop();
	cout << stack_1.get_top_value();
	stack_1.push(20);
	cout << stack_1.get_top_value();
}