#include <stdio.h>


class Node {
	int value;
	Node* next;
public:
	Node(int v) : value(v), next(0) { }

	//I'm not sure in correctness of add() implementation, but this is bycicle for implement list only by Node class in correct List ADT (Khan DSA one love)
	Node* end() {
		Node *tmp = this;
		while(tmp->next != 0) {
			tmp = tmp->next;
		}
		return tmp;
	}

	const int& getValue() {
		return value;
	}

	Node* getNext() {
		return next;
	}
	void add(Node* n) {
		n->next = this->next; this->next = n;
	}

	bool operator!=(Node& other) {
		return other.getValue() != value;
	}

	operator int() {
		return value;
	}

	class Iterator;
	friend class Iterator;
	class Iterator {
		Node *p;
	public:
		Iterator(Node *node) {
			p = node;
		}
		int operator*() {
			return p->getValue();
		}
		void operator++() {
			p = p->getNext();
		}
		bool operator!=(Node& other) {
			return p != &other;
		}

	};
};



/*
 *Requirenments:
 *
 *	P container must implement method: P++ for iterate throw items
 *	P container must implement method: P*  to compare its object with target value
 *	P container must implement method: P!= to check if it is border element of data structure
 *
 */
template <typename P, typename T>
T* find5 ( P first, P beyond, const T& x) {
	P p = first;
	while(p != beyond && *p != x) {
		p++;
	}
	return (T*)p; // fail or success
}


int main() {
	Node *list = new Node(0);
	int i;
	for(i = 1; i < 10; i++) {
		list->end()->add(new Node(i));
	}

	int *p = find5<Node *, int>(list, NULL, 7);
	printf("%d\n", *p);

	return 0;
}