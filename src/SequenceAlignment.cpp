#include "SequenceAlignment.h"
#include <stack>

SequenceAlignment::SequenceAlignment()
    : gap_penalty_(30)
{
    InitializePenaltyTable(mismatch_penalty_table_);
}

void SequenceAlignment::InitializePenaltyTable(unordered_map<char, unordered_map<char, int>>& table)
{
    table['A']['A'] = 0;
    table['A']['C'] = 110;
    table['A']['G'] = 48;
    table['A']['T'] = 94;
    table['C']['A'] = 110;
    table['C']['C'] = 0;
    table['C']['G'] = 118;
    table['C']['T'] = 48;
    table['G']['A'] = 48;
    table['G']['C'] = 118;
    table['G']['G'] = 0;
    table['G']['T'] = 110;
    table['T']['A'] = 94;
    table['T']['C'] = 48;
    table['T']['G'] = 110;
    table['T']['T'] = 0;
}

vector<vector<int>> SequenceAlignment::ComputeMinimumAlignmentCost(
    const string& _s1,
    const string& _s2)
{
    int m = _s1.size() + 1; // OPT table's row
    int n = _s2.size() + 1; // OPT table's col
    vector<vector<int>> OPT(m, vector<int>(n, INT32_MAX));

    // Initialize edge case
    OPT[0][0] = 0;
    for (int i = 1; i < m; i++) {
        OPT[i][0] = i * gap_penalty_;
    }
    for (int i = 1; i < n; i++) {
        OPT[0][i] = i * gap_penalty_;
    }

    // DP formula bottom-up
    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            OPT[i][j] =
                min(OPT[i - 1][j - 1] + mismatch_penalty_table_[_s1[i - 1]][_s2[j - 1]],
                    min(OPT[i - 1][j] + gap_penalty_, OPT[i][j - 1] + gap_penalty_));
        }
    }

    return OPT;
}

vector<pair<char, char>> SequenceAlignment::ReconstructAlignment(
    vector<vector<int>>& table,
    const string& _s1,
    const string& _s2)
{
    int i = table.size() - 1;
    int j = table[0].size() - 1;

    vector<pair<char, char>> alignment;
    // The optimal alignment is not unique
    // Below is one of the ways to reconstruct alignment
    while (i > 0 || j > 0) {
        if (j - 1 >= 0 && table[i][j] == (table[i][j - 1] + gap_penalty_)) {
            // skip s2[j]
            alignment.push_back({'_', _s2[j - 1]});
            j--;
        } else if (
            (i - 1) >= 0 && (j - 1) >= 0 &&
            table[i][j] ==
                (table[i - 1][j - 1] + mismatch_penalty_table_[_s1[i - 1]][_s2[j - 1]])) {
            // s1[i] is matched with s2[j]
            alignment.push_back({_s1[i - 1], _s2[j - 1]});
            i--;
            j--;
        } else if ((i - 1) >= 0 && table[i][j] == (table[i - 1][j] + gap_penalty_)) {
            // skip s1[i]
            alignment.push_back({_s1[i - 1], '_'});
            i--;
        }
    }
    return alignment;
}

vector<pair<char, char>> SequenceAlignment::DivideAndConquerAlignment(
    const string& _s1,
    const string& _s2)
{
    // Base Case
    if (_s1.size() <= 2 || _s2.size() <= 2) {
        vector<vector<int>> opt_table = ComputeMinimumAlignmentCost(_s1, _s2);

        return ReconstructAlignment(opt_table, _s1, _s2);
    }

    vector<pair<char, char>> res;

    // Divide
    // TODO: split the longest
    int s1_mid = _s1.size() / 2;
    string s1_left_part = _s1.substr(0, s1_mid);
    vector<int> cost_left = SpaceEfficientAlignment(s1_left_part, _s2);

    string s1_right_part = _s1.substr(s1_mid, _s1.size() - s1_mid);
    string reversed_s1_right_part = string(s1_right_part.rbegin(), s1_right_part.rend());
    string reversed_s2 = string(_s2.rbegin(), _s2.rend());
    vector<int> cost_right = SpaceEfficientAlignment(reversed_s1_right_part, reversed_s2);

    vector<int> cost(cost_left.size(), 0);
    for (int i = 0; i < cost_left.size(); i++) {
        cost[i] = cost_left[i] + cost_right[cost_right.size() - 1 - i];
    }

    int s2_optimal_divide_length =
        std::min_element(cost.begin(), cost.end()) - cost.begin(); // One of optimal cut lengths
    //    cout << "s2_optimal_divide_length: " << s2_optimal_divide_length << endl;

    // Conquer
    auto res_left =
        DivideAndConquerAlignment(s1_left_part, _s2.substr(0, s2_optimal_divide_length));
    auto res_right = DivideAndConquerAlignment(
        s1_right_part,
        _s2.substr(s2_optimal_divide_length, _s2.size() - s2_optimal_divide_length));

    // Combine
    res.resize(res_right.size() + res_left.size());
    move(res_right.begin(), res_right.end(), res.begin());
    move(res_left.begin(), res_left.end(), res.begin() + res_right.size());

    return res;
}

vector<int> SequenceAlignment::SpaceEfficientAlignment(const string& _s1, const string& _s2)
{
    int m = _s1.size() + 1; // OPT table's row
    int n = _s2.size() + 1; // OPT table's col
    vector<vector<int>> table(2, vector<int>(n, INT32_MAX));

    // Initialize Edge Case
    for (int i = 0; i < n; i++) {
        table[0][i] = i * gap_penalty_;
    }

    // DP formula bottom-up
    for (int i = 1; i < m; i++) {
        table[1][0] = i * gap_penalty_;
        for (int j = 1; j < n; j++) {
            table[1][j] =
                min(table[0][j - 1] + mismatch_penalty_table_[_s1[i - 1]][_s2[j - 1]],
                    min(table[0][j] + gap_penalty_, table[1][j - 1] + gap_penalty_));
        }
        table[0] = table[1];
    }

    return table[1];
}