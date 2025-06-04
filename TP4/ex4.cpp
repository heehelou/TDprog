#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

//somme du carré des éléments
int somme_carres(std::vector<int> const& v) {
    return std::accumulate(v.begin(), v.end(), 0, [](int acc, int element) {
        return acc + element * element;
    });
}

//produit des éléments pairs
int produit_pairs(std::vector<int> const& v) {
    return std::accumulate(v.begin(), v.end(), 1, [](int acc, int element) {
        if (element % 2 == 0) {
            return acc * element;
        }
        return acc;
    });
}

int main() {
    std::vector<int> v{2,4, 3,5,7,9};
    
    std::cout << "vecteur : ";
    for (int element : v) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
    
    std::cout << "somme des carrés : " << somme_carres(v) << std::endl;
    std::cout << "produit des pairs : " << produit_pairs(v) << std::endl;
    
    return 0;
}