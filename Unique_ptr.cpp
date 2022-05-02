#include <cstddef>
#include <utility>
#include <memory>

template<typename T, typename Deleter = std::default_delete<T>>
class UniquePtr {
    std::tuple <T*, Deleter> ptr;

public:
    UniquePtr() {
        std::get<0>(ptr) = nullptr;
    }

    explicit UniquePtr(T* ptr_) {
        std::get<0>(ptr) = ptr_;
    }
    UniquePtr(T *ptr_, Deleter del_) {
        std::get<0>(ptr) = ptr_;
        std::get<1>(ptr) = del_;
    }

    UniquePtr(UniquePtr&& x) {
        std::swap(ptr, x.ptr);
    }
    UniquePtr& operator=(const std::nullptr_t &x) {
        std::get<1>(ptr)(std::get<0>(ptr));
        ptr = x;
        return *this;
    }

    UniquePtr& operator=(UniquePtr &&x) {
        std::swap(ptr, x.ptr);
        return *this;
    }
    ~UniquePtr() {
        std::get<1>(ptr)(std::get<0>(ptr));
    }

    T& operator*() const {
        return *std::get<0>(ptr);
    }
    T* operator->() const {
        return std::get<0>(ptr);
    }
    T* release() {
        T* x = std::get<0>(ptr);
        std::get<0>(ptr) = nullptr;
        return x;
    }
    void reset(T* x) {
        std::get<1>(ptr)(std::get<0>(ptr));
        std::get<0>(ptr) = x;
    }

    void swap(UniquePtr &x) {
        std::swap(ptr, x.ptr);
    }

    T* get() const {
        return std::get<0>(ptr);
    }

    explicit operator bool() {
        return std::get<0>(ptr) != nullptr;
    }
    const Deleter &get_deleter() const {
        return std::get<1>(ptr);
    }

    Deleter &get_deleter() {
        return std::get<1>(ptr);
    }
};
