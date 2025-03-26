#pragma once

#include <iostream>

struct Fraction {
     int numerator;
     int denominator;

    void display();

    Fraction& operator+=(Fraction const& f2);
    Fraction& operator-=(Fraction const& f2);
    Fraction& operator*=(Fraction const& f2);
    Fraction& operator/=(Fraction const& f2);

    float to_float() const;
    operator float() const;

    // Méthodes

    Fraction(int num, int den) : numerator(num), denominator(den) {
        if (denominator == 0) {
            throw std::invalid_argument("Le dénominateur ne peut pas être zéro.");
        }
    }
};

Fraction operator+(Fraction f1, Fraction const& f2);
Fraction operator-(Fraction f1, Fraction const& f2);
Fraction operator*(Fraction f1, Fraction const& f2);
Fraction operator/(Fraction f1, Fraction const& f2);

std::ostream& operator<<(std::ostream& os, Fraction const& p);

bool operator==(Fraction f1, Fraction f2);
bool operator!=(Fraction const& f1, Fraction const& f2);

bool operator<(Fraction const& f1, Fraction const& f2);
bool operator<=(Fraction const& f1, Fraction const& f2);
bool operator>(Fraction const& f1, Fraction const& f2);
bool operator>=(Fraction const& f1, Fraction const& f2);


// opérations avec des entiers
Fraction operator+(Fraction const& f, int const i);
Fraction operator+(int const i, Fraction const& f);

Fraction operator-(Fraction const& f, int const i);
Fraction operator-(int const i, Fraction const& f);

Fraction operator*(Fraction const& f, int const i);
Fraction operator*(int const i, Fraction const& f);

Fraction operator/(Fraction const& f, int const i);
Fraction operator/(int const i, Fraction const& f);

Fraction abs(Fraction const& f);
Fraction ceil(Fraction const& f);
Fraction floor(Fraction const& f);
Fraction round(Fraction const& f);