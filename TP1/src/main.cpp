#include <iostream>
#include "fraction.hpp"

int main()
{
    Fraction f1 { 3, 4 };
    Fraction f2 { 1, 2 };

    std::cout << "f1 = " << f1 << " f2 = " << f2 << std::endl;

    std::cout << "f1 + f2 = " << (f1 + f2) << std::endl;
    f1 += f2;
    std::cout << "f1 += f2 -> " << f1 << std::endl;

    std::cout << "f1 - f2 = " << (f1 - f2) << std::endl;
    f1 -= f2;
    std::cout << "f1 -= f2 -> " << f1 << std::endl;

    std::cout << "f1 * f2 = " << (f1 * f2) << std::endl;
    f1 *= f2;
    std::cout << "f1 *= f2 -> " << f1 << std::endl;

    std::cout << "f1 / f2 = " << (f1 / f2) << std::endl;
    f1 /= f2;
    std::cout << "f1 /= f2 -> " << f1 << std::endl;


    std::cout << "add(1/6, 2/6) = "<< (Fraction{1, 6} + Fraction{2, 6}) << std::endl;


    Fraction f4 { 3, 4 };
    std::cout << "f4 = " << f4 << std::endl;
    std::cout << "f1 == f4 ? " << (f1 == f4) << std::endl;
    std::cout << "f1 != f4 ? " << (f1 != f4) << std::endl;
    std::cout << "f1 < f2 ? " << (f1 < f2) << std::endl;
    std::cout << "f1 <= f2 ? " << (f1 <= f2) << std::endl;
    std::cout << "f1 > f2 ? " << (f1 > f2) << std::endl;
    std::cout << "f1 >= f2 ? " << (f1 >= f2) << std::endl;


    std::cout << "f1 en float : " << f1.to_float() << std::endl; 
    std::cout << "f2 en float : " << f2.to_float() << std::endl;

    // Test des méthodes mathématiques
    Fraction f3(-7, 3);
    std::cout << "f3 = " << f3 << std::endl;
    std::cout << "abs(f3) = " << abs(f3) << std::endl;
    std::cout << "ceil(f3) = " << ceil(f3) << std::endl;
    std::cout << "floor(f3) = " << floor(f3) << std::endl;
    std::cout << "round(f3) = " << round(f3) << std::endl;

    // Test des opérations avec des entiers
    std::cout << "f1 + 3 = " << (f1 + 3) << std::endl;
    std::cout << "3 + f1 = " << (3 + f1) << std::endl;
    std::cout << "f1 - 2 = " << (f1 - 2) << std::endl;
    std::cout << "2 - f1 = " << (2 - f1) << std::endl;
    std::cout << "f1 * 4 = " << (f1 * 4) << std::endl;
    std::cout << "4 * f1 = " << (4 * f1) << std::endl;
    std::cout << "f1 / 2 = " << (f1 / 2) << std::endl;
    std::cout << "2 / f1 = " << (2 / f1) << std::endl;

    return 0;
}