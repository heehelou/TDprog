#include <iostream>
#include <unordered_map>
#include <string>
#include <queue>
#include <vector>

struct Node {
    char character;
    size_t frequency;
    Node* left { nullptr };
    Node* right { nullptr };
    
    bool operator<(const Node& other) const {
        return frequency > other.frequency;
    }
};

// calculer les fréquences
std::unordered_map<char, size_t> frequency(const std::string& s) {
    std::unordered_map<char, size_t> freq_map;
    for (char c : s) {
        freq_map[c]++;
    }
    return freq_map;
}

// créer un nœud
Node* createNode(char character, size_t frequency) {
    Node* node = new Node;
    node->character = character;
    node->frequency = frequency;
    return node;
}

Node* createSymbolNode(Node* left, Node* right) {
    Node* node = new Node;
    node->character = 0;
    node->frequency = left->frequency + right->frequency;
    node->left = left;
    node->right = right;
    return node;
}

// construire l'arbre de huffman
Node* build_huffman_tree(const std::unordered_map<char, size_t>& freq_map) {
    std::priority_queue<Node*, std::vector<Node*>, std::function<bool(Node*, Node*)>> pq(
        [](Node* a, Node* b) { return *a < *b; }
    );
    
    // ajouter tous les caractères
    for (const auto& pair : freq_map) {
        pq.push(createNode(pair.first, pair.second));
    }
    
    // construire l'arbre
    while (pq.size() > 1) {
        Node* right = pq.top(); pq.pop();
        Node* left = pq.top(); pq.pop();
        
        Node* merged = createSymbolNode(left, right);
        pq.push(merged);
    }
    
    return pq.empty() ? nullptr : pq.top();
}

void fill_encoding_table(Node const* node, std::unordered_map<char, std::string>& table, std::string str) {
    if (!node) return;
    
    if (!node->left && !node->right) {
        table[node->character] = str.empty() ? "0" : str;
        return;
    }
    
    fill_encoding_table(node->left, table, str + "0");
    fill_encoding_table(node->right, table, str + "1");
}

// construire la table d'encodage
std::unordered_map<char, std::string> build_encoding_table(Node const* root) {
    std::unordered_map<char, std::string> table;
    fill_encoding_table(root, table, "");
    return table;
}

// encoder
std::string encode(std::string str, std::unordered_map<char, std::string> const& table) {
    std::string result;
    for (char c : str) {
        auto it = table.find(c);
        if (it != table.end()) {
            result += it->second;
        }
    }
    return result;
}

// décoder
std::string decode(std::string const& str, Node const* huffman_tree_root) {
    if (!huffman_tree_root) return "";
    
    std::string result;
    Node const* current = huffman_tree_root;
    
    for (char bit : str) {
        if (bit == '0') {
            current = current->left;
        } else if (bit == '1') {
            current = current->right;
        }

        if (!current->left && !current->right) {
            result += current->character;
            current = huffman_tree_root;
        }
    }
    
    return result;
}


void delete_huffman_tree(Node* root) {
    if (!root) return;
    
    delete_huffman_tree(root->left);
    delete_huffman_tree(root->right);
    delete root;
}

int main() {
    std::string text = "ceci est une phrase";
    
    auto freq_map = frequency(text);
    std::cout << "fréquences:" << std::endl;
    for (const auto& pair : freq_map) {
        std::cout << "'" << pair.first << "': " << pair.second << std::endl;
    }
    
    Node* root = build_huffman_tree(freq_map);
    
    auto encoding_table = build_encoding_table(root);
    std::cout << "\ntable d'encodage:" << std::endl;
    for (const auto& pair : encoding_table) {
        std::cout << "'" << pair.first << "': " << pair.second << std::endl;
    }
    
    std::string encoded = encode(text, encoding_table);
    std::cout << "\noriginal: " << text << std::endl;
    std::cout << "encodé: " << encoded << std::endl;
    
    std::string decoded = decode(encoded, root);
    std::cout << "décodé: " << decoded << std::endl;
    
    std::cout << "\ntaille originale: " << text.length() * 8 << " bits" << std::endl;
    std::cout << "taille encodée: " << encoded.length() << " bits" << std::endl;
    std::cout << "taux de compression: " << (double)encoded.length() / (text.length() * 8) << std::endl;
    
    delete_huffman_tree(root);
    
    return 0;
}