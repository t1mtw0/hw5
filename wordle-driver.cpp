// main() program to test your schedule function.
// Feel free to modify though it will be easiest to
// simply pass in different command line arguments to test
// various cases of words and letters.
// This file will not be graded.
#include "dict-eng.h"
#include "wordle.h"
#include <iostream>
#include <set>
#include <string>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "Please provide an initial string (e.g. \"s---ng\")"
                " and optional string of floating characters."
             << std::endl;
        return 1;
    }
    const std::set<std::string> &dict = readDictWords("dict-eng.txt");
    std::string in(argv[1]);
    std::string floatingChars;
    if (argc > 2) {
        floatingChars = argv[2];
    }
    std::set<std::string> answers;
    answers = wordle(in, floatingChars, dict);
    for (auto s : answers) {
        std::cout << s << std::endl;
    }
    return 0;
}
