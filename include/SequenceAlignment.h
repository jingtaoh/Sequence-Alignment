#ifndef SEQUENCE_ALIGNMENT_H
#define SEQUENCE_ALIGNMENT_H

#include <algorithm>
#include <iostream>
#include <map>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class SequenceAlignment
{
public:
    /**
     * @brief: Initialize mismatch penalty table and gap penalty;
     *         Record two input strings;
     *         Initialize 2D matrix to store minimum cost.
     * @param: s1: input string 1
     * @param: s2: input string 2
     **/
    SequenceAlignment();

    ~SequenceAlignment() {}

    /**
     * @brief: Use Dynamic Programming to compute OPT table
     * @param: s1: input string 1
     * @param: s2: input string 2
     **/
    vector<vector<int>> ComputeMinimumAlignmentCost(const string& _s1, const string& _s2);

    /**
     * @brief: D&C helper function
     * @param: s1: input string 1
     * @param: s2: input string 2
     **/
    stack<pair<int, int>> DivideAndConquerAlignmentHelper(const string& _s1, const string& _s2);

    /**
     * @brief: D&C + DP to solve sequence alignment
     * @param: s1: input string 1
     * @param: s2: input string 2
     **/
    map<int, int> DivideAndConquerAlignment(const string& _s1, const string& _s2);

    /**
     * @brief: Space efficient way to compute the last row of the OPT table
     * @param: s1: input string 1
     * @param: s2: input string 2
     **/
    vector<int> SpaceEfficientAlignment(const string& _s1, const string& _s2);

    /**
     * @brief: Reconstruct Alignment from OPT table
     * @param: table: OPT table
     * @param: s1: input string 1
     * @param: s2: input string 2
     * @return: matched pairs
     **/
    stack<pair<int, int>>
    ReconstructAlignment(vector<vector<int>>& table, const string& _s1, const string& _s2);

private:
    /**
     * @brief: Initialize  mismatch penalty table
     * @param: table: mismatch penalty table
     **/
    void InitializePenaltyTable(unordered_map<char, unordered_map<char, int>>& table);

private:
    const int gap_penalty_;

public:
    unordered_map<char, unordered_map<char, int>> mismatch_penalty_table_;
};

#endif