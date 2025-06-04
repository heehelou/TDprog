#include <iostream>
#include <vector>
#include <string>

size_t folding_string_hash(std::string const& s, size_t max){
    size_t somme = 0;
    for (char c : s){
        somme += static_cast<size_t>(c);
    }
    return somme % max;
}

size_t folding_string_ordered_hash(std::string const& s, size_t max){
    size_t somme = 0;
    for (size_t i =0;i<s.length();++i){
        somme += static_cast<size_t>(s[i])*(i + 1);
    }

    return somme % max;
}

size_t polynomial_rolling_hash(const std::string& s, size_t p, size_t m){
    size_t hash_value = 0;
    size_t puiss = 1;
    for (char c : s){
        hash_value = (hash_value + (static_cast<size_t>(c) * puiss) % m) % m;
        puiss = (puiss * p) % m;
    }
    return hash_value;
}

int main() {
    std::string mot = "watibg";
    size_t maximum = 1024;
    size_t hash = folding_string_hash(mot, maximum);
    std::cout << "hachage de " << mot << " est " << hash << std::endl;
  
    size_t ordered_hash = folding_string_ordered_hash(mot, maximum);
    std::cout << "nouveau hachage de " << mot << " est " << ordered_hash << std::endl;

    size_t p = 31;
    size_t m = 1000000009;
    size_t poly_hash = polynomial_rolling_hash(mot, p, m);
    std::cout << "nouveau nouveau hashage de " << mot << " est " << poly_hash << std::endl;
    
}

