#include "node.hpp"
#include <iostream>

int main() {
    // Création de l'arbre binaire
    Node* root = create_node(10);
    
    // Insertion de valeurs
    root->insert(5);
    root->insert(15);
    root->insert(3);
    root->insert(7);
    root->insert(12);
    root->insert(18);
    root->insert(1);
    root->insert(6);
    root->insert(8);
    
    std::cout << "test de l'arbre binaire" << std::endl;
    
    //test de l'affichage infixe
    std::cout << "Parcours infixe: ";
    root->display_infix();
    std::cout << std::endl;
    
    //test de la hauteur
    std::cout << "Hauteur de l'arbre: " << root->height() << std::endl;
    
    //test des valeurs min et max (BONUS)
    std::cout << "Valeur minimale: " << root->min() << std::endl;
    std::cout << "Valeur maximale: " << root->max() << std::endl;
    
    //test du parcours préfixe
    std::cout << "Parcours préfixe: ";
    auto prefix_nodes = root->prefix();
    for (const Node* node : prefix_nodes) {
        std::cout << node->value << " ";
    }
    std::cout << std::endl;
    
    //bonus
    //test parcours postfixe
    std::cout << "Parcours postfixe: ";
    auto postfix_nodes = root->postfix();
    for (const Node* node : postfix_nodes) {
        std::cout << node->value << " ";
    }
    std::cout << std::endl;
    
    //test suppression
    std::cout << "\ntests de suppression" << std::endl;
    
    // Suppression d'une feuille
    std::cout << "Suppression de 1 (feuille): " << (remove(root, 1) ? "réussi" : "échec") << std::endl;
    std::cout << "Parcours infixe après suppression: ";
    root->display_infix();
    std::cout << std::endl;
    
    // Suppression d'un nœud avec un enfant
    std::cout << "Suppression de 7 (un enfant): " << (remove(root, 7) ? "réussi" : "échec") << std::endl;
    std::cout << "Parcours infixe après suppression: ";
    root->display_infix();
    std::cout << std::endl;
    
    // Suppression d'un nœud avec deux enfants
    std::cout << "Suppression de 5 (deux enfants): " << (remove(root, 5) ? "réussi" : "échec") << std::endl;
    std::cout << "Parcours infixe après suppression: ";
    root->display_infix();
    std::cout << std::endl;
    
    //test suppression d'une valeur inexistante
    std::cout << "Suppression de 99 (inexistant): " << (remove(root, 99) ? "réussi" : "échec") << std::endl;
    
    //test is_leaf
    std::cout << "\ntest is_leaf" << std::endl;
    std::cout << "La racine est-elle une feuille? " << (root->is_leaf() ? "oui" : "non") << std::endl;
    
    // Libération de la mémoire
    delete_tree(root);
    std::cout << "\nMémoire libérée avec succès!" << std::endl;
    
    return 0;
}
