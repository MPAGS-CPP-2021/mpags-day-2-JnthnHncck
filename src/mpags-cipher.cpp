#include <cctype>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "TransformChar.hpp"
#include "runCaesarCipher.hpp"

bool processCommandLine(const std::vector<std::string>& args,
const std::size_t& nArgs,
bool& helpRequested,
bool& versionRequested,
bool& doCipher,
bool& encrypt,
size_t& key,
std::string& inputFileName,
std::string& outputFileName)
{
    // Process command line arguments - ignore zeroth element, as we know this
    // to be the program name and don't need to worry about it
    for (std::size_t i{1}; i < nArgs; ++i) {
            if (args[i] == "-h" || args[i] == "--help") {
                helpRequested = true;
            } else if (args[i] == "--version") {
                versionRequested = true;
            } else if (args[i] == "-i") {
                // Handle input file option
                // Next element is filename unless "-i" is the last argument
                if (i == nArgs - 1) {
                    std::cerr << "[error] -i requires a filename argument"
                            << std::endl;
                    // exit main with non-zero return to indicate failure
                    return 1;
                } else {
                    // Got filename, so assign value and advance past it
                    inputFileName = args[i + 1];
                    ++i;
                }
            } else if (args[i] == "-o") {
                // Handle output file option
                // Next element is filename unless "-o" is the last argument
                if (i == nArgs - 1) {
                    std::cerr << "[error] -o requires a filename argument"
                            << std::endl;
                    // exit main with non-zero return to indicate failure
                    return 1;
                } else {
                    // Got filename, so assign value and advance past it
                    outputFileName = args[i + 1];
                    ++i;
                }    
            } else if (args[i] == "-d") {
                doCipher = true;
                if (i == nArgs - 1) {
                    std::cerr << "[error] -d requires a key argument"
                            << std::endl;
                    // exit main with non-zero return to indicate failure
                    return 1;
                } else{
                    key = std::stoul(args[i + 1]);
                    ++i;
                }
            } else if (args[i] == "-e") {
                doCipher = true;
                encrypt = true;
                if (i == nArgs - 1) {
                    std::cerr << "[error] -e requires a key argument"
                            << std::endl;
                    // exit main with non-zero return to indicate failure
                    return 1;
                } else{
                    key = std::stoul(args[i + 1]);
                    ++i;
                }
            } else {
                // Have an unknown flag to output error message and return non-zero
                // exit status to indicate failure
                std::cerr << "[error] unknown argument '" << args[i]
                        << "'\n";
                return 1;
            }
    }
    return 0;
}


int main(int argc, char* argv[])
{
    // Convert the command-line arguments into a more easily usable form
    const std::vector<std::string> cmdLineArgs{argv, argv + argc};
    const std::size_t nCmdLineArgs{cmdLineArgs.size()};

    // Options that might be set by the command-line arguments
    bool helpRequested{false};
    bool versionRequested{false};
    bool doCipher{false};
    bool encrypt{false};
    size_t key{0};
    std::string inputFile{""};
    std::string outputFile{""};

    bool commandLineStatus= processCommandLine(cmdLineArgs, nCmdLineArgs, helpRequested, versionRequested, doCipher, encrypt, key, inputFile, outputFile);
    if (commandLineStatus)
    {
        return 1;
    }

    // Handle help, if requested
    if (helpRequested) {
        // Line splitting for readability
        std::cout
            << "Usage: mpags-cipher [-h/--help] [--version] [-i <file>] [-o <file>]\n\n"
            << "Encrypts/Decrypts input alphanumeric text using classical ciphers\n\n"
            << "Available options:\n\n"
            << "  -h|--help        Print this help message and exit\n\n"
            << "  --version        Print version information\n\n"
            << "  -i FILE          Read text to be processed from FILE\n"
            << "                   Stdin will be used if not supplied\n\n"
            << "  -o FILE          Write processed text to FILE\n"
            << "                   Stdout will be used if not supplied\n\n"
            << std::endl;
        // Help requires no further action, so return from main
        // with 0 used to indicate success
        return 0;
    }

    // Handle version, if requested
    // Like help, requires no further action,
    // so return from main with zero to indicate success
    if (versionRequested) {
        std::cout << "0.1.0" << std::endl;
        return 0;
    }

    // Initialise variables
    char inputChar{'x'};
    std::string inputText;

    // Read in user input from stdin/file
    // If there is no input, use text instead
    if (!inputFile.empty()) {
        
        std::ifstream in_file {inputFile};
        //Checks that the file can be opened
        bool ok_to_read = in_file.good();
        if (!ok_to_read) {
            return 1;
        }
        char inputCharF {'x'};

        while (in_file >> inputCharF) {
            inputText += transformChar(inputCharF);
        }
        in_file.close();
    }
    else {
        // loop over each character from user input
        while (std::cin >> inputChar) {
            inputText += transformChar(inputChar);
        }
    }

    if (doCipher){
        inputText = runCaesarCipher(inputText, key, encrypt);
    }
    
    if (!outputFile.empty()) {
        std::ofstream out_file {outputFile};
        //Checks that the file can be opened
        bool ok_to_read = out_file.good();
        if (!ok_to_read) {
            return 1;
        }
        out_file << inputText;
        out_file.close();
    }
    else {
        // Print out the transliterated text
        std::cout << inputText << std::endl;
    }
    

    // No requirement to return from main, but we do so for clarity
    // and for consistency with other functions
    return 0;
}
