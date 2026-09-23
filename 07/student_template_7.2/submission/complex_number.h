// Simon Sutoris 7542170
// Eric Berger 7064584

#pragma once

#include <iostream>

template<typename T>
class ComplexNumber
{
public:
    ComplexNumber() noexcept = default;
    ComplexNumber(T real, T imaginary) : real_number(real), imaginary_number(imaginary) {};

    ComplexNumber& operator+=(const ComplexNumber& rhs);

    T getIm() const { return imaginary_number; };
    T getRe() const { return real_number; }

private:
    T real_number{};
    T imaginary_number{};
};

template<typename T>
ComplexNumber<T>& ComplexNumber<T>::operator+=(const ComplexNumber& other)
{
    real_number += other.getRe();
    imaginary_number += other.getIm();
    return *this;
}

template<typename T>
ComplexNumber<T> operator +(const ComplexNumber<T>& lhs, const ComplexNumber<T>& rhs)
{
    return ComplexNumber<T>(lhs.getRe() + rhs.getRe(), lhs.getIm() + rhs.getIm());
}

template<typename T>
std::ostream& operator<<(std::ostream& out, const ComplexNumber<T>& complex)
{
    if (complex.getIm() < 0) {
    out << complex.getRe() << "-" << -complex.getIm() << "i";
    }
    else {
    out << complex.getRe() << "+" << complex.getIm() << "i";
    }
    return out;
}
