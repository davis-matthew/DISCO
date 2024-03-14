#include <iostream>
#include <regex>
#include <unordered_map>
#include <cctype>
#include <sstream>
#include <cstdint>

extern std::unordered_map<std::string, std::string> spellcheck_dict;
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
        if (spellcheck_dict.find(token) != spellcheck_dict.end()) {
            std::cerr << "[DISCO] Found token \"" << token << "\". Perhaps you meant \"" << spellcheck_dict[token] << "\"?" << std::endl; 
            count_spellcheck_errors++;
        }
    }
}

void printSpellcheckStats() {
    std::cerr << count_spellcheck_errors << " spellcheck errors found." << std::endl;
}