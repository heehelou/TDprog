#include "fraction.hpp"
#include "utils.hpp"
#include <cmath> 
#include <iostream>

std::ostream& operator<<(std::ostream& os, Fraction const& p) {
    return os << p.numerator << "/ " << p.denominator;
}



// Fraction operator+(Fraction const& f1, Fraction const& f2) {
//     return simplify({
//         f1.numerator * f2.denominator + f2.numerator * f1.denominator,
//         f1.denominator * f2.denominator
//     });
// }

Fraction& Fraction::operator+=(Fraction const& f2) {
    numerator = numerator * f2.denominator + f2.numerator * denominator;
    denominator = denominator * f2.denominator;

    *this = simplify(*this);
    return *this;
}

Fraction operator+(Fraction f1, Fraction const& f2) {
    f1 += f2; 
    return f1;
}

// Fraction add(Fraction const& f1, Fraction const& f2) {
//     Fraction result {
//         f1.numerator * f2.denominator + f2.numerator * f1.denominator
//         f1.denominator * f2.denominator
//     };

//     return simplify(result);
// }


// Fraction operator-(Fraction const& f1, Fraction const& f2) {
//     return simplify({
//         f1.numerator * f2.denominator - f2.numerator * f1.denominator,
//         f1.denominator * f2.denominator
//     });
// }

Fraction& Fraction::operator-=(Fraction const& f2) {
    numerator = numerator * f2.denominator - f2.numerator * denominator;
    denominator = denominator * f2.denominator;

    *this = simplify(*this);
    return *this;
}

Fraction operator-(Fraction f1, Fraction const& f2) {
    f1 -= f2; 
    return f1;
}

// Fraction operator*(Fraction const& f1, Fraction const& f2) {
//     return simplify({
//         f1.numerator * f2.numerator,
//         f1.denominator * f2.denominator
//     });
// }

Fraction& Fraction::operator*=(Fraction const& f2) {
    numerator = numerator * f2.numerator;
    denominator = denominator * f2.denominator;
    *this = simplify(*this);
    return *this;
}

Fraction operator*(Fraction f1, Fraction const& f2) {
    f1 *= f2; 
    return f1;
}

// Fraction operator/(Fraction const& f1, Fraction const& f2) {
//     return simplify({
//         f1.numerator * f2.denominator,
//         f1.denominator * f2.numerator
//     });
// }

Fraction& Fraction::operator/=(Fraction const& f2) {
    numerator = numerator * f2.denominator;
    denominator = denominator * f2.numerator;

    *this = simplify(*this);
    return *this;
}

Fraction operator/(Fraction f1, Fraction const& f2) {
    f1 /= f2; 
    return f1;
}


bool operator==(Fraction f1, Fraction f2) {
   f1 = simplify(f1);
   f2 = simplify(f2);
       
    return f1.numerator==f2.numerator && f1.denominator==f2.denominator;
}

bool operator!=(Fraction const& f1, Fraction const& f2) {
    return !(f1 == f2);
}

bool operator<(Fraction const& f1, Fraction const& f2) {
    int f1numerator, f2numerator;
    f1numerator=f1.numerator*f2.denominator;
    f2numerator=f2.numerator*f1.denominator;
    
    return f1numerator<f2numerator;
}

bool operator>(Fraction const& f1, Fraction const& f2) {

    return !(f1<f2);
}

bool operator>=(Fraction const& f1, Fraction const& f2) {
    return (f1>f2)||(f1==f2);
}

bool operator<=(Fraction const& f1, Fraction const& f2){
    return (f1<f2)||(f1==f2);
}

float Fraction::to_float() const{
    if (denominator == 0) {
        throw std::invalid_argument("Le dénominateur ne peut pas être zéro.");
    }
    return static_cast<float>(numerator) / denominator; 
}
Fraction::operator float() const {
    return to_float();  
}

// Valeur absolue d'une fraction
Fraction abs(Fraction const& f) {
    return Fraction(std::abs(static_cast<int>(f.numerator)), f.denominator);
}
// Arrondi supérieur d'une fraction
Fraction ceil(Fraction const& f) {
    float value = static_cast<float>(f.numerator) / f.denominator;
    return Fraction(std::ceil(value), 1); // On arrondit à l'entier supérieur
}

// Arrondi inférieur d'une fraction
Fraction floor(Fraction const& f) {
    float value = static_cast<float>(f.numerator) / f.denominator;
    return Fraction(std::floor(value), 1); // On arrondit à l'entier inférieur
}

// Arrondi au plus proche d'une fraction
Fraction round(Fraction const& f) {
    float value = static_cast<float>(f.numerator) / f.denominator;
    return Fraction(std::round(value), 1); // On arrondit au plus proche
}


// Les opérateurs pour les fractions et les entiers
Fraction operator+(Fraction const& f, int const i) {
    Fraction temp(i, 1);
    return f + temp;
}

Fraction operator+(int const i, Fraction const& f) {
    return f + i;
}

Fraction operator-(Fraction const& f, int const i) {
    Fraction temp(i, 1);
    return f - temp;
}

Fraction operator-(int const i, Fraction const& f) {
    Fraction temp(i, 1);
    return temp - f;
}

Fraction operator*(Fraction const& f, int const i) {
    return Fraction(f.numerator * i, f.denominator);
}

Fraction operator*(int const i, Fraction const& f) {
    return f * i;
}

Fraction operator/(Fraction const& f, int const i) {
    if (i == 0) {
        throw std::invalid_argument("Division par zéro.");
    }
    return Fraction(f.numerator, f.denominator * i);
}

Fraction operator/(int const i, Fraction const& f) {
    if (f.numerator == 0) {
        throw std::invalid_argument("Division par zéro.");
    }
    return Fraction(i * f.denominator, f.numerator);
}

