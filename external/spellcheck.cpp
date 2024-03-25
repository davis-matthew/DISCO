#include <iostream>
#include <regex>
#include <unordered_map>
#include <cctype>
#include <sstream>
#include <cstdint>

extern std::unordered_map<std::string, std::string> replacements_dictionary;
extern uint64_t count_spellcheck_errors;

void spellcheck_io(std::string &input) {
    std::string input_without_symbols = std::regex_replace(input, std::regex("[,.\\/:\"-]"), " ");
    int i = 0;
    for (char &c : result) {
        input_without_symbols[i] = std::tolower(c);
        i++;
    }

    std::istringstream input_without_symbols_stringstream(input_without_symbols);
 
    std::string token;
    while (std::getline(input_without_symbols_stringstream, token, ' ')) {
        if (replacements_dictionary.find(token) != replacements_dictionary.end()) {
            std::cerr << "[DISCO] Found token \"" << token << "\". Perhaps you meant \"" << replacements_dictionary[token] << "\"?" << std::endl; 
            count_spellcheck_errors++;
        }
    }
}

void printSpellcheckStats() {
    std::cerr << count_spellcheck_errors << " spellcheck errors found." << std::endl;
}