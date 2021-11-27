#include "SequenceAlignment.h"

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

stack<pair<int, int>> SequenceAlignment::ReconstructAlignment(
    vector<vector<int>>& table,
    const string& _s1,
    const string& _s2)
{
    int i = table.size() - 1;
    int j = table[0].size() - 1;

    stack<pair<int, int>> alignment;
    // The optimal alignment is not unique
    // Below is one of the ways to reconstruct alignment
    while (i > 0 || j > 0) {
        if (j - 1 >= 0 && table[i][j] == (table[i][j - 1] + gap_penalty_)) {
            // skip s2[j]
            j--;
        } else if (
            (i - 1) >= 0 && (j - 1) >= 0 &&
            table[i][j] ==
                (table[i - 1][j - 1] + mismatch_penalty_table_[_s1[i - 1]][_s2[j - 1]])) {
            // s1[i] is matched with s2[j]
            alignment.push({i - 1, j - 1});
            i--;
            j--;
        } else if ((i - 1) >= 0 && table[i][j] == (table[i - 1][j] + gap_penalty_)) {
            // skip s1[i]
            i--;
        }
    }
    return alignment;
}


stack<pair<int, int>> SequenceAlignment::DivideAndConquerAlignmentHelper(
    const string& _s1,
    const string& _s2)
{
    stack<pair<int, int>> res; // s1: 0-res[0]; s2: 0-res[1]; res[2] s1 & s2 mismatch penalty
    // Base Case
    if (_s1.size() <= 2 || _s2.size() <= 2) {
        vector<vector<int>> opt_table = ComputeMinimumAlignmentCost(_s1, _s2);

        return ReconstructAlignment(opt_table, _s1, _s2);
        ;
    }

    ///// Divide
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
    // cout << "s2_optimal_divide_length: " << s2_optimal_divide_length << endl;

    //// Conquer
    stack<pair<int, int>> stack_left =
        DivideAndConquerAlignmentHelper(s1_left_part, _s2.substr(0, s2_optimal_divide_length));


    stack<pair<int, int>> stack_right = DivideAndConquerAlignmentHelper(
        s1_right_part,
        _s2.substr(s2_optimal_divide_length, _s2.size() - s2_optimal_divide_length));

    //// Combine
    stack<pair<int, int>> tmp_stack2;
    while (!stack_right.empty()) {
        pair<int, int> tmp = stack_right.top();
        stack_right.pop();
        tmp.first += s1_mid;
        tmp.second += s2_optimal_divide_length;
        tmp_stack2.push(tmp);
    }
    while (!tmp_stack2.empty()) {
        pair<int, int> tmp = tmp_stack2.top();
        tmp_stack2.pop();
        res.push(tmp);
    }

    res.push({s1_mid - 1, s2_optimal_divide_length - 1});

    stack<pair<int, int>> tmp_stack1;
    while (!stack_left.empty()) {
        pair<int, int> tmp = stack_left.top();
        stack_left.pop();
        tmp_stack1.push(tmp);
    }
    while (!tmp_stack1.empty()) {
        pair<int, int> tmp = tmp_stack1.top();
        tmp_stack1.pop();
        res.push(tmp);
    }
    return res;
}

map<int, int> SequenceAlignment::DivideAndConquerAlignment(const string& _s1, const string& _s2)
{
    stack<pair<int, int>> s = DivideAndConquerAlignmentHelper(_s1, _s2);
    map<int, int> matches;
    unordered_set<int> s2_set;
    while (!s.empty()) {
        pair<int, int> tmp = s.top();
        if (!matches.count(tmp.first) && !s2_set.count(tmp.second)) {
            matches[tmp.first] = tmp.second;
            s2_set.insert(tmp.second);
        }
        s.pop();
    }
    return matches;
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