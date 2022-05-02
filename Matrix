#include <iostream>
#include <vector>
#include <cstddef>
#include <assert.h>


template<typename T>
class Matrix {
private:
    std::vector<std::vector<T>> data;
    size_t N, M;
    class Iterator {
    private:
        size_t i, j;
        Matrix<T>& M;

    public:
        Iterator(size_t I, size_t J, Matrix<T>& D) : i(I), j(J), M(D) {}

        T& operator*() const {
            return M[i][j];
        }

        Iterator& operator++() {
            ++j;
            if (j == M.M) {
                j = 0;
                ++i;
            }
            return *this;
        }
        Iterator operator++(int) {
            auto old(*this);
            ++j;
            if (j == M.M) {
                j = 0;
                ++i;
            }
            return old;
        }
        bool operator==(Iterator other) const {
            return i == other.i && j == other.j;
        }
        bool operator!=(Iterator other) const {
            return !(*this == other);
        }
    };

    class ConstIterator {
    private:
        size_t i, j;
        const Matrix<T>& M;

    public:
        ConstIterator(size_t I, size_t J, const Matrix<T>& D) : i(I), j(J), M(D) {}

        T operator*() const {
            return M[i][j];
        }

        ConstIterator& operator++() {
            ++j;
            if (j == M.M) {
                j = 0;
                ++i;
            }
            return *this;
        }
        ConstIterator operator++(int) {
            auto old(*this);
            ++j;
            if (j == M.M) {
                j = 0;
                ++i;
            }
            return old;
        }
        bool operator==(ConstIterator other) const {
            return i == other.i && j == other.j;
        }
        bool operator!=(ConstIterator other) const {
            return !(*this == other);
        }
    };

public:
    Iterator begin() {
        return Iterator(0, 0, *this);
    }
    Iterator end() {
        return Iterator(N, 0, *this);
    }
    ConstIterator begin() const {
        return ConstIterator(0, 0, *this);
    }
    ConstIterator end() const {
        return ConstIterator(N, 0, *this);
    }
    Matrix(const std::vector<std::vector<T>>& x) {
        data = x;
        N = x.size();
        M = x[0].size();
    }
    Matrix(const size_t& n, const size_t& m) {
        N = n;
        M = m;
        data.resize(N, std::vector<T>(M, 0));
    }
    std::pair<size_t, size_t> size() const {
        return {data.size(), data[0].size()};
    }

    std::vector<T>& operator[](size_t i) {
        return data[i];
    }
    const std::vector<T>& operator[](size_t i) const {
        return data[i];
    }

    Matrix& operator+=(const Matrix& B) {
        for (size_t i = 0; i != B.size().first; ++i) {
            for (size_t j = 0; j != B.size().second; ++j) {
                data[i][j] += B[i][j];
            }
        }
        return *this;
    }
    Matrix operator*=(const Matrix& B) {
        assert(M == B.N);
        Matrix M(N, B.M);
        for (size_t i = 0; i != (*this).size().first; ++i) {
            for (size_t j = 0; j != (B).size().second; ++j) {
                for (size_t k = 0; k != B.size().first; ++k) {
                    M[i][j] += (*this)[i][k] * B[k][j];
                }
            }
        }
        *this = M;
        return *this;
    }
    Matrix& operator*=(const T& B) {
        for (size_t i = 0; i != N; ++i) {
            for (size_t j = 0; j != M; ++j) {
                data[i][j] *= B;
            }
        }
        return *this;
    }
    template <typename R>
    Matrix<T>& operator=(const Matrix<T>& rhs) const {
        return rhs;
    }
    Matrix& transpose() {
        Matrix result(M, N);
        for (size_t i = 0; i != N; ++i) {
            for (size_t j = 0; j != M; ++j) {
                result[j][i] = data[i][j];
            }
        }
        *this = result;
        return *this;
    }

    Matrix transposed() const {
        auto result(*this);
        result.transpose();
        return result;
    }
};

template  <typename T>
Matrix<T> operator+(const Matrix<T>& A, const Matrix<T>& B) {
    Matrix<T> result(A);
    result += B;
    return result;
}

template<typename T, typename Y>
Matrix<T> operator*(const Matrix<T>& A, const Y& B) {
    Matrix<T> result(A);
    T multiplier(B);
    result *= multiplier;
    return result;
}
template<typename T>
Matrix<T> operator*(const Matrix<T>& A, const Matrix<T>& B) {
    Matrix<T> result(A);
    result *= B;
    return result;
}
template<typename T, typename Y>
Matrix<T> operator*(const Y& B, const Matrix<T>& A) {
    Matrix<T> result(A);
    result *= B;
    return result;
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const Matrix<T>& A) {
    for (size_t i = 0; i != A.size().first; ++i) {
        for (size_t j = 0; j != A.size().second; ++j) {
            out << A[i][j];
            if (j != A.size().second - 1) {
                out << "\t";
            }
        }
        if (i != A.size().first - 1) {
            out << "\n";
        }
    }
    return out;
}
