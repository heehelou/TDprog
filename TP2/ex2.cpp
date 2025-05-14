#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iterator>
#include <cctype>
#include <stack>
#include <cmath> 

enum class Operator { ADD, SUB, MUL, DIV, EXP };
enum class TokenType { OPERATOR, OPERAND };

struct Token {
    TokenType type;
    float value;
    Operator op;
};

Token make_token(float value) {
    return Token{ TokenType::OPERAND, value, Operator::ADD };
}

Token make_token(Operator op) {
    return Token{ TokenType::OPERATOR, 0.0f, op };
}

bool is_floating(std::string const& s) {
    bool hasDot = false;
    if (s.empty()) return false;

    size_t start = 0;
    if (s[0] == '-' || s[0] == '+') {
        start = 1;
    }
    if (start >= s.size()) return false;

    for (size_t i = start; i < s.size(); ++i) {
        if (s[i] == '.') {
            if (hasDot) return false;
            hasDot = true;
        } else if (!std::isdigit(s[i])) {
            return false;
        }
    }
    return true;
}

std::vector<std::string> split_string(std::string const& s) {
    std::istringstream in(s);
    return std::vector<std::string>(std::istream_iterator<std::string>(in), std::istream_iterator<std::string>());
}

std::vector<Token> tokenize(std::vector<std::string> const& words) {
    std::vector<Token> tokens;

    for (std::string const& word : words) {
        if (is_floating(word)) {
            tokens.push_back(make_token(std::stof(word)));
        } else if (word == "+") {
            tokens.push_back(make_token(Operator::ADD));
        } else if (word == "-") {
            tokens.push_back(make_token(Operator::SUB));
        } else if (word == "*") {
            tokens.push_back(make_token(Operator::MUL));
        } else if (word == "/") {
            tokens.push_back(make_token(Operator::DIV));
        } else if (word == "^") { 
            tokens.push_back(make_token(Operator::EXP));
        } else {
            std::cout << "Erreur : Token invalide : " << word << std::endl;
            return {}; // Retourne un vecteur vide
        }
    }

    return tokens;
}

float npi_evaluate(std::vector<Token> const& tokens) {
    std::stack<float> stack;

    for (Token const& token : tokens) {
        if (token.type == TokenType::OPERAND) {
            stack.push(token.value);
        } else if (token.type == TokenType::OPERATOR) {
            if (stack.size() < 2) {
                std::cout << "Erreur : Pas assez d'opérandes pour effectuer l'opération." << std::endl;
                return 0.0f;
            }

            float right = stack.top();
            stack.pop();
            float left = stack.top();
            stack.pop();
            float result = 0.0f;

            switch (token.op) {
                case Operator::ADD:
                    result = left + right;
                    break;
                case Operator::SUB:
                    result = left - right;
                    break;
                case Operator::MUL:
                    result = left * right;
                    break;
                case Operator::DIV:
                    if (right == 0) {
                        std::cout << "Erreur : Division par zéro." << std::endl;
                        return 0.0f;
                    }
                    result = left / right;
                    break;
                case Operator::EXP: 
                    result = std::pow(left, right);
                    break;
            }

            stack.push(result);
        }
    }

    if (stack.size() != 1) {
        std::cout << "Erreur : Expression invalide." << std::endl;
        return 0.0f;
    }

    return stack.top();
}

int main() {
    std::string input;
    std::cout << "Entrez une expression arithmétique en NPI : ";
    std::getline(std::cin, input);

    std::vector<std::string> words = split_string(input);
    std::vector<Token> tokens = tokenize(words);

    if (tokens.empty()) {
        std::cout << "Erreur : Impossible de traiter l'expression." << std::endl;
        return 1;
    }

    float result = npi_evaluate(tokens);
    std::cout << "Résultat = " << result << std::endl;

    return 0;
}