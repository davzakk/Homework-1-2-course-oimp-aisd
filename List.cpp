#include <optional>
#include <iostream>

template <typename T = int>
class List {
private:
    class Node {
    public:
        Node() = default;
        Node(const T& x) : val_(x) {}
        std::optional<T> val_;
        Node* next_ptr_ = nullptr;
        Node* prev_ptr_ = nullptr;
    };

    void Insert(Node* node, const T& x) {
        Node* new_node = new Node(x);
        node->next_ptr_->prev_ptr_ = new_node;
        new_node->next_ptr_ = node->next_ptr_;
        new_node->prev_ptr_ = node;
        node->next_ptr_ = new_node;
    }

    void Erase(Node* node) {
        node->prev_ptr_->next_ptr_ = node->next_ptr_;
        node->next_ptr_->prev_ptr_ = node->prev_ptr_;
        delete node;
    }

    class Iterator {
        const Node* ptr_ = nullptr;
        Iterator(const Node* ptr) : ptr_(ptr) {}

    public:
        Iterator() = default;
        friend List;

        const T& operator*() const {
            return ptr_->val_.value();
        }

        bool operator==(Iterator x) const {
            return ptr_ == x.ptr_;
        }

        bool operator!=(Iterator x) const {
            return ptr_ != x.ptr_;
        }
        Iterator& operator++() {
            ptr_ = ptr_->next_ptr_;
            return *this;
        }
        Iterator& operator--() {
            ptr_ = ptr_->prev_ptr_;
            return *this;
        }

        Iterator operator++(int) {
            Node* x = ptr_;
            ptr_ = ptr_->next_ptr_;
            return *x;
        }
        Iterator operator--(int) {
            Node* x = ptr_;
            ptr_ = ptr_->prev_ptr_;
            return *x;
        }
    };

    Node dum;
    size_t sz = 0;

public:
    List() {
        dum.next_ptr_ = dum.prev_ptr_ = &dum;
    }

    void push_back(const T& x) {
        Insert(dum.prev_ptr_, x);
        ++sz;
    }

    void pop_back() {
        Erase(dum.prev_ptr_);
        --sz;
    }

    void push_front(const T& x) {
        Insert(&dum, x);
        ++sz;
    }
    void pop_front() {
        Erase(dum.next_ptr_);
        --sz;
    }

    Iterator begin() const {
        return Iterator(dum.next_ptr_);
    }

    Iterator end() const {
        return Iterator(&dum);
    }

    size_t size() const {
        return sz;
    }

    ~List() {
        while (sz > 0) {
            pop_back();
        }
    }
};
