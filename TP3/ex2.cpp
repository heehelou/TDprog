#include <iostream>
#include <vector>
#include <algorithm>

bool is_sorted(std::vector<int> const& vec) { 
    return std::is_sorted(vec.begin(), vec.end()); 
}

void merge_sort_merge(std::vector<int>& vec, size_t left, size_t middle, size_t right) {
    size_t n1 = middle - left + 1;
    size_t n2 = right - middle;

    std::vector<int> leftArr(n1);
    std::vector<int> rightArr(n2);

    for (size_t i = 0; i < n1; i++)
        leftArr[i] = vec[left + i];
    for (size_t j = 0; j < n2; j++)
        rightArr[j] = vec[middle + 1 + j];

    size_t i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            vec[k] = leftArr[i];
            i++;
        } else {
            vec[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        vec[k] = leftArr[i];
        i++;
        k++;
    }

    while (j < n2) {
        vec[k] = rightArr[j];
        j++;
        k++;
    }
}

void merge_sort(std::vector<int>& vec, size_t left, size_t right) {
    if (left < right) {
        size_t middle = left + (right - left) / 2;
        merge_sort(vec, left, middle);
        merge_sort(vec, middle + 1, right);
        merge_sort_merge(vec, left, middle, right);
    }
}

void merge_sort(std::vector<int>& vec) {
    if (!vec.empty()) {
        merge_sort(vec, 0, vec.size() - 1);
    }
}

int main() {
    std::vector<int> array {7, 3, 2, 6, 1, 8};
    if (is_sorted(array)) {
        std::cout << "Le tableau est trié" << std::endl;
    } else {
        std::cout << "Le tableau n'est pas trié" << std::endl;
    }

    merge_sort(array);

    if (is_sorted(array)) {
        std::cout << "Le tableau est trié" << std::endl;
    } else {
        std::cout << "Le tableau n'est pas trié" << std::endl;
    }

    // la sortie du tableau
    std::cout << "Tableau trié : ";
    for (const auto& elem : array) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    return 0;
}
