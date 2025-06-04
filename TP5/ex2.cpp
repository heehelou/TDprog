#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <numeric>
#include <functional>
#include <random>
#include <iterator>
#include <algorithm>
#include <iomanip>

enum class Insect {
    ClassicBee,
    Ladybug,
    Butterfly,
    Dragonfly,
    Ant,
    Grasshopper,
    Beetle,
    Wasp,
    Caterpillar,
    Spider,
    GuimielBee
};

std::vector<Insect> const insect_values {
    Insect::ClassicBee,
    Insect::Ladybug,
    Insect::Butterfly,
    Insect::Dragonfly,
    Insect::Ant,
    Insect::Grasshopper,
    Insect::Beetle,
    Insect::Wasp,
    Insect::Caterpillar,
    Insect::Spider,
    Insect::GuimielBee
};

std::unordered_map<Insect, std::string> const insect_to_string = {
    {Insect::ClassicBee, "ClassicBee"},
    {Insect::Ladybug, "Ladybug"},
    {Insect::Butterfly, "Butterfly"},
    {Insect::Dragonfly, "Dragonfly"},
    {Insect::Ant, "Ant"},
    {Insect::Grasshopper, "Grasshopper"},
    {Insect::Beetle, "Beetle"},
    {Insect::Wasp, "Wasp"},
    {Insect::Caterpillar, "Caterpillar"},
    {Insect::Spider, "Spider"},
    {Insect::GuimielBee, "GuimielBee"}
};

std::vector<int> const expected_insect_counts {
    75, // ClassicBee
    50, // Ladybug
    100, // Butterfly
    20, // Dragonfly
    400, // Ant
    150, // Grasshopper
    60, // Beetle
    10, // Wasp
    40, // Caterpillar
    90, // Spider 
    5, // GuimielBee
};

// prend en paramètre un vecteur de comptages et retourne un vecteur de probabilités à partir de ces comptages
std::vector<float> probabilities_from_count(std::vector<int> const& counts) {
    int total = std::accumulate(counts.begin(), counts.end(), 0);
    std::vector<float> probabilities;
    probabilities.reserve(counts.size());

    for (int count : counts) {
        probabilities.push_back(static_cast<float>(count) / total);
    }
    return probabilities;
}

// génère une liste d'observations aléatoires 
std::vector<std::pair<Insect, int>> get_insect_observations(
    size_t const number_of_observations,
    std::vector<float> const& insect_probabilities,
    unsigned int const seed = std::random_device{}()
) {
    // Create a random engine with a given seed
    std::default_random_engine random_engine{seed};

    auto rand_insect_index { std::bind(std::discrete_distribution<size_t>{insect_probabilities.begin(), insect_probabilities.end()}, random_engine) };
    
    std::vector<std::pair<Insect, int>> observations {};
    observations.reserve(number_of_observations);

    for(size_t i {0}; i < number_of_observations; ++i) {
        size_t const random_insect_index { rand_insect_index() };
        Insect const random_insect { insect_values[random_insect_index] };
        
        // If we have already seen the same insect, increment the count on the last observation
        if(!observations.empty() && observations.back().first == random_insect) {
            observations.back().second++;
            i -= 1;
        } else {
            observations.push_back({random_insect, 1});
        }
    }

    return observations;
}

//main
int main() {
    std::cout << std::fixed << std::setprecision(3);

    size_t number_of_observations = 10000;
    auto expected_probabilities = probabilities_from_count(expected_insect_counts);
    auto observations = get_insect_observations(number_of_observations, expected_probabilities, 42); 

    //comptage 
    std::unordered_map<Insect, int> insect_counts;
    for (auto const& [insect, count] : observations) {
        insect_counts[insect] += count;
    }

    //Transformer le unordered_map en vecteur dans l’ordre de insect_values
    std::vector<int> observed_counts;
    for (auto const& insect : insect_values) {
        observed_counts.push_back(insect_counts[insect]);
    }

    auto observed_probabilities = probabilities_from_count(observed_counts);

    //comparaison et affichage des résultats
    std::cout << "Probabilities of observed insects vs expected probabilities\n";
    for (size_t i = 0; i < insect_values.size(); ++i) {
        Insect insect = insect_values[i];
        float observed = observed_probabilities[i];
        float expected = expected_probabilities[i];
        
        std::string status;
        if (std::abs(observed - expected) < 0.01f) {
            status = "OK";
        } else {
            status = "BAD";
        }

        std::cout << insect_to_string.at(insect) << " : "
                  << observed << " vs " << expected << " " << status << '\n';
    }

    return 0;
}
