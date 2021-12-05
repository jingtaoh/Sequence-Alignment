#include "SequenceAlignment.h"
#include "utility.h"

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

    auto alignment = sa.DivideAndConquerAlignment(s1, s2);

    // Generate output filename
    string output_file = OutputGenerator(program, input_file);

    WriteFile(output_file, alignment);
    return 0;
}