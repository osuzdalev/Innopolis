#include <iostream>

using namespace std;

class searcher{
	public:
		searcher(){}

		/*
		Iterator type should support operator*();
			this operator should return a value of value type.
		Iterator type should support operator--();
			the result should denote the previous container element.
		Iterator type should support operator!=().
		*/
		template <typename type, typename it_type>
		static it_type find5 ( it_type start, it_type end, bool (*c)(type) ){
			it_type it = end;
			it--;
			while(!c(*it) && it != start){
				it--;
			}
			if(c(*it))
				return it; //success
			else
				return end; // fail
		}
};