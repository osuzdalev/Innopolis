class NODE {
    int value;
    NODE * next;
public:
    NODE(int v): value(v), next(0) {}
    void add(NODE * n) {
        n->next = this->next;
        this->next = n;
    }
    bool operator!=(const NODE& other) const {
        return this->value != other.value;
    }
    operator int() {
        return value;
    }
    class iterator;
    friend class iterator;
    class iterator {
        NODE* obj;
    public:
        iterator(NODE* node): obj(node) {}
        int operator*() const {
            return obj->value;
        }
        iterator& operator++(int) {
            obj = obj->next;
            return *this;
        }
        bool operator!=(const iterator& other) const {
            return this->obj != other.obj;
        }
        operator NODE*() const {
            return obj;
        }
    };
};