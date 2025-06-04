#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

enum class CardKind {
    Heart,
    Diamond,
    Club,
    Spade
};

enum class CardValue {
    Two,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Ten,
    Jack,
    Queen,
    King,
    Ace
};

struct Card {
    CardKind kind;
    CardValue value;

    bool operator==(const Card& other) const {
        return kind == other.kind && value == other.value;
    }

    size_t hash() const {
        return static_cast<int>(kind) * 13 + static_cast<int>(value);
    }
};

namespace std {
    template<>
    struct hash<Card> {
        size_t operator()(const Card& c) const {
            return c.hash();
        }
    };
}

std::string card_name(Card const& card) {
    std::string name {};

    unsigned int card_value {(static_cast<unsigned int>(card.value)+2) % 14};

    if (card_value < 10) {
        name += '0' + std::to_string(card_value);
    }else if (card_value == 10) {
        name += "10";
    }else if (card_value == 11) {
        name += 'J';
    }else if (card_value == 12) {
        name += 'Q';
    }else if (card_value == 13) {
        name += 'K';
    }

    name += " of ";

    if (card.kind == CardKind::Heart) {
        name += "Heart";
    }else if (card.kind == CardKind::Diamond) {
        name += "Diamond";
    }else if (card.kind == CardKind::Club) {
        name += "Club";
    }else if (card.kind == CardKind::Spade) {
        name += "Spade";
    }
    return name;
}

std::vector<Card> get_cards(size_t n) {
    std::vector<Card> cards;
    for (size_t i = 0; i < n; ++i) {
        CardKind k = static_cast<CardKind>(rand() % 4);
        CardValue v = static_cast<CardValue>(rand() % 13);
        cards.push_back({k, v});
    }
    return cards;
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    auto cards = get_cards(100);

    std::unordered_map<Card, int> freq;

    for (const auto& c : cards) {
        freq[c]++;
    }

    for (const auto& pair : freq) {
        std::cout << card_name(pair.first) << " : " << pair.second << std::endl;
    }

    return 0;
}
