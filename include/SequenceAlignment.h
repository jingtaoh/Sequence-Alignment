#ifndef SEQUENCE_ALIGNMENT_H
#define SEQUENCE_ALIGNMENT_H

#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <stack>

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
    SequenceAlignment(const string &s1, const string &s2);

    ~SequenceAlignment() {}

    /**
     * @brief: Use Dynamic Programming to compute OPT table
     **/
    void ComputeMinimumAlignmentCost();

    /**
     * @brief: Reconstruct Alignment from OPT table
     * @return: matched pairs
     **/
    stack<pair<int, int>> ReconstructAlignment();

    /**
     * @brief: Return OPT table
     **/
    vector<vector<int>> GetOptTable();

private:
    void InitializePenaltyTable(unordered_map<char, unordered_map<char, int>> &table);

private:
    string s1_;
    string s2_;

    const int gap_penalty_;
    unordered_map<char, unordered_map<char, int>> mismatch_penalty_table_;

    vector<vector<int>> OPT_;
};

#endif