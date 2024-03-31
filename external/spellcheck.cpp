#include <iostream>
#include <regex>
#include <unordered_map>
#include <cctype>
#include <sstream>
#include <cstdint>

extern std::unordered_map<std::string, std::string> replacements_dictionary;
uint64_t count_spellcheck_errors = 0;

// Replace all instances of 'target' in a string with 'replacement'
void replaceAll(std::string &str, const std::string &target, const std::string &replacement) {
    size_t index = 0;
    while((index = str.find(target, index)) != std::string::npos) {
        str.replace(index, target.length(), replacement);
        index += replacement.length();
    }
}

extern "C" void spellcheck_io(const char* input_cstr) {
    std::string input(input_cstr);
    
    std::string input_without_symbols = std::regex_replace(input, std::regex("[,.\\/:\"-]"), " ");
    
    for (size_t i = 0; i < input_without_symbols.length(); ++i) {
        input_without_symbols[i] = std::tolower(input_without_symbols[i]);
    }

    std::istringstream input_without_symbols_stringstream(input_without_symbols);
 
    bool replacementMade = false;
    std::string token;
    std::vector<std::pair<uint64_t,uint64_t>> replacements;
    while (std::getline(input_without_symbols_stringstream, token, ' ')) {
        if (replacements_dictionary.find(token) != replacements_dictionary.end()) {
            replaceAll(input, token, replacements_dictionary[token]);
            count_spellcheck_errors++;
            replacementMade = true;
        }
    }
    
    if(replacementMade) {
        std::cerr << "[DISCO] Detected spelling/grammar mistakes in the upcoming print statement. Probably meant:\n" << input << "\n\n"; 
    }
}

extern "C" void printSpellcheckStats() {
    std::cerr << "[DISCO] " << count_spellcheck_errors << " spellcheck errors found." << std::endl;
}