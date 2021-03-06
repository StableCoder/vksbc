/*
 *  MIT License
 *
 *  Copyright (c) 2017-2018 George Cave - gcave@stablecoder.ca
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 *
 */

#include <algorithm>
#include <cstdint>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <memory>
#include <string>

void printVersion() {
    printf("Vulkan Shader Binary Converter 1.1\n");
}

void printHelp() {
    printVersion();
    printf(
        "\nThis program takes in a file, and prints the binary data in"
        "\nan unsigned integer format so that it can be pasted in source code"
        "\nfor use."
        "\n\nUsage: vksbc [OPTIONS]... [FILE]\n"
        "\n  -o <FILE> Specified the particular file to print the output to, rather than the"
        "\n            default '<FILE>.out'"
        "\n\n  --ch      Output a C style header with the code in a static uint32_t array"
        "\n  --cpph    Output a C++ style header with the code in a constexpr uint32_t std::array"
        "\n  --help    Display this help and exit"
        "\n  --version Output version information and exit"
        "\n");
}

int main(int argc, char **argv) {
    std::string outFileName;
    int itemsWide = 8;
    bool cHeader{false};
    bool cppHeader{false};

    // Exit if no parameters given.
    if (argc < 2) {
        printf("vksbc error: no file given.\n");
        return 1;
    }

    for (int i = 0; i < argc; ++i) {
        char *arg = argv[i];
        if (!strcmp(arg, "--help")) {
            printHelp();
            return 0;
        } else if (!strcmp(arg, "--version")) {
            printVersion();
            return 0;
        } else if (!strcmp(arg, "-o") && (i + 1) < argc) {
            // Grab the next one and use it as the output file.
            outFileName = argv[i + 1];
        } else if (!strcmp(arg, "--ch")) {
            cHeader = true;
        } else if (!strcmp(arg, "--cpph")) {
            cppHeader = true;
        }
    }

    // Open the file.
    FILE *fp = fopen(argv[argc - 1], "rb");
    if (!fp) {
        printf("vksbc error: could not open shader file: %s\n", argv[1]);
        return 1;
    }

    // Generate the output file name if necessary
    if (outFileName.empty()) {
        outFileName = argv[argc - 1];
        // Find the last '.' and change the extension of it.
        auto pos = outFileName.find_last_of('.');
        if (pos != std::string::npos) {
            outFileName.erase(pos);
        }
    }

    // Read the file.
    fseek(fp, 0L, SEEK_END);
    unsigned int byteSize = static_cast<unsigned int>(ftell(fp));
    if (byteSize == 0) {
        printf("vksbc error: File is empty.\n");
        return 1;
    }
    if (byteSize % 4 != 0) {
        printf("vksbc error: file content is not multiple of 4.\n");
        return 1;
    }

    // Read the data in.
    fseek(fp, 0L, SEEK_SET);
    std::unique_ptr<uint32_t[]> data(new uint32_t[byteSize / 4]);
    if (fread(data.get(), byteSize, 1, fp) != 1) {
        printf("vksbc error: couldn't read file.\n");
        return 1;
    }
    // Close the file
    fclose(fp);

    // Open the output file(s)
    std::ofstream outFile(outFileName + ".out", std::ofstream::out);
    std::ofstream cOut;
    std::ofstream cppOut;
    if (cHeader) {
        cOut.open(outFileName + ".h", std::ofstream::out);
        cOut << "// Header generated by vksbc\n\n";
        cOut << "#include <stdint.h>\n\n";

        std::string varName = outFileName;
        auto lastSlash = varName.find_last_of('/');
        if (lastSlash != std::string::npos)
            varName = varName.substr(lastSlash + 1);
        lastSlash = varName.find_last_of('\\');
        if (lastSlash != std::string::npos)
            varName = varName.substr(lastSlash + 1);
        std::replace(varName.begin(), varName.end(), '.', '_');

        cOut << "static const uint32_t vk_" << varName << "_size = " << byteSize << ";\n";
        cOut << "static const uint32_t vk_" << varName << "[] = {\n    ";
    }
    if (cppHeader) {
        cppOut.open(outFileName + ".hpp", std::ofstream::out);
        cppOut << "// Header generated by vksbc\n\n";
        cppOut << "#include <array>\n";
        cppOut << "#include <cstdint>\n\n";

        std::string varName = outFileName;
        auto lastSlash = varName.find_last_of('/');
        if (lastSlash != std::string::npos)
            varName = varName.substr(lastSlash + 1);
        lastSlash = varName.find_last_of('\\');
        if (lastSlash != std::string::npos)
            varName = varName.substr(lastSlash + 1);
        std::replace(varName.begin(), varName.end(), '.', '_');

        cppOut << "constexpr uint32_t vk_" << varName << "_size = " << byteSize << ";\n";
        cppOut << "constexpr std::array<uint32_t, " << (byteSize / 4) << "> vk_" << varName
               << " = {\n    ";
    }

    int currentWidth = 0;
    for (unsigned int i = 0; i < byteSize / 4; ++i) {
        // Convert the 4-bytes into a 0x00000000 hexadecimal representation.
        outFile << "0x" << std::hex << std::setw(sizeof(uint32_t) * 8 / 4) << std::uppercase
                << std::setfill('0') << data[i] << ", ";
        if (cOut)
            cOut << "0x" << std::hex << std::setw(sizeof(uint32_t) * 8 / 4) << std::uppercase
                 << std::setfill('0') << data[i] << ", ";
        if (cppOut)
            cppOut << "0x" << std::hex << std::setw(sizeof(uint32_t) * 8 / 4) << std::uppercase
                   << std::setfill('0') << data[i] << ", ";

        ++currentWidth;

        // Newline after certain number of items.
        if (currentWidth == itemsWide) {
            currentWidth = 0;
            outFile << '\n';
            if (cOut)
                cOut << "\n    ";
            if (cppOut)
                cppOut << "\n    ";
        }
    }

    outFile.close();
    if (cOut) {
        cOut << "\n};";
        cOut.close();
    }
    if (cppOut) {
        cppOut << "\n};";
        cppOut.close();
    }

    return 0;
}