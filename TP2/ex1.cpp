#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iterator>
#include <cctype>
#include <stack>
#include <cmath>

std::vector<std::string> split_string(const std::string& input) {
    std::istringstream stream(input);
    std::vector<std::string> tokens((std::istream_iterator<std::string>(stream)), std::istream_iterator<std::string>());
    return tokens;
}

bool is_floating(const std::string& str) {
    if (str.empty()) {
        return false;
    }

    bool decimalPointFound = false;

    for (char ch : str) {
        if (!isdigit(ch)) {
            if (ch == '.' && !decimalPointFound) {
                decimalPointFound = true;
            } else {
                return false; // caractère non valide
            }
        }
    }

    return true; // tous les caractères sont valides
}

float npi_evaluate(const std::vector<std::string>& tokens) {
    std::stack<float> stack;

    for (const auto& token : tokens) {
        if (is_floating(token)) {
            stack.push(std::stof(token)); // convertir le token en float puis l'empiler
        } else if (token == "+" || token == "-" || token == "*" || token == "/" || token == "^") {
            if (stack.size() < 2) {
                std::cout << "Erreur : il n'y a pas assez d'opérandes pour l'opérateur " << token << "\n";
                return 0.0f;
            }

            float rightOperand = stack.top();
            stack.pop();
            float leftOperand = stack.top();
            stack.pop();
            float result = 0;

            if (token == "+") {
                result = leftOperand + rightOperand;
            } else if (token == "-") {
                result = leftOperand - rightOperand;
            } else if (token == "*") {
                result = leftOperand * rightOperand;
            } else if (token == "/") {
                if (rightOperand == 0) {
                    std::cout << "Oups ! on ne peut pas diviser par zéro.\n";
                    return 0.0f;
                }
                result = leftOperand / rightOperand;
            } else if (token == "^") {
                result = std::pow(leftOperand, rightOperand);
            }

            stack.push(result);
        } else {
            std::cout << "Oups ! opération invalide " << token << "\n";
            return 0.0f;
        }
    }

    if (stack.size() != 1) {
        std::cout << "OUps ! expression invalide. Il y a trop ou pas assez d'opérateurs.\n";
        return 0.0f;
    }

    return stack.top();
}

int main() {
    std::string input;
    std::cout << "Entrer une expression en notation polonaise inversée (NPI) : ";
    std::getline(std::cin, input);

    std::vector<std::string> tokens = split_string(input);

    float result = npi_evaluate(tokens);

    std::cout << "Résultat : " << result << std::endl;

    return 0;
}