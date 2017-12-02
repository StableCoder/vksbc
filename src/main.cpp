/*
 *  MIT License
 *
 *  Copyright (c) 2017 George Cave
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

// C++
#include <cstring>
#include <iomanip>
#include <memory>
#include <sstream>

void printHelp() {
    printf("\nThis program takes in a file, and prints the binary data in"
           "\nan unsigned integer format so that it can be pasted in source code"
           "\nfor use."
           "\n\nUsage: vkshaderbinaryconverter [option]... [file]\n"
           "\n  -o <file> Specified the particular file to print the output to, rather than the"
           "\n            default '<input-file>.txt'."
           "\n\n  --help     Display this help and exit."
           "\n  --version  Output version information and exit\n");
}

void printVersion() {
    printf("\nVulkan Shader Binary Converter 1.0");
}

int main(int argc, char **argv) {
    std::string outFileName;
    int itemsWide = 8;

    // Exit if no other parameters given.
    if (argc < 2) {
        printf("vkshaderbinaryconverter: no file given.");
        return 0;
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
        }
    }

    // Open the file.
    FILE *fp = fopen(argv[argc - 1], "rb");
    if (!fp) {
        printf("vkshaderbinaryconverter: could not open shader file: %s", argv[1]);
        return 0;
    }

    // Generate the output file name if necessary
    if (outFileName.empty()) {
        outFileName = argv[argc - 1];
        // Find the last '.' and change the extension of it.
        auto pos = outFileName.find_last_of('.');
        if (pos != std::string::npos) {
            outFileName.erase(pos);
        }
        outFileName += ".txt";
    }

    // Read the file.
    fseek(fp, 0L, SEEK_END);
    unsigned int byteSize = static_cast<unsigned int>(ftell(fp));
    if (byteSize == 0) {
        printf("File is empty.");
        return 0;
    }
    if (byteSize % 4 != 0) {
        printf("vkshaderbinaryconverter: file content is not multiple of 4.");
        return 0;
    }

    // Read the data in.
    fseek(fp, 0L, SEEK_SET);
    std::unique_ptr<uint32_t[]> data(new uint32_t[byteSize / 4]);
    if (fread(data.get(), byteSize, 1, fp) != 1) {
        printf("vkshaderbinaryconverter: error reading file.");
        return 0;
    }
    // Close the file
    fclose(fp);

    // Open the output file.
    fp = fopen(outFileName.c_str(), "w");

    int currentWidth = 0;
    for (unsigned int i = 0; i < byteSize / 4; ++i) {
        std::stringstream ss;
        // Convert the 4-bytes into a 0x00000000 hexadecimal representation.
        ss << "0x" << std::hex << std::setw(sizeof(uint32_t) * 8 / 4) << std::uppercase
           << std::setfill('0') << data[i];
        // Write it out.
        fwrite(ss.str().c_str(), ss.str().size(), 1, fp);
        // Add a comma and space.
        fwrite(", ", 2, 1, fp);
        ++currentWidth;

        if (currentWidth == itemsWide) {
            currentWidth = 0;
            fwrite("\n", 1, 1, fp);
        }
    }
    fclose(fp);

    return 0;
}