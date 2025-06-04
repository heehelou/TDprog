#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

auto const is_space = [](char letter){ return letter == ' '; };

int fonction(const std::string& str){

// trouver le premier caractère qui n'est pas un espace
auto start = std::find_if_not(str.begin(), str.end(), is_space);

// trouve la fin du premier mot (premier espace après le début du mot)
auto end = std::find_if(start, str.end(), is_space);


return std::distance(start, end);
}

std::vector<std::string> split_string(std::string const& str){

// je trouve le debut et fin du premier mot et je les prends et les mets dans un tableau et ensuite je prends le mot suivant

std::vector<std::string> words;
    auto begin = str.begin();

    while (begin != str.end()) {
        // Trouver le début du mot (ignorer les espaces)
        begin = std::find_if_not(begin, str.end(), is_space);
        if (begin == str.end()) break;  // Si on atteint la fin, on arrête
        
        // Trouver la fin du mot
        auto end = std::find_if(begin, str.end(), is_space);
        
        std::string word1{};
        // Ajouter le mot trouvé dans le vector
        for(auto begin2=begin;begin2<end;begin2++){
            word1+=*begin2;
        }
        words.push_back(word1);

        // Continuer après le mot
        begin = end;
    }

    return words;
}



int main(){
    std::string phrase = " Ca pique ses chocapics";
    std::cout << "Longueur du premier mot : " << fonction(phrase) << std::endl;
   
    std::vector<std::string> resultat= split_string(phrase);

    for (std::string const element : resultat) {
        std::cout << element << std::endl;
    }
    
    
   return 0;
}