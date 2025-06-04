#include <iostream>
#include <vector>
#include <numeric>
#include "src/node.hpp"

int main() {
    Node* root = nullptr;
    std::vector<int> vals = {5, 3, 7, 2, 4, 6, 8, 1, 9, 0};
    
    std::cout << "insertion des valeurs: ";
    for (int v : vals) {
        std::cout << v << " ";
        if (root == nullptr) {
            root = create_node(v);
        } else {
            root->insert(v);
        }
    }
    std::cout << std::endl;
    
    
//parcours infix (ordre croissant)
    std::cout << "\nparcours infix: ";
    root->display_infix();
    std::cout << std::endl;
    
//min et max
    std::cout << "min: " << root->min() << ", max: " << root->max() << std::endl;
    
//calcul somme avec parcours prefix
    std::vector<Node const*> prefix_vals = root->prefix();
    std::cout << "prefix: ";
    for (auto node : prefix_vals) {
        std::cout << node->value << " ";
    }
    
    int somme = 0;
    for (auto node : prefix_vals) {
        somme += node->value;
    }
    std::cout << "\nsomme: " << somme << std::endl;
    
    std::cout << "hauteur: " << root->height() << std::endl;
    
    delete_tree(root);
    return 0;
}