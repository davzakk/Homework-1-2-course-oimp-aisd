#include <iostream>
#include <numeric>


class Rational {
public:
    Rational() {
        x = 0, y = 1;
    }
    Rational(const int _x) : x(_x), y(1) {}
    Rational(const int _x, const int _y) : x(_x), y(_y) {
        if (y == 0) {
            throw std::logic_error("");
        }
        int d = std::gcd(x, y);
        x /= d;
        y /= d;
        if (y < 0) {
            x *= -1;
            y *= -1;
        }
    }
    Rational operator+(const Rational& rhs) const {
        return Rational(x * rhs.y + rhs.x * y, y * rhs.y);
    }
    Rational operator+(const int& num) const {
        return *this + Rational(num);
    }
    Rational operator+() const {
        return *this;
    }
    Rational& operator+=(const Rational& rhs) {
        *this = *this + rhs;
        return *this;
    }
    Rational operator-(const Rational& rhs) const {
        return Rational(x * rhs.y - rhs.x * y, y * rhs.y);
    }
    Rational operator-(const int& num) const {
        return *this - Rational(num);
    }
    Rational& operator-=(const Rational& rhs) {
        *this = *this - rhs;
        return *this;
    }
    Rational operator*(const Rational& rhs) const {
        return Rational(x * rhs.x, y * rhs.y);
    }
    Rational operator*(const int& num) const {
        return *this * Rational(num);
    }
    Rational operator-() const {
        return *this * Rational(-1);
    }
    Rational& operator*=(const Rational& rhs) {
        *this = *this * rhs;
        return *this;
    }
    Rational operator/(const Rational& rhs) const {
        return Rational(x * rhs.y, y * rhs.x);
    }
    Rational operator/(const int& num) const {
        return *this / Rational(num);
    }
    Rational& operator/=(const Rational& rhs) {
        *this = *this / rhs;
        return *this;
    }
    Rational operator++(int) {
        Rational tmp(*this);
        *this += Rational(1, 1);
        return tmp;
    }
    Rational& operator++() {
        return *this += Rational(1, 1);
    }
    Rational operator--(int) {
        Rational tmp(*this);
        *this -= Rational(1, 1);
        return tmp;
    }
    Rational& operator--() {
        return *this -= Rational(1, 1);
    }
    bool operator==(const Rational& rhs) const {
        return (this->x == rhs.x) && (this->y == rhs.y);
    }
    bool operator!=(const Rational& rhs) const {
        return !(*this == rhs);
    }
    int Numerator() const {
        return x;
    }
    int Denominator() const {
        return y;
    }

private:
    int x, y;
};
Rational operator*(const int& num, Rational rhs) {
    return rhs * Rational(num);
}

std::ostream& operator<<(std::ostream& cout, Rational rhs) {
    return cout << rhs.Numerator() << " " << rhs.Denominator() << "\n";
}
