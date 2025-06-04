#include "smartNode.hpp"
#include <iostream>
#include <algorithm>


bool SmartNode::is_leaf() const {
    // Je vérifie si c'est une feuille en regardant si y'a pas d'enfants
    return !left && !right;
}

void SmartNode::insert(int val) {
    if (val < value) {
        if (!left) {
            // Pas d'enfant gauche, j'en crée un nouveau
            left = std::make_unique<SmartNode>();
            left->value = val;
        } else {
            // Y'a déjà un enfant gauche, je continue récursivement
            left->insert(val);
        }
    } else if (val > value) {
        if (!right) {
            // Pareil mais à droite
            right = std::make_unique<SmartNode>();
            right->value = val;
        } else {
            right->insert(val);
        }
    }
    // Si val == value, je fais rien (pas de doublons)
}

size_t SmartNode::height() const {
    size_t left_height = 0;
    size_t right_height = 0;
    
    if (left) {
        // Je calcule la hauteur du sous-arbre gauche
        left_height = left->height();
    }
    if (right) {
        // Et celle du sous-arbre droit
        right_height = right->height();
    }
    
    // La hauteur= 1+ la plus grande hauteur des deux sous-arbres
    return 1 + std::max(left_height, right_height);
}

void SmartNode::display_infix() const {
    if (left) {
        // sous-arbre gauche
        left->display_infix();
    }
    //(parcours infix=gauche-racine-droite)
    std::cout << value << " ";
    if (right) {
        //sous-arbre droit
        right->display_infix();
    }
}

std::vector<SmartNode const*> SmartNode::prefix() const {
    std::vector<SmartNode const*> result;
    result.push_back(this);
    
    if (left) {
        auto left_prefix = left->prefix();
        result.insert(result.end(), left_prefix.begin(), left_prefix.end());
    }
    
    if (right) {
        auto right_prefix = right->prefix();
        result.insert(result.end(), right_prefix.begin(), right_prefix.end());
    }
    
    return result;
}

std::vector<SmartNode const*> SmartNode::postfix() const {
    std::vector<SmartNode const*> result;
    
    if (left) {
        auto left_postfix = left->postfix();
        result.insert(result.end(), left_postfix.begin(), left_postfix.end());
    }
    
    if (right) {
        auto right_postfix = right->postfix();
        result.insert(result.end(), right_postfix.begin(), right_postfix.end());
    }
    
    result.push_back(this);
    return result;
}

int SmartNode::min() const {
    if (!left) {
        return value;
    }
    return left->min();
}

int SmartNode::max() const {
    if (!right) {
        return value;
    }
    return right->max();
}

std::unique_ptr<SmartNode> create_smart_node(int value) {
    auto node = std::make_unique<SmartNode>();
    node->value = value;
    return node;
}

std::unique_ptr<SmartNode>& most_left(std::unique_ptr<SmartNode>& node) {
    if (!node || !node->left) {
        return node;
    }
    return most_left(node->left);
}

bool remove(std::unique_ptr<SmartNode>& node, int value) {
    if (!node) {
        return false;
    }
    
    if (value < node->value) {
        return remove(node->left, value);
    } else if (value > node->value) {
        return remove(node->right, value);
    } else {
        if (node->is_leaf()) {
            // Case 1: pas de fils
            node.reset();
        } else if (!node->left) {
            // Cas 2.1: qu'un fils droit
            node = std::move(node->right); // Je remplace par l'enfant droit
        } else if (!node->right) {
            // Case 2.2: qu'un fils gauche
            node = std::move(node->left); // je remplace par l'enfant gauche
        } else {
            // Case 3: 2 fils
            // Je trouve le successeur (plus petit élément du sous-arbre droit)
            std::unique_ptr<SmartNode>& successor = most_left(node->right);
            
            // Je remplace la valeur par celle du successeur
            node->value = successor->value;
            
            // Et je supprime le successeur (qui a au max 1 enfant)
            remove(node->right, successor->value);
        }
        return true;
    }
}
