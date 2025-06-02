#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include "ScopedTimer.hpp"

// tri fusion

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
        vec[k++] = (leftArr[i] <= rightArr[j]) ? leftArr[i++] : rightArr[j++];
    }

    while (i < n1) vec[k++] = leftArr[i++];
    while (j < n2) vec[k++] = rightArr[j++];
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
    if (!vec.empty())
        merge_sort(vec, 0, vec.size() - 1);
}

// vecteur

std::vector<int> generate_random_vector(size_t size, int max = 100000) {
    std::vector<int> vec(size);
    std::generate(vec.begin(), vec.end(), [&]() { return std::rand() % max; });
    return vec;
}

// main

int main() {
    std::vector<int> original = generate_random_vector(100000); // tableau de 100000 entiers aléatoires
    std::vector<int> vec1 = original; // pour tri fusion
    std::vector<int> vec2 = original; // pour sort

    {
        ScopedTimer timer("Temps tri fusion");
        merge_sort(vec1);
    }

    {
        ScopedTimer timer("Temps std::sort");
        std::sort(vec2.begin(), vec2.end());
    }

    return 0;
}


// Le tri de la bibliothèque standard est beaucoup plus rapide que le tri à bulles et tri fusions. 
//Il vaut donc mieux utiliser la bibliothèque standard pour trier un tableau.