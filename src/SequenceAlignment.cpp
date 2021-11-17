#include "SequenceAlignment.h"

SequenceAlignment::SequenceAlignment(const string& s1, const string& s2)
    : gap_penalty_(30)
{
    s1_ = s1;
    s2_ = s2;
    InitializePenaltyTable(mismatch_penalty_table_);

    OPT_.resize(s1_.size() + 1);
    for (int i = 0; i <= s1_.size(); i++) {
        OPT_[i].resize(s2_.size() + 1);
    }
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

void SequenceAlignment::ComputeMinimumAlignmentCost()
{
    int m = s1_.size() + 1; // OPT table's row
    int n = s2_.size() + 1; // OPT table's col

    // Initialize edge case
    OPT_[0][0] = 0;
    for (int i = 1; i < m; i++) {
        OPT_[i][0] = i * gap_penalty_;
    }
    for (int i = 1; i < n; i++) {
        OPT_[0][i] = i * gap_penalty_;
    }

    // DP formula bottom-up
    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            OPT_[i][j] =
                min(OPT_[i - 1][j - 1] + mismatch_penalty_table_[s1_[i - 1]][s2_[j - 1]],
                    min(OPT_[i - 1][j] + gap_penalty_, OPT_[i][j - 1] + gap_penalty_));
        }
    }

    return;
}

vector<vector<int>> SequenceAlignment::GetOptTable()
{
    return vector<vector<int>>(OPT_);
}

stack<pair<int, int>> SequenceAlignment::ReconstructAlignment()
{
    int i = s1_.size();
    int j = s2_.size();

    stack<pair<int, int>> alignment;

    while (i > 0 && j > 0) {
        // s1[i] is matched with s2[j]
        if ((i - 1) >= 0 && (j - 1) >= 0 &&
            OPT_[i][j] == OPT_[i - 1][j - 1] + mismatch_penalty_table_[s1_[i - 1]][s2_[j - 1]]) {
            alignment.push({i - 1, j - 1});
            i--;
            j--;
        }

        // skip s1[i]
        if ((i - 1) >= 0 && OPT_[i][j] == OPT_[i - 1][j] + gap_penalty_) {
            i--;
        }

        // skip s2[j]
        if (j - 1 >= 0 && OPT_[i][j] == OPT_[i][j - 1] + gap_penalty_) {
            j--;
        }
    }
    return alignment;
}