#include <iostream>
#include <assert.h>

using namespace std;

class NODE{
	public:
		int val;
		NODE * next;
		bool flag;
		NODE(){
			val = 0;
			next = NULL;
			flag=0;
		}
};

class linked{
	public:
		NODE* head;
		//create first element
		linked(int g){
			head = new NODE;
			head->val = g;
			NODE * tmp = new NODE;
			tmp->flag = 1;
			head->next = tmp;
		}

		void push_back(int g){
			NODE * tmp = head;
			while((tmp->next)->flag==0)
				tmp=tmp->next;
			NODE * f = new NODE;
			f->val = g;
			NODE*  rr  = tmp->next;
			tmp->next = f;
			f->next = rr;
		}
		void push_front(int g){
			NODE * tmp = head;
			NODE * f = new NODE;
			f->val =g;
			f->next = head;
			head = f;
		}
		NODE * getend(){
			NODE * tmp = head;
			while(tmp->next)
				tmp=tmp->next;
			return tmp;
		}
		NODE * begin(){
			return head;
		}

		class literator{
			private:
				NODE * it;
			public:
				literator(NODE* init){
					it = init;
				}
				
				NODE * getit(){
					return it;
				}
				
				literator operator --(){
					if(it->next==NULL){
						printf("OUT OF RANGE\n");
						assert(0);
					}
					it = it->next;
				}
				int operator*(){
					return it->val;
				}
				bool operator != (literator other){
					if(it == other.getit()) return false;
					return true;
				}
				void operator = (NODE* xx){
					it = xx;
				}
			};

			literator end(){
				literator ret(getend());
				return ret;
			}
};

//generalising the object
template <typename T, T N>
class bigger{
	public:
		bool operator() (T x) const{
			return x>N;
		}
};

template <typename T, T N>
class lesser{
	public:
		bool operator() (T x) const{
			return x<N;
		}
};

template <typename T, T N>
class is_equal{
	public:
		bool operator() (T x) const{
			return x==N;
		}
};

//generalising the function
//1st parameter should allow the following operators:
// '()' '>' '<' '=='
template <typename P , typename Comparator>
P find ( P first, P last , Comparator comp )
{
	P p = last;
	while ( p != (first ) && !(comp(*p)))
	{
		--p;
	}
	return p; // fail
}

template < typename T, typename P >
P find5 ( P first, P last , bool (*c)(T) )
{
	P p = last;
	while ( p != (first ) && !(c(*p)))
	{
		--p;
	}
	return p; // fail
}

bool less_t5( int x ) { return x < 5; }

int main(){
	linked L(0);// new linked list;
	for(int i=1;i<=8;i++){
		L.push_back(i);
	}
	/*
	for(linked::literator it = L.begin(); it != L.end(); ++it){
		cout << *it<< endl;
	}*/
	cout << L.end();
	cout << *find5<int, linked::literator>( L.begin(), L.end() , less_t5 ) <<endl;
	return 0;
}