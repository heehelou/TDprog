#include <iostream>
#include <vector>
#include <numeric>

bool palindrome(std::string const& str){

// Je compare la premiere et dernier letter puis la deuxieme et l'avant derniere et ainsi de suite
// jusqu'à que : soit je trouve une lettre qui ne correspond pas soit je trouve que j'ai fait le tour de la chain
//
    return std::equal(std::begin(str), std::begin(str) + str.size()/2, std::rbegin(str));
}

int main(){
    std::string test1 = "test";
    std::string test2 = "kayak";
    
    std::cout  << test1 << " n'est pas un palindrome : " << palindrome(test1) << std::endl;
    std::cout  << test2 << " est un palindrome : " << palindrome(test2) << std::endl;
    
    return 0;
}
