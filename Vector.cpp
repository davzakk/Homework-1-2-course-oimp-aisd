#include <cstddef>
#include <utility>
#include <memory>
#include <assert.h>
template <typename T>
struct RawMemory {
    T* buf = nullptr;
    size_t cp = 0;
    static T* Allocate(size_t n) {
        return static_cast<T*> (operator new(n * sizeof(T)));
    }

    static void Deallocate(T* buf) {
        operator delete(buf);
    }

    void Swap(RawMemory& x) noexcept {
        std::swap(buf, x.buf);
        std::swap(cp, x.cp);
    }
    RawMemory() = default;
    RawMemory(size_t n) {
        buf = Allocate(n);
        cp = n;
    }
    RawMemory(const RawMemory&) = delete;
    RawMemory(RawMemory&& x) noexcept {
        Swap(x);
    }

    RawMemory& operator = (const RawMemory&) = delete;
    RawMemory& operator = (RawMemory&& x) {
        Swap(x);
        return *this;
    }

    ~RawMemory() {
        Deallocate(buf);
    }

    T* operator + (size_t i) {
        return buf + i;
    }
    const T* operator + (size_t i) const {
        return buf + i;
    }
    T& operator[] (size_t i) {
        return buf[i];
    }

    const T& operator[] (size_t i) const {
        return buf[i];
    }
};

template <typename T>
class Vector {
    RawMemory<T> data;
    size_t sz = 0;

    static void Construct(void * buf) {
        new (buf) T();
    }

    static void Construct(void * buf, const T& x) {
        new (buf) T(x);
    }
    static void Construct(void * buf, T && x) {
        new (buf) T(std::move(x));
    }
    static void Destroy(T* buf) {
        buf->~T();
    }

public:
    Vector() = default;
    Vector(size_t n) : data(n) {
        std::uninitialized_value_construct_n(data.buf, n);
        sz = n;
    }
    Vector(const Vector& x) : data(x.sz) {
        std::uninitialized_copy_n(x.data.buf, x.sz, data.buf);
        sz = x.sz;
    }

    void swap(Vector& x) noexcept {
        data.Swap(x.data);
        std::swap(sz, x.sz);
    }
    Vector(Vector&& x) noexcept {
        swap(x);
    }
    ~Vector() {
        std::destroy_n(data.buf, sz);
    }

    Vector& operator = (const Vector& x) {
        if (x.sz > data.cp) {
            Vector tmp(x);
            swap(tmp);
        } else {
            for (size_t i = 0; i < sz && i < x.sz; ++i) {
                data[i] = x.data[i];
            }
            if (sz < x.sz) {
                std::uninitialized_copy_n(x.data.buf + sz, x.sz - sz, data.buf + sz);
            } else if (sz > x.sz) {
                std::destroy_n(data.buf + x.sz, sz - x.sz);
            }
            sz = x.sz;
        }
        return *this;
    }

    Vector& operator = (Vector&& x) noexcept {
        Swap(x);
        return *this;
    }
    void reserve(size_t n) {
        if (n > data.cp) {
            RawMemory<T> data2(n);
            std::uninitialized_move_n(data.buf, sz, data2.buf);
            std::destroy_n(data.buf, sz);
            data = std::move(data2);
        }
    }

    void resize(size_t n) {
        reserve(n);
        if (sz < n) {
            std::uninitialized_value_construct_n(data + sz, n - sz);
        } else if (sz > n) {
            std::destroy_n(data + n, sz - n);
        }
        sz = n;
    }

    void push_back(const T& x) {
        if (sz == data.cp) {
            reserve(sz == 0 ? 1 : sz * 2);
        }
        new (data + sz) T(x);
        ++sz;
    }
    void push_back(const T&& x) {
        if (sz == data.cp) {
            reserve(sz == 0 ? 1 : sz * 2);
        }
        new (data + sz) T(std::move(x));
        ++sz;
    }
    void pop_back() {
        std::destroy_at(data + sz - 1);
        --sz;
    }
    T* begin() {
        return reinterpret_cast<T*>(data.buf);
    }
    T* begin() const {
        return reinterpret_cast<T*>(data.buf);;
    }
    T* end() {
        return reinterpret_cast<T*>(data.buf + sz);
    }

    T* end() const {
        return reinterpret_cast<T*>(data.buf + sz);
    }
    void clear() {
        std::destroy_n(data.buf, sz);
        sz = 0;
    }

    size_t size() const {
        return sz;
    }
    size_t capacity() const {
        return data.cp;
    }
    const T& operator[](size_t i) const {
        return data[i];
    }
    T& operator[](size_t i) {
        return data[i];
    }
};
