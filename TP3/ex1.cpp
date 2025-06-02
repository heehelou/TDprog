#include <iostream>
#include <vector>
#include <algorithm>

bool is_sorted(std::vector<int> const& vec) { return std::is_sorted(vec.begin(), vec.end()); }

void bubble_sort(std::vector<int> & vec){
    for (int a = vec.size(); a>0;a--){
        for (int i=1;i<a;i++){

            if (vec[i-1]>vec[i]){
                std::swap(vec[i-1], vec[i]);
            }
        }
    }

}

int main(){
    std::vector<int> array {7,3,2,6,1};
    if (is_sorted(array)) {
        std::cout << "Le tableau est trié" << std::endl;
    } else {
        std::cout << "Le tableau n'est pas trié" << std::endl;
    }

    bubble_sort(array);

        if (is_sorted(array)) {
        std::cout << "Le tableau est trié" << std::endl;
    } else {
        std::cout << "Le tableau n'est pas trié" << std::endl;
    }

    //sortie tableau
    std::cout << "Tableau trié : ";
    for (const auto& elem : array) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    return 0;
}
