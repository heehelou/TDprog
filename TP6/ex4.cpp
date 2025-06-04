#include <iostream>
#include <vector>
#include <stdexcept>
#include "src/binaryTree.hpp"

int main() {
    BinaryTree tree;
    
    // Test avec un arbre vide d'abord
    std::cout << "Arbre vide - Taille: " << tree.size() 
              << ", Hauteur: " << tree.height() 
              << ", Vide? " << tree.empty() << std::endl;
    
    // Je teste ce qui se passe si j'essaie de trouver le min sur un arbre vide
    try {
        int minimum = tree.min();
        std::cout << "Min trouvé: " << minimum << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Erreur min sur arbre vide: " << e.what() << std::endl;
    }
    
    //ajoute de valeurs
    std::vector<int> donnees = {1, 3, 7, 4, 2, 6, 8, 5, 9, 0};
    std::cout << "J'insère les valeurs: ";
    for (int valeur : donnees) {
        std::cout << valeur << " ";
        tree.insert(valeur);
    }
    std::cout << std::endl;
    
    // Je vérifie l'état après insertion
    std::cout << "Après insertions:" << std::endl;
    std::cout << "  - Taille: " << tree.size() << " éléments" << std::endl;
    std::cout << "  - Hauteur: " << tree.height() << " niveaux" << std::endl;
    
    std::cout << "Affichage infixe: ";
    tree.display_infix();
    std::cout << std::endl;
    
    // Tests de recherche
    int a_chercher = 5, pas_la = 99;
    std::cout << "Recherches:" << std::endl;
    std::cout << "  - " << a_chercher << " présent? " << (tree.contains(a_chercher) ? "oui" : "non") << std::endl;
    std::cout << "  - " << pas_la << " présent? " << (tree.contains(pas_la) ? "oui" : "non") << std::endl;
    
    // Min et max
    std::cout << "Valeurs extrêmes: min=" << tree.min() << ", max=" << tree.max() << std::endl;
    
    // Test du parcours préfixe
    auto parcours_prefixe = tree.prefix();
    std::cout << "Parcours préfixe (" << parcours_prefixe.size() << " noeuds): ";
    for (const auto* noeud : parcours_prefixe) {
        std::cout << noeud->value << " ";
    }
    std::cout << std::endl;
    
    // Tests de suppression
    int a_supprimer1 = 2;
    std::cout << "Je supprime " << a_supprimer1 << "..." << std::endl;
    if (tree.remove(a_supprimer1)) {
        std::cout << "Suppression réussie. Nouvel arbre: ";
        tree.display_infix();
        std::cout << " (taille=" << tree.size() << ")" << std::endl;
    }
    
    int a_supprimer2 = 5; // La racine cette fois
    std::cout << "Je supprime la racine (" << a_supprimer2 << ")..." << std::endl;
    if (tree.remove(a_supprimer2)) {
        std::cout << "Racine supprimée. Arbre final: ";
        tree.display_infix();
        std::cout << std::endl;
    }
    
    // Nettoyage complet
    std::cout << "Je nettoie tout l'arbre..." << std::endl;
    tree.clear();
    std::cout << "Après clear() - Arbre vide? " << (tree.empty() ? "oui" : "non") << std::endl;
    
    return 0;
}
