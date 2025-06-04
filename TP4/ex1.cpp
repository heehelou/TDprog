#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

int main(){
    
    std::vector<int>v{78,45,3,26,80,33,12,2,33};
    std::vector<int>::iterator end_iterator { v.end() };

    for (std::vector<int>::iterator it { v.begin() }; it != end_iterator; ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    int nombre{};
    std::cout << "Choisir un nombre à chercher : ";
    std::cin>>nombre;
    auto it { std::find(v.begin(), v.end(), nombre) };

    if (it != v.end())
    {
        std::cout << "Le nombre "<< nombre << " est présent." << std::endl;
    }
    else
    {
        std::cout << "Le nombre" << nombre << "n'est pas présent." << std::endl;
    }

    int mycount = std::count (v.begin(), v.end(), nombre);
    std::cout <<"Le nombre "<<nombre << " apparait " << mycount  << " fois.\n";

    std::sort(v.begin(), v.end());
    std::cout << "Les éléments sont maintenant rangés dans l'ordre :" << std::endl;

    for (int element : v)
    {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    //somme des éléments
    int sum { std::accumulate(v.begin(), v.end(), 0, [](int acc, int current_element) { return acc + current_element; }) };
    std::cout << "La somme des éléments est :" << std::endl;
    std::cout << sum << std::endl;

    return 0;
}
