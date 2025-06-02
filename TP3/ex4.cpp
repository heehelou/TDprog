#include <iostream>
#include <vector>
#include <algorithm>

int search(const std::vector<int>& vec, int value){
    int left = 0;
    int right = static_cast<int>(vec.size())- 1;

    while (left <= right){
        int middle = left +(right - left) / 2;

        if (vec[middle] == value) {
            return middle;
        } else if (vec[middle] < value) {
            left = middle + 1;
        } else {
            right = middle -1;
        }
    }

    return -1; 
}

int main() {
    std::vector<std::vector<int>> tests =
    {
        {1, 2, 2, 3, 4, 8, 12},
        {1, 2, 3, 3, 6, 14, 12, 15}, 
        {2, 2, 3, 4, 5, 8, 12, 15, 16},
        {5, 6, 7, 8, 9, 10, 11, 12, 13},
        {1, 2, 3, 4, 5, 6, 7, 8, 9}
    };

    std::vector<int> values = {8, 15, 16, 6, 10};

    for (size_t i = 0; i < tests.size(); ++i) {
        std::vector<int>& vec =tests[i];
        int val = values[i];

        
        std::sort(vec.begin(), vec.end());

        int index = search(vec, val);
        std::cout << "Recherche de " << val << " dans [";
        for (size_t j = 0; j < vec.size(); ++j){
            std::cout << vec[j] << (j < vec.size() - 1 ? ", " : "");
        }
        if(index != -1) {
            std::cout << "] valeur rechrchée " << index << "\n";
        } else{
            std::cout << "] Non trouvé\n";
        }
    }

    return 0;
}
