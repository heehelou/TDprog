#include <vector>
#include <iostream>

void counting_sort(std::vector<int>& vec, int const max) {
    std::vector<int> count(max +1, 0);

    for (int num : vec) {
        count[num]+= 1;
    }

    size_t index = 0;
    for (int i = 0; i <= max; ++i) {
        while (count[i] > 0) {
            vec[index++] = i;
            count[i]-= 1;
        }
    }
}

int main() {
    std::vector<int> vec = {4, 2, 2, 8, 3, 3, 1};

    int max_value = *std::max_element(vec.begin(), vec.end());

    counting_sort(vec, max_value);

    std::cout << "Tableau trié : ";
    for (int num : vec) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}
