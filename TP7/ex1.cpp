#include <iostream>
#include <vector>
#include <unordered_map>
#include <utility>

namespace Graph {
    struct WeightedGraphEdge {
        int to {};
        float weight {1.0f};

        // default ici permet de définir les opérateurs de comparaison membres à membres automatiquement
        // Cela ne fonctionne qu'en C++20
        bool operator==(WeightedGraphEdge const& other) const = default;
        bool operator!=(WeightedGraphEdge const& other) const = default;
    };

    struct WeightedGraph {
        // L'utilisation d'un tableau associatif permet d'avoir une complexité en O(1) pour l'ajout et la recherche d'un sommet.
        // Cela permet de stocker les sommets dans un ordre quelconque (et pas avoir la contrainte d'avoir des identifiants (entiers) de sommets consécutifs lors de l'ajout de sommets).
        // Cela permet également de pouvoir utiliser des identifiants de sommets de n'importe quel type (string, char, int, ...) et pas seulement des entiers.
        std::unordered_map<int, std::vector<WeightedGraphEdge>> adjacency_list {};

        void add_vertex(int const id);
        void add_directed_edge(int const from, int const to, float const weight = 1.0f);
        void add_undirected_edge(int const from, int const to, float const weight = 1.0f);
        
        // Même fonctionnement que pour WeightedGraphEdge
        bool operator==(WeightedGraph const& other) const = default;
        bool operator!=(WeightedGraph const& other) const = default;

        void print_DFS(int const start) const;
        void print_BFS(int const start) const;
    };

    WeightedGraph build_from_adjacency_matrix(std::vector<std::vector<float>> const& adjacency_matrix);
} // namespace

// implementation de add_vertex
void Graph::WeightedGraph::add_vertex(int const id) {
    //teste si le sommet existe déjà avec find
    if (adjacency_list.find(id) == adjacency_list.end()) {
        // si le sommet n'existe pas, on l'ajoute avec une liste vide
        adjacency_list[id] = std::vector<WeightedGraphEdge>();
    }
}


void Graph::WeightedGraph::add_directed_edge(int const from, int const to, float const weight) {
    // on s'assure que les sommets existent
    add_vertex(from);
    add_vertex(to);
    
    // ajouter l'arete
    adjacency_list[from].push_back({to, weight});
}

// pour les aretes non orientees
void Graph::WeightedGraph::add_undirected_edge(int const from, int const to, float const weight) {
    // on fait 2 aretes directionnelles
    add_directed_edge(from, to, weight);
    add_directed_edge(to, from, weight);
}

// construire graphe depuis matrice
Graph::WeightedGraph Graph::build_from_adjacency_matrix(std::vector<std::vector<float>> const& adjacency_matrix) {
    WeightedGraph graph;
    
    // check si matrice vide
    if (adjacency_matrix.empty()) {
        return graph;
    }
    
    size_t n = adjacency_matrix.size();
    
    // parcourir matrice
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < adjacency_matrix[i].size(); j++) {
            if (adjacency_matrix[i][j] != 0.0f) {
                graph.add_directed_edge(static_cast<int>(i), static_cast<int>(j), adjacency_matrix[i][j]);
            }
        }
    }
    
    return graph;
}

int main() {
    using namespace Graph;
    
    // matrice d'adjacence pour tester
    std::vector<std::vector<float>> matrice = {
        {0.0f, 2.5f, 1.0f, 0.0f},
        {2.5f, 0.0f, 0.0f, 3.0f},
        {1.0f, 0.0f, 0.0f, 1.5f},
        {0.0f, 3.0f, 1.5f, 0.0f}
    };
    
    std::cout << "Matrice d'adjacence utilisée :" << std::endl;
    for (size_t i = 0; i < matrice.size(); i++) {
        for (size_t j = 0; j < matrice[i].size(); j++) {
            std::cout << matrice[i][j] << "  ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    
    // Test 1: creation depuis la matrice d'adjacence
    WeightedGraph graphe1 = build_from_adjacency_matrix(matrice);
    
    std::cout << "   Nombre de sommets : " << graphe1.adjacency_list.size() << std::endl;
    std::cout << "   Arêtes du graphe 1 :" << std::endl;
    for (const auto& [sommet, aretes] : graphe1.adjacency_list) {
        for (const auto& arete : aretes) {
            std::cout << "     " << sommet << " --> " << arete.to 
                      << " (poids=" << arete.weight << ")" << std::endl;
        }
    }
    std::cout << std::endl;
    
    // Test 2: Création manuelle
    WeightedGraph graphe2;
    
    // Ajout des sommets
    std::cout << "   Ajout des sommets 0, 1, 2, 3..." << std::endl;
    for (int i = 0; i < 4; i++) {
        graphe2.add_vertex(i);
    }
    
    // Ajout des arêtes non-orientées selon la matrice
    std::cout << "   Ajout des arêtes non-orientées..." << std::endl;
    graphe2.add_undirected_edge(0, 1, 2.5f);  // matrice[0][1] = 2.5
    graphe2.add_undirected_edge(0, 2, 1.0f);  // matrice[0][2] = 1.0
    graphe2.add_undirected_edge(1, 3, 3.0f);  // matrice[1][3] = 3.0
    graphe2.add_undirected_edge(2, 3, 1.5f);  // matrice[2][3] = 1.5
    
    std::cout << " Nombre de sommets : " << graphe2.adjacency_list.size() << std::endl;
    std::cout << " Arêtes du graphe 2 :" << std::endl;
    for (const auto& [sommet, aretes] : graphe2.adjacency_list) {
        for (const auto& arete : aretes) {
            std::cout << "     " << sommet << " --> " << arete.to 
                      << " (poids=" << arete.weight << ")" << std::endl;
        }
    }
    std::cout << std::endl;
    
    // Test 3: Comparaison des deux graphes
    if (graphe1 == graphe2) {
        std::cout << "les deux graphes sont identiques !" << std::endl;
    } else {
        std::cout << "les graphes sont différents." << std::endl;
    }
    
    return 0;
}

