#include <iostream>
#include <regex>
#include <unordered_map>
#include <cctype>
#include <sstream>
#include <cstdint>

extern std::unordered_map<std::string, std::string> replacements_dictionary;
uint64_t count_spellcheck_errors = 0;

extern "C" void spellcheck_io(const char* input_cstr) {
    std::string input(input_cstr);
    
    std::string input_without_symbols = std::regex_replace(input, std::regex("[,.\\/:\"-]"), " ");
    
    for (size_t i = 0; i < input_without_symbols.length(); ++i) {
        input_without_symbols[i] = std::tolower(input_without_symbols[i]);
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

extern "C" void printSpellcheckStats() {
    std::cerr << "[DISCO] " << count_spellcheck_errors << " spellcheck errors found." << std::endl;
}