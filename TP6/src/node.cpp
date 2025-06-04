#include "node.hpp"
#include <iostream>
#include <algorithm>

//Créer un nouveau nœud
Node* create_node(int value) {
    return new Node{value, nullptr, nullptr};
}

// vérifier si un nœud est une feuille
bool Node::is_leaf() const {
    return left == nullptr && right == nullptr;
}

//insérer une valeur dans l'arbre binaire
void Node::insert(int value) {
    if (value < this->value) {
        if (left == nullptr) {
            left = create_node(value);
        } else {
            left->insert(value);
        }
    } else {
        if (right == nullptr) {
            right = create_node(value);
        } else {
            right->insert(value);
        }
    }
}

//calculer la hauteur de l'arbre
int Node::height() const {
    if (is_leaf()) {
        return 1;
    }
    
    int left_height = 0;
    int right_height = 0;
    
    if (left != nullptr) {
        left_height = left->height();
    }
    
    if (right != nullptr) {
        right_height = right->height();
    }
    
    return 1 + std::max(left_height, right_height);
}

//supprimer les enfants d'un nœud
void Node::delete_children() {
    if (left != nullptr) {
        left->delete_children();
        delete left;
        left = nullptr;
    }
    
    if (right != nullptr) {
        right->delete_children();
        delete right;
        right = nullptr;
    }
}

// afficher l'arbre en ordre infixe
void Node::display_infix() const {
    if (left != nullptr) {
        left->display_infix();
    }
    
    std::cout << value << " ";
    
    if (right != nullptr) {
        right->display_infix();
    }
}

// parcourir l'arbre en ordre préfixe
std::vector<Node const*> Node::prefix() const {
    std::vector<Node const*> nodes;
    
    // Ajouter le nœud courant
    nodes.push_back(this);
    
    // Ajouter les nœuds du sous-arbre gauche
    if (left != nullptr) {
        auto left_nodes = left->prefix();
        nodes.insert(nodes.end(), left_nodes.begin(), left_nodes.end());
    }
    
    // Ajouter les nœuds du sous-arbre droit
    if (right != nullptr) {
        auto right_nodes = right->prefix();
        nodes.insert(nodes.end(), right_nodes.begin(), right_nodes.end());
    }
    
    return nodes;
}

// bonus 
//parcourir l'arbre en ordre postfixe
std::vector<Node const*> Node::postfix() const {
    std::vector<Node const*> nodes;
    
// Ajouter les nœuds du sous-arbre gauche
    if (left != nullptr) {
        auto left_nodes = left->postfix();
        nodes.insert(nodes.end(), left_nodes.begin(), left_nodes.end());
    }
    
// Ajouter les nœuds du sous-arbre droit
    if (right != nullptr) {
        auto right_nodes = right->postfix();
        nodes.insert(nodes.end(), right_nodes.begin(), right_nodes.end());
    }
    
// Ajouter le nœud courant
    nodes.push_back(this);
    
    return nodes;
}

// bonus fonction pour trouver le nœud le plus à gauche
Node*& most_left(Node*& node) {
    if (node->left == nullptr) {
        return node;
    }
    return most_left(node->left);
}

// fonction pour supprimer une valeur de l'arbre
bool remove(Node*& node, int value) {
    if (node == nullptr) {
        return false;
    }
    
    if (value < node->value) {
        return remove(node->left, value);
    } else if (value > node->value) {
        return remove(node->right, value);
    } else {
        // Nœud trouvé
        if (node->is_leaf()) {
            // Cas 1: Le nœud n'a pas de fils
            delete node;
            node = nullptr;
            return true;
        } else if (node->left == nullptr) {
            // Cas 2.1: Le nœud n'a qu'un fils droit
            Node* temp = node;
            node = node->right;
            delete temp;
            return true;
        } else if (node->right == nullptr) {
            // Cas 2.2: Le nœud n'a qu'un fils gauche
            Node* temp = node;
            node = node->left;
            delete temp;
            return true;
        } else {
            // Cas 3: Le nœud a deux fils
            Node*& successor = most_left(node->right);
            node->value = successor->value;
            return remove(successor, successor->value);
        }
    }
}

//supprimer tout l'arbre
void delete_tree(Node* node) {
    if (node != nullptr) {
        delete_tree(node->left);
        delete_tree(node->right);
        delete node;
    }
}

// bonus trouver la valeur minimale
int Node::min() const {
    if (left == nullptr) {
        return value;
    }
    return left->min();
}

// bonus trouver la valeur maximale
int Node::max() const {
    if (right == nullptr) {
        return value;
    }
    return right->max();
}
