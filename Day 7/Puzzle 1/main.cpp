#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <tuple>
#include <map>
#include <algorithm>

enum class HandStrength {
    HIGHCARD,
    ONEPAIR,
    TWOPAIR,
    THREEOFAKIND,
    FULLHOUSE,
    FOUROFAKIND,
    FIVEOFAKIND
};

int cardStrength(char card) {
    if (card >= '2' && card <= '9') return card - '0';
    if (card == 'T') return 10;
    if (card == 'J') return 11;
    if (card == 'Q') return 12;
    if (card == 'K') return 13;
    if (card == 'A') return 14;
    return -1;
}

HandStrength evaluateHand(const std::string &cards) {
    std::map<int, int> frequency;
    for (char card : cards) frequency[cardStrength(card)]++;

    bool isPair = false, isThreeOfAKind = false, isFourOfAKind = false, isFiveOfAKind = false;
    for (const auto &pair : frequency) {
        if (pair.second == 2) isPair = true;
        else if (pair.second == 3) isThreeOfAKind = true;
        else if (pair.second == 4) isFourOfAKind = true;
        else if (pair.second == 5) isFiveOfAKind = true;
    }

    if (isFiveOfAKind) return HandStrength::FIVEOFAKIND;
    else if (isFourOfAKind) return HandStrength::FOUROFAKIND;
    else if (isThreeOfAKind && isPair) return HandStrength::FULLHOUSE;
    else if (isThreeOfAKind) return HandStrength::THREEOFAKIND;
    else if (isPair) {
        int pairCount = 0;
        for (const auto &pair : frequency) {
            if (pair.second == 2) pairCount++;
        }
        if (pairCount == 2) return HandStrength::TWOPAIR;
        else return HandStrength::ONEPAIR;
    }

    return HandStrength::HIGHCARD;
}

int main() {
    std::vector<std::tuple<std::string, int, HandStrength>> hands;
    std::string temp;
    std::ifstream fIn("../../input.txt");
    while (std::getline(fIn, temp)) {
        std::stringstream ss(temp);
        int value;
        ss >> temp >> value;
        hands.emplace_back(temp, value, HandStrength::HIGHCARD);
    }
    fIn.close();

    for(auto& hand:hands){
        std::string cards = std::get<0>(hand);
        std::sort(cards.begin(), cards.end(), [](char a, char b) {
            return cardStrength(a) < cardStrength(b);
        });
        std::get<2>(hand) = evaluateHand(cards);
    }

    std::sort(hands.begin(), hands.end(), [](const auto& a, const auto& b) {
        HandStrength strengthA = std::get<2>(a);
        HandStrength strengthB = std::get<2>(b);

        if (strengthA == strengthB) {
            const std::string &cardsA = std::get<0>(a);
            const std::string &cardsB = std::get<0>(b);

            for (int i = 0; i < cardsA.size(); ++i) {
                if (cardStrength(cardsA[i]) != cardStrength(cardsB[i])) {
                    return cardStrength(cardsA[i]) < cardStrength(cardsB[i]);
                }
            }
        }

        return strengthA < strengthB;
    });

    int totalWinnings = 0;
    for (int i = 0; i < hands.size(); ++i) {
        totalWinnings += std::get<1>(hands[i]) * (i +1);
    }

    std::cout << totalWinnings << std::endl;
    return 0;
}
