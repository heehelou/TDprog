#include <iostream>
#include <string>
#include <cctype>

// run-length
std::string runlength_encode(const std::string& s) {
    if (s.empty()) return "";
    
    std::string result;
    char current_char = s[0];
    int count = 1;
    
    for (size_t i = 1; i < s.length(); ++i) {
        if (s[i] == current_char) {
            count++;
        } else {
            result += std::to_string(count) + current_char;
            current_char = s[i];
            count = 1;
        }
    }
    result += std::to_string(count) + current_char;
    return result;
}

//décoder 
std::string runlength_decode_simple(const std::string& s) {
    std::string result;
    for (size_t i = 0; i < s.length(); i += 2) {
        if (i + 1 < s.length()) {
            int count = s[i] - '0';
            char character = s[i + 1];
            result += std::string(count, character);
        }
    }
    return result;
}

//décoder avec nombres à pls chiffres
std::string runlength_decode(const std::string& s) {
    std::string result;
    size_t i = 0;
    
    while (i < s.length()) {
        std::string number_str;
        while (i < s.length() && std::isdigit(s[i])) {
            number_str += s[i];
            i++;
        }
        
        if (i < s.length()) {
            int count = std::stoi(number_str);
            char character = s[i];
            result += std::string(count, character);
            i++;
        }
    }
    return result;
}

//encodage avec caractère de contrôle
std::string runlength_encode_control(const std::string& s, char control_char) {
    if (s.empty()) return s;
    
    std::string result;
    char current_char = s[0];
    int count = 1;
    
    for (size_t i = 1; i < s.length(); ++i) {
        if (s[i] == current_char) {
            count++;
        } else {
            if (count > 1) {
                result += control_char + std::to_string(count) + current_char;
            } else {
                result += current_char;
            }
            current_char = s[i];
            count = 1;
        }
    }
    
    if (count > 1) {
        result += control_char + std::to_string(count) + current_char;
    } else {
        result += current_char;
    }

    if (result.length() < s.length()) {
        return result;
    } else {
        return s;
    }
}

//décodage avec caractère de contrôle
std::string runlength_decode_control(const std::string& s, char control_char) {
    std::string result;
    size_t i = 0;
    
    while (i < s.length()) {
        if (s[i] == control_char) {
            i++; 
            
            std::string number_str;
            while (i < s.length() && std::isdigit(s[i])) {
                number_str += s[i];
                i++;
            }
            
            if (i < s.length()) {
                int count = std::stoi(number_str);
                char character = s[i];
                result += std::string(count, character);
                i++;
            }
        } else {
            result += s[i];
            i++;
        }
    }
    return result;
}

int main() {
    std::string test = "AAAABBBCCDAA";
    
    // Test encodage de base
    std::string encoded = runlength_encode(test);
    std::cout << "Original: " << test << std::endl;
    std::cout << "Encodé: " << encoded << std::endl;
    
    // Test décodage
    std::string decoded = runlength_decode(encoded);
    std::cout << "Décodé: " << decoded << std::endl;
    
    // Test avec caractère de contrôle
    std::string encoded_control = runlength_encode_control(test, '*');
    std::cout << "Encodé avec contrôle: " << encoded_control << std::endl;
    
    std::string decoded_control = runlength_decode_control(encoded_control, '*');
    std::cout << "Décodé du contrôle: " << decoded_control << std::endl;
    
    // Test avec nombres à plusieurs chiffres
    std::string multi_digit = "12A3B2C1D2A";
    std::string decoded_multi = runlength_decode(multi_digit);
    std::cout << "Multi-chiffres décodé: " << decoded_multi << std::endl;
    
    return 0;
}