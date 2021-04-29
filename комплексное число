#include <iostream>
#include <cmath>

class Complex {
public:
    Complex() {
        x = 0, y = 0;
    }
    Complex(const double _x) : x(_x), y(0) {}
    Complex(const double _x, const double _y) : x(_x), y(_y) {}
    Complex operator+(const Complex& rhs) const {
        return Complex(x + rhs.x, y + rhs.y);
    }
    Complex operator+(const double& num) const {
        return *this + Complex(num);
    }
    Complex operator+() const {
        return *this;
    }
    Complex& operator+=(const Complex& rhs) {
        *this = *this + rhs;
        return *this;
    }
    Complex operator-(const Complex& rhs) const {
        return Complex(x - rhs.x, y - rhs.y);
    }
    Complex operator-(const double& num) const {
        return *this - Complex(num);
    }
    Complex& operator-=(const Complex& rhs) {
        *this = *this - rhs;
        return *this;
    }
    Complex operator*(const Complex& rhs) const {
        return Complex(x * rhs.x - y * rhs.y, x * rhs.y + y * rhs.x);
    }
    Complex operator*(const double& num) const {
        return *this * Complex(num);
    }
    Complex operator-() const {
        return *this * Complex(-1);
    }
    Complex& operator*=(const Complex& rhs) {
        *this = *this * rhs;
        return *this;
    }
    Complex operator/(const Complex& rhs) const {
        double den = rhs.x * rhs.x + rhs.y * rhs.y;
        return Complex((x * rhs.x + y * rhs.y) / den, (rhs.x * y - x * rhs.y) / den);
    }
    Complex operator/(const double& num) const {
        return *this / Complex(num);
    }
    Complex& operator/=(const Complex& rhs) {
        *this = *this / rhs;
        return *this;
    }
    bool operator==(const Complex& rhs) const {
        return (this->x == rhs.x) && (this->y == rhs.y);
    }
    bool operator!=(const Complex& rhs) const {
        return !(*this == rhs);
    }
    double Re() const {
            return x;
    }
    double Im() const {
        return y;
    }

private:
    double x, y;
};
Complex operator*(const double& num, Complex rhs) {
    return rhs * Complex(num);
}
double Abs(const Complex& rhs) {
    return sqrt(rhs.Re() * rhs.Re() + rhs.Im() * rhs.Im());
}

std::ostream& operator<<(std::ostream& cout, Complex rhs) {
    return cout << rhs.Re() << " " << rhs.Im() << "\n";
}
