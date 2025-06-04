#include <iostream>
#include <vector>
#include <memory>
#include "src/smartNode.hpp"

int main() {  
    auto root = create_smart_node(5);
    int data[] = {3, 7, 2, 4, 6, 8, 1, 9, 0};
    
    for (int val : data) {
        root->insert(val);
    }
    
    std::cout << "is_leaf test: ";
    if (root->is_leaf()) {
        std::cout << "yes";
    } else {
        std::cout << "no";
    }
    std::cout << std::endl;
    
    std::cout << "Infix: ";
    root->display_infix();
    std::cout << std::endl;
    
    std::cout << "Min/Max: " << root->min() << "/" << root->max() << std::endl;
    std::cout << "Height: " << root->height() << std::endl;
    
//prefix/postfix
    auto pre = root->prefix();
    auto post = root->postfix();
    
    std::cout << "Prefix (" << pre.size() << "): ";
    for (auto n : pre) std::cout << n->value << " ";
    std::cout << std::endl;
    
    std::cout << "Postfix: ";
    for (auto n : post) std::cout << n->value << " ";
    std::cout << std::endl;
    

    remove(root, 2);
    std::cout << "After remove(2): ";
    root->display_infix();
    std::cout << std::endl;
    
    remove(root, 3);
    std::cout << "After remove(3): ";
    root->display_infix();
    std::cout << std::endl;
    return 0;
}