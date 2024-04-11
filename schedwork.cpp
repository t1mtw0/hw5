#ifndef RECCHECK
#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

// a constant that can be used to indicate an INVALID
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;

// Add prototypes for any helper functions here
bool schedule_helper(const AvailabilityMatrix &avail, const size_t dailyNeed,
                     const size_t maxShifts, std::vector<int> &shiftsDone,
                     std::vector<std::vector<int>> &workedAlready, int n, int d,
                     int k, DailySchedule &sched);

// Add your implementation of schedule() and other helper functions here

bool schedule(const AvailabilityMatrix &avail, const size_t dailyNeed,
              const size_t maxShifts, DailySchedule &sched) {
    if (avail.size() == 0U) {
        return false;
    }
    sched.clear();
    // Add your code below
    std::vector<int> shiftsDone((int)avail[0].size(), 0);
    std::vector<std::vector<int>> workedAlready(
        avail.size(), std::vector<int>(avail[0].size(), 0));
    for (int i = 0; i < (int)avail[0].size(); ++i) {
        std::vector<unsigned int> tmp;
        for (int j = 0; j < (int)dailyNeed; ++j) {
            tmp.push_back(0);
        }
        sched.push_back(tmp);
    }
    return schedule_helper(avail, dailyNeed, maxShifts, shiftsDone,
                           workedAlready, 0, 0, avail[0].size(), sched);
}

bool schedule_helper(const AvailabilityMatrix &avail, const size_t dailyNeed,
                     const size_t maxShifts, std::vector<int> &shiftsDone,
                     std::vector<std::vector<int>> &workedAlready, int n, int d,
                     int k, DailySchedule &sched) {
    // for (int i = 0; i < shiftsDone.size(); ++i) {
        // std::cout << shiftsDone[i] << " ";
    // }
    // std::cout << std::endl;
    // std::cout << n << " " << d << std::endl;
    if (n >= (int)avail.size())
        return true;
    int nN = n;
    int nD = d;
    if (d + 1 == dailyNeed) {
        nN++;
        nD = 0;
    } else {
        nD++;
    }
    for (int i = 0; i < k; ++i) {
        if (avail[n][i] && !workedAlready[n][i] &&
            (size_t)shiftsDone[i] < maxShifts) {
            workedAlready[n][i] = 1;
            sched[n][d] = i;
            shiftsDone[i]++;
            bool res = schedule_helper(avail, dailyNeed, maxShifts, shiftsDone,
                                       workedAlready, nN, nD, k, sched);
            if (res)
                return true;
            workedAlready[n][i] = 0;
            shiftsDone[i]--;
        }
    }
    return false;
}
