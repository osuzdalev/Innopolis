#include <iostream>

class Node {
    int value; // Node’s “semantics”
    Node* next;
public:
    Node(int v){
        value = v;
        next = NULL;
    }
    void add(Node* n){
        n->next = this->next;
        this->next = n;
    }
    bool operator != (Node& n){
        return value != n.value;
    }
    operator int(){
        return value;
    }
    Node* getNext(){
        return next;
    }
    class iterator;
    friend class iterator;
    class iterator {
        Node* p;
    public:
        iterator(Node* node){
            p = node;
        }
        int operator*(){
            return p->value;
        }
        void operator++(int){
            p = p->next;
        }
        bool operator!=(Node& n){
            return p->value != n.value;
        }
        operator Node*(){
            return p;
        }
        iterator end(){
            return iterator(NULL);
        }
    };
};

using namespace std;

typedef Node::iterator myIterator;

template < typename T, typename P >
P find5 ( P first, P beyond, const T& x )
{
    P p = first;
    while ( p != beyond && *p != x )
        p++;
    return p;
}

int main(){

    Node node1(1);
    Node node2(2);
    Node node3(6);
    Node node4(5);
    Node node5(4);
    node1.add(&node2);
    node2.add(&node3);
    node3.add(&node4);
    node4.add(&node5);

    myIterator it1(&node1);
    // iterate through "linked-list" using iterator and printing values of each node
    cout << "All elements of linked list are: " << endl;
    while(it1 != it1.end()){
        cout << *it1 << endl;
        it1++;
    }

    myIterator it2(&node1);
    // result should point to 6
    myIterator result = find5(it2, it2.end(), 6);

    cout << "Value that finds our function iterating through list: "
         << *result << endl;

	return 0;
}