/*
 * Nick Ray
 * 2/15/21
 * scanner
 */
#include <fstream>
#include <istream>
#include <iostream>
#include "init.hpp"
#include "parseCommandLineOpts.hpp"
#include "parser.hpp"
#include "scanner.hpp"
#include "TokenRecord.hpp"
#include "token.hpp"
#include "utils.hpp"

int main(int argc, char **argv) {
    std::string fileNameToRead;

    // Parse Command Line Options
    switch (parseCommandLineOpts(argc, argv)) {
        case -1:
            std::cout << "Invalid Usage - Terminating" << std::endl;
            return -1;
        case 1: // Help flag was used, gracefully exit
            return 0;
    }

    // Setup / validate file to read from using keyboard input, input redirection or command line argument
    init(argc, argv, fileNameToRead);

    // Setup a file stream to assign src in scanner
    std::ifstream srcFile(fileNameToRead + ".fs");
    std::string srcString;
    readSrcIntoString(srcFile, srcString);
    std::cout << "srcString: \n" << srcString << std::endl;

    // Initialize the Scanner
    Scanner *scanner = initScanner(srcString);

    /* ------------------------------------ */
    // Test Parser
    /* ------------------------------------ */

    parser(scanner);

    std::cout << "\t::Post-parser()" << std::endl;

    /* ------------------------------------ */
    // Free memory
    /* ------------------------------------ */
    free(scanner);
    srcFile.close();

    return 0;
}
