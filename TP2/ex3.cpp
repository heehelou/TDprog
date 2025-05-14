#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iterator>
#include <cctype>
#include <stack>
#include <stdexcept>
#include <cmath>

enum class Operator { ADD, SUB, MUL, DIV, EXP, OPEN_PAREN, CLOSE_PAREN };
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

    size_t start = (s[0] == '-' || s[0] == '+') ? 1 : 0;
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
        } else if (word == "(") {
            tokens.push_back(make_token(Operator::OPEN_PAREN));
        } else if (word == ")") {
            tokens.push_back(make_token(Operator::CLOSE_PAREN));
        } else if (word == "^") {
            tokens.push_back(make_token(Operator::EXP));
        } else {
            std::cout << "Erreur : Token invalide : " << word << std::endl;
            return {}; 
        }
    }

    return tokens;
}

int operator_precedence(Operator const op) {
    switch (op) {
        case Operator::ADD:
        case Operator::SUB: return 1;
        case Operator::MUL:
        case Operator::DIV: return 2;
        case Operator::EXP: return 3;
        default: return 0; 
    }
}

std::vector<Token> infix_to_npi_tokens(std::string const& expression) {
    std::vector<std::string> words = split_string(expression);
    std::vector<Token> infix_tokens = tokenize(words);

    if (infix_tokens.empty()) {
        std::cout << "Erreur : Impossible de convertir les tokens en NPI." << std::endl;
        return {};
    }

    std::vector<Token> output;
    std::stack<Operator> ops;

    for (Token const& token : infix_tokens) {
        if (token.type == TokenType::OPERAND) {
            output.push_back(token);
        } else if (token.op == Operator::OPEN_PAREN) {
            ops.push(token.op);
        } else if (token.op == Operator::CLOSE_PAREN) {
            while (!ops.empty() && ops.top() != Operator::OPEN_PAREN) {
                output.push_back(make_token(ops.top()));
                ops.pop();
            }
            if (ops.empty()) {
                std::cout << "Erreur : Parenthèse fermante sans ouvrante." << std::endl;
                return {}; 
            }
            ops.pop(); 
        } else {
            while (!ops.empty() &&
                   ((operator_precedence(ops.top()) > operator_precedence(token.op)) ||
                    (operator_precedence(ops.top()) == operator_precedence(token.op) && token.op != Operator::EXP))) {
                output.push_back(make_token(ops.top()));
                ops.pop();
            }
            ops.push(token.op);
        }
    }

    while (!ops.empty()) {
        if (ops.top() == Operator::OPEN_PAREN || ops.top() == Operator::CLOSE_PAREN) {
            std::cout << "Erreur : Parenthèses mal appariées." << std::endl;
            return {}; 
        }
        output.push_back(make_token(ops.top()));
        ops.pop();
    }

    return output;
}


int main() {
    std::string input;
    std::cout << "Entrez une expression infixe : ";
    std::getline(std::cin, input);

    std::vector<Token> npi_tokens;
    std::string error_message;

    std::vector<std::string> words = split_string(input);
    npi_tokens = infix_to_npi_tokens(input);

    if (npi_tokens.empty()) {
        std::cout << "Erreur : Impossible de convertir l'expression en NPI." << std::endl;
        return 1;
    }

    std::cout << "Expression en NPI : ";
    for (const Token& token : npi_tokens) {
        if (token.type == TokenType::OPERAND) {
            std::cout << token.value << " ";
        } else {
            switch (token.op) {
                case Operator::ADD: std::cout << "+ "; break;
                case Operator::SUB: std::cout << "- "; break;
                case Operator::MUL: std::cout << "* "; break;
                case Operator::DIV: std::cout << "/ "; break;
                case Operator::EXP: std::cout << "^ "; break;
                default: break;
            }
        }
    }
    std::cout << std::endl;

    return 0;
}
