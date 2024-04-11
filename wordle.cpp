#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm>
#include <map>
#include <set>
#endif

#include "dict-eng.h"
#include "wordle.h"

// Add prototypes of helper functions here
void wordle_helper(std::string in, std::string floating,
                   const std::set<std::string> &dict, int pos, int num_blnk,
                   std::set<std::string> &res);

// Definition of primary wordle function
std::set<std::string> wordle(const std::string &in, const std::string &floating,
                             const std::set<std::string> &dict) {
    std::set<std::string> res;
    int num_blnk;
    for (char c : in) {
        if (c == '-')
            num_blnk++;
    }
    wordle_helper(in, floating, dict, 0, num_blnk, res);
    return res;
}

// Define any helper functions here
void wordle_helper(std::string in, std::string floating,
                   const std::set<std::string> &dict, int pos, int num_blnk,
                   std::set<std::string> &res) {
    if (pos == (int)in.size()) {
        if (dict.find(in) != dict.end())
            res.insert(in);
    }
    int num_flt;
    for (std::string::iterator it = floating.begin(); it != floating.end();
         ++it) {
        if (*it == '-')
            continue;
        in[pos] = *it;
        *it = '-';
        wordle_helper(in, floating, dict, pos + 1, num_blnk - 1, res);
        num_flt++;
    }
    if (num_blnk < num_flt) {
        for (char c = 'a'; c < 'z'; ++c) {
            in[pos] = c;
            wordle_helper(in, floating, dict, pos + 1, num_blnk - 1, res);
        }
    }
    in[pos] = '-';
}
