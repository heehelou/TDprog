#include "binaryTree.hpp"
#include <iostream>


void BinaryTree::insert(int value) {
    if (!root) {
        root = create_smart_node(value);
    } else {
        root->insert(value);
    }
}

bool BinaryTree::remove(int value) {
    if (!root) {
        return false;
    }
    return ::remove(root, value);
}

void BinaryTree::clear() {
    root.reset(); 
}

bool BinaryTree::contains(int value) const {
    if (!root) {
        return false; 
    }
    return ::contains(const_cast<std::unique_ptr<SmartNode>&>(root), value);
}

size_t BinaryTree::height() const {
    if (!root) {
        return 0; 
    }
    return root->height();
}

void BinaryTree::display_infix() const {
    if (!root) {
        std::cout << "(arbre vide)";
        return;
    }
    root->display_infix();
}

std::vector<SmartNode const*> BinaryTree::prefix() const {
    if (!root) {
        return {}; 
    }
    return root->prefix();
}

std::vector<SmartNode const*> BinaryTree::postfix() const {
    if (!root) {
        return {};
    }
    return root->postfix();
}

int BinaryTree::min() const {
    if (!root) {
        throw std::runtime_error("Cannot find minimum in empty tree");
    }
    return root->min();
}

int BinaryTree::max() const {
    if (!root) {
        throw std::runtime_error("Cannot find maximum in empty tree");
    }
    return root->max();
}

bool BinaryTree::empty() const {
    return !root; 
}

size_t BinaryTree::size() const {
    return count_nodes(root);
}



bool contains(std::unique_ptr<SmartNode>& node, int value) {
    if (!node) {
        return false;
    }
    
    if (value == node->value) {
        return true;
    } else if (value < node->value) {
        return contains(node->left, value);
    } else {
        return contains(node->right, value);
    }
}

size_t count_nodes(const std::unique_ptr<SmartNode>& node) {
    if (!node) {
        return 0;
    }
    return 1 + count_nodes(node->left) + count_nodes(node->right);
}
