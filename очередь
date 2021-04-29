#include <iostream>
#include <deque>

template <typename T, typename Container = std::deque<T>>
class Queue {
private:
    Container que;

public:
    Queue() {
        que = {};
    }
    const T& front() const {
        return que.front();
    }
    T& front() {
        return que.front();
    }
    void pop() {
        que.pop_front();
    }
    void push(const T& x) {
        que.push_back(x);
    }
    size_t size() const {
        return que.size();
    }
    bool empty() const {
        return que.empty();
    }
    bool operator==(const Queue& q) const {
        return que == q.que;
    }
    bool operator!=(const Queue& q) const {
        return que != q.que;
    }
};
