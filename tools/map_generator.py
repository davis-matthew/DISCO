def generate_cpp_code(input_file, output_file):
    with open(input_file, 'r') as file, open(output_file, 'w') as output:
        output.write("#include <unordered_map>\n#include <string>\n#include <cstdint>\n\n")
        output.write("static uint64_t count_spellcheck_errors = 0;\n")
        output.write("static std::unordered_map<std::string, std::string> spellcheck_dict = {\n")

        for line in file:
            parts = line.strip().split('->')

            key, values = parts
            value = values.split(',')[0]
            key = key.replace('"', '\\"')
            value = value.replace('"', '\\"')
            output.write(f'    {{"{key.lower()}", "{value.lower()}"}},\n')
        output.write("};\n")

generate_cpp_code("replacements.txt", "../external/spellcheck_dict.cpp")
