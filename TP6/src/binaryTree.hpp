#pragma once

#include <memory>

#include "smartNode.hpp"

struct BinaryTree {
    std::unique_ptr<SmartNode> root { nullptr };

    void insert(int value);
    bool remove(int value);
    void clear();
    bool contains(int value) const;
    size_t height() const;
    void display_infix() const;
    std::vector<SmartNode const*> prefix() const;
    std::vector<SmartNode const*> postfix() const;
    int min() const;
    int max() const;
    bool empty() const;
    size_t size() const;
};

bool contains(std::unique_ptr<SmartNode>& node, int value);
size_t count_nodes(const std::unique_ptr<SmartNode>& node);
