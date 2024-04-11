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
                   int num_flt, std::set<std::string> &res);

// Definition of primary wordle function
std::set<std::string> wordle(const std::string &in, const std::string &floating,
                             const std::set<std::string> &dict) {
    std::set<std::string> res;
    int num_blnk = 0;
    for (char c : in) {
        if (c == '-')
            num_blnk++;
    }
    wordle_helper(in, floating, dict, 0, num_blnk, floating.size(), res);
    return res;
}

// Define any helper functions here
void wordle_helper(std::string in, std::string floating,
                   const std::set<std::string> &dict, int pos, int num_blnk,
                   int num_flt, std::set<std::string> &res) {
    if (in[pos] != '-')
        wordle_helper(in, floating, dict, pos + 1, num_blnk, num_flt, res);
    if (num_blnk == 0) {
        if (num_flt == 0 && dict.find(in) != dict.end())
            res.insert(in);
        return;
    }
    for (std::string::iterator it = floating.begin(); it != floating.end();
         ++it) {
        if (*it == '-')
            continue;
        in[pos] = *it;
        *it = '-';
        wordle_helper(in, floating, dict, pos + 1, num_blnk - 1, num_flt - 1,
                      res);
    }
    if (num_blnk > num_flt) {
        for (char c = 'a'; c < 'z'; ++c) {
            in[pos] = c;
            wordle_helper(in, floating, dict, pos + 1, num_blnk - 1, num_flt,
                          res);
        }
    }
    in[pos] = '-';
}
