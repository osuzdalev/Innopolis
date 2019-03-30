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