#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

template <typename T>
class Polynomial {
private:
    vector<T> _coefficients;
    void Canonize() {
        while (_coefficients.size() && _coefficients.back() == T(0)) {
            _coefficients.pop_back();
        }
    }

public:
    Polynomial(const vector<T>& c) : _coefficients(c) {
        Canonize();
    }

    Polynomial(const T& a) : _coefficients({a }) {
        Canonize();
    }

    template <typename Iter>
    Polynomial(Iter begin, Iter end) : _coefficients(begin, end) {
        Canonize();
    }

    bool operator==(const Polynomial<T>& other) const {
        return _coefficients == other._coefficients;
    }
    bool operator!=(const Polynomial<T>& other) const {
        return !(*this == other);
    }
    bool operator==(const T& other) const {
        return _coefficients == Polynomial<T>({other})._coefficients;
    }
    bool operator!=(const T& other) const {
        return !(*this == Polynomial<T>({other}));
    }
    Polynomial<T>& operator+=(const Polynomial<T>& other) {
        auto min_size = min(_coefficients.size(), other._coefficients.size());
        for (size_t i = 0; i < min_size; ++i) {
            _coefficients[i] += other._coefficients[i];
        }

        if (other._coefficients.size() > _coefficients.size()) {
            _coefficients.insert(_coefficients.end(),
                                 other._coefficients.begin() + min_size, other._coefficients.end());
        }
        Canonize();
        return *this;
    }

    Polynomial<T> operator+(const Polynomial<T>& other) const {
        Polynomial<T> result(_coefficients);
        return result += other;
    }
    Polynomial<T> operator+(const T& other) const {
        Polynomial<T> result(_coefficients);
        return result += Polynomial(other);
    }
    Polynomial<T>& operator-=(const Polynomial<T>& other) {
        auto min_size = min(_coefficients.size(), other._coefficients.size());
        auto max_size = max(_coefficients.size(), other._coefficients.size());
        for (size_t i = 0; i < min_size; ++i) {
            _coefficients[i] -= other._coefficients[i];
        }

        if (other._coefficients.size() > _coefficients.size()) {
            for (size_t i = min_size; i < max_size; ++i) {
                _coefficients.push_back(-other._coefficients[i]);
            }
        }
        Canonize();
        return *this;
    }

    Polynomial<T> operator-(const Polynomial<T>& other) const {
        Polynomial<T> result(_coefficients);
        return result -= other;
    }

    Polynomial<T>& operator*=(const Polynomial<T>& other) {
        vector<T> vec;
        ssize_t saved_size = static_cast<ssize_t>(_coefficients.size());
        vec.resize(other._coefficients.size() + _coefficients.size());
        for (ssize_t i = saved_size - 1; i >= 0; --i) {
            for (ssize_t j = static_cast<ssize_t>(other._coefficients.size()) - 1; j >= 0; --j) {
                vec[i + j] += _coefficients[i] * other._coefficients[j];
            }
        }
        (*this)._coefficients = vec;
        (*this).Canonize();
        return *this;
    }

    Polynomial<T> operator*(const Polynomial<T>& other) const {
        Polynomial<T> new_lhs(*this);
        new_lhs *= other;
        return new_lhs;
    }
    T operator[](size_t i) const {
        if (i >= _coefficients.size()) {
            return T(0);
        }
        return _coefficients[i];
    }

    int Degree() const {
        return static_cast<int> (_coefficients.size()) - 1;
    }

    typename vector<T>::const_iterator begin() const {
        return _coefficients.cbegin();
    }

    typename vector<T>::const_iterator end() const {
        return _coefficients.cend();
    }

    T operator()(T x) const {
        if (_coefficients.size() == 0) {
            return T(0);
        }
        T y = x;
        T summ = _coefficients[0];
        for (size_t i = 1; i < _coefficients.size(); ++i) {
            summ += _coefficients[i] * y;
            y *= x;
        }
        return summ;
    }

    size_t size() const {
        return _coefficients.size();
    }
    Polynomial<T> operator&(const Polynomial<T>& other) const {
        Polynomial<T> result(0), power(1);
        for (size_t i = 0; i < (*this).size(); ++i) {
            result += power * (*this)._coefficients[i];
            power *= other;
        }
        result.Canonize();
        return result;
    }
    Polynomial<T> operator/(const Polynomial<T>& other) const {
        vector<T> result(_coefficients.size() -
        other._coefficients.size() + 1, 0);
        Polynomial<T> a = *this;
        while (a.Degree() >= other.Degree()) {
            size_t i = a.size() - 1, j = other.size() - 1;
            vector<T> mon(i - j + 1, T(0));
            mon[i - j] = T(1);
            result[i - j] = (a._coefficients[i] / other._coefficients[j]);
            if (a._coefficients[i] / other._coefficients[j] == T(0)) {
                break;
            }
            a -= Polynomial<T>((other * Polynomial(mon) *
                                (a._coefficients[i] / other._coefficients[j])));
        }
        Polynomial<T> Q(result);
        return Q;
    }
    Polynomial<T> operator%(const Polynomial<T>& other) const {
        Polynomial<T> x = *this - (((*this) / other) * other);
        x.Canonize();
        return x;
    }
    Polynomial<T> operator,(const Polynomial<T>& other) const {
        Polynomial<T> a = (*this), b = other;
        while (a * b != Polynomial(T(0))) {
            if (a.Degree() > b.Degree()) {
                a = a % b;
            } else if (a.Degree() < b.Degree()) {
                b = b % a;
            } else {
                if (a._coefficients[a.size() - 1] > b._coefficients[b.size() - 1]) {
                    a = a % b;
                } else {
                    b = b % a;
                }
            }
        }
        Polynomial<T> ans = a + b;
        for (size_t i = 0; i < ans.size(); ++i) {
            ans._coefficients[i] = ans._coefficients[i] / ans._coefficients[ans.size() - 1];
        }
        return ans;
    }
};

template <typename T>
Polynomial<T> operator+(const T& other, const Polynomial<T>& f) {
    return f + other;
}

template <typename T>
Polynomial<T> operator*(const T& other, const Polynomial<T>& f) {
    return f * other;
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const Polynomial<T>& A) {
    if (A.size() == 0) {
        out << T(0);
        return out;
    }
    for (size_t i = A.size() - 1; i >= 0; --i) {
        if (A[i] == T(0)) {
            if (A.size() == 1) {
                out << T(0);
            }
            if (i == 0) {
                break;
            }
            continue;
        } else if (A[i] == T(1) || A[i] == T(-1)) {
            if (0 == A.size() - 1) {
                cout << A[i];
            } else if (i == 0) {
                if (A[i] < T(0)) {
                    out << A[i];
                } else {
                    out << "+" << A[i];
                }
            } else {
                if (A[i] == T(-1)) {
                    out << "-";
                } else if (A[i] == T(1)) {
                    if (i == A.size() - 1) {
                        out << "";
                    } else {
                        out << "+";
                    }
                }
            }
        } else {
            if (A[i] > T(0)) {
                if (i == A.size() - 1) {
                    out << A[i];
                    if (i > 0) {
                        out << "*";
                    }
                } else {
                    out << "+" << A[i];
                    if (i > 0) {
                        out << "*";
                    }
                }
            } else {
                out << A[i];
                if (i > 0) {
                    out << "*";
                }
            }
        }
        if (i > 0) {
            out << "x";
            if (i > 1) {
                out << "^" << i;
            }
        }
        if (i == 0) {
            break;
        }
    }
    return out;
}
