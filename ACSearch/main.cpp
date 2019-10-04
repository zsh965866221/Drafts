#include "ACSearch.h"

int main() {
    std::vector<std::string> patterns {"ash", "shex", "bcd", "sha", "ab", "abc", "aba"};
    zsh::ACSearchor searchor(patterns);
    std::string text = "secashcvashexbcdashareerwqrqewrababcabacabacc";
    std::map<std::string, std::vector<int>> ret = searchor.find(text);
    for (auto pair: ret) {
        std::cout << pair.first << ": ";
        for (auto index: pair.second) {
            std::cout << index << ", ";
        }
        std::cout << std::endl;
    }

    return 0;
}