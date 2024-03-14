def generate_cpp_code(input_file, output_file):
    with open(input_file, 'r') as file, open(output_file, 'w') as output:
        output.write("#include <unordered_map>\n#include <string>\n\n")
        output.write("std::unordered_map<std::string, std::string> globalDictionary = {\n")

        for line in file:
            parts = line.strip().split('->')

            key, values = parts
            value = values.split(',')[0]
            key = key.replace('"', '\\"')
            value = value.replace('"', '\\"')
            output.write(f'    {{"{key.lower()}", "{value.lower()}"}},\n')
        output.write("};\n")

generate_cpp_code("replacements.txt", "../src/globalDictionary.cpp")
