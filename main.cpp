#include <iostream>
#include <fstream>      // For file reading
#include <string>
#include <cctype>       // For character handling
#include <sstream>      // For string streaming
#include "BinaryTree/BinaryTree.h"
#include "BinaryTree/TreeMap.h"

#ifndef UNIT_TEST
int main() {
    std::string filename;
    std::cout << "Enter the filename to process: ";
    std::cin >> filename;

    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Could not open the file: " << filename << std::endl;
        return 1;
    }

    TreeMap<char, std::vector<std::string>> wordMap;
    std::string word;

    while (file >> word) {
        // Clean up the word and convert to lowercase if needed
        std::string cleanWord;
        for (char ch : word) {
            if (std::isalpha(ch)) {
                cleanWord += std::tolower(ch);
            }
        }
        if (!cleanWord.empty()) {
            char firstLetter = cleanWord[0];
            wordMap[firstLetter].push_back(cleanWord);
        }
    }

    file.close();

    // Display the results
    std::vector<char> keys = wordMap.keySet();
    std::cout << "Letters found in the file:" << std::endl;
    for (char key : keys) {
        std::cout << key << std::endl;
    }

    char inputKey;
    std::cout << "Enter a letter to see all associated words or '#' to exit: ";
    while (std::cin >> inputKey && inputKey != '#') {
        if (wordMap.containsKey(inputKey)) {
            std::vector<std::string> words = wordMap.get(inputKey);
            std::cout << "Words starting with '" << inputKey << "':" << std::endl;
            for (const std::string& w : words) {
                std::cout << w << std::endl;
            }
        } else {
            std::cout << "No words start with '" << inputKey << "'." << std::endl;
        }
        std::cout << "Enter another letter or '#' to exit: ";
    }

    return 0;
}
#endif