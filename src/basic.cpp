#include "utility.h"
#include "SequenceAlignment.h"

int main(int argc, char** argv)
{
    // Read from file
    string program = argv[0];
    string input_file = argv[1]; // input data file
    vector<string> strs; // base strings
    vector<vector<int>> indices(2, vector<int>()); // indices
    ReadFile(input_file, strs, indices);

    // Generate two cumulative strings
    string s1 = InputGenerator(strs[0], indices[0]);
    string s2 = InputGenerator(strs[1], indices[1]);

    // Define object
    SequenceAlignment sa;

    // Compute OPT value table
    auto OPT_table = sa.ComputeMinimumAlignmentCost(s1, s2);
    int OPT_value = OPT_table[OPT_table.size() - 1][OPT_table[0].size() - 1];

    // Reconstruct alignment
    auto alignment = sa.ReconstructAlignment(OPT_table, s1, s2);

    // Generate output filename
    string output_file = OutputGenerator(program, input_file);

    WriteFile(output_file, alignment, OPT_value);
    return 0;
}