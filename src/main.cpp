#include <iostream>
#include <fstream>
#include <string>

#include "SequenceAlignment.h"

/**
 * @brief: Read input from a given file
 * @param: filename
 * @param: strs: base strings
 * @param: indices: indices to generate a cumulative string
 **/
void ReadFile(const string &filename, vector<string> &strs, vector<vector<int>> &indices);

/**
 * @brief: Generate cumulative string
 * @param: base_str: base strings
 * @param: indices: indices to generate a cumulative string
 **/
string InputGenerator(const string &base_str, const vector<int> &indices);

int main(int argc, char **argv)
{
    // Read from file
    string input_file = "../data/data1.txt";       // input data file
    vector<string> strs;                           // base strings
    vector<vector<int>> indices(2, vector<int>()); // indices
    ReadFile(input_file, strs, indices);

    // Generate two cumulative strings
    string s1 = InputGenerator(strs[0], indices[0]);
    string s2 = InputGenerator(strs[1], indices[1]);
    cout << "String 1: " << s1 << endl;
    cout << "String 2: " << s2 << endl;

    // Compute OPT value table
    SequenceAlignment sa(s1, s2);
    sa.ComputeMinimumAlignmentCost();
    vector<vector<int>> OPT = sa.GetOptTable();
    cout << "OPT table: " << endl;
    for (int i = 0; i < OPT.size(); i++)
    {
        for (int j = 0; j < OPT[0].size(); j++)
        {
            cout << OPT[i][j] << " ";
        }
        cout << endl;
    }

    // Reconstruct alignment
    stack<pair<int, int>> alignment = sa.ReconstructAlignment();
    while (!alignment.empty())
    {
        pair<int, int> match = alignment.top();
        alignment.pop();
        cout << s1[match.first] << match.first << " - " << s2[match.second] << match.second << endl;
    }

    cout << "Exit Program..." << endl;
    return 0;
}

void ReadFile(const string &filename, vector<string> &strs, vector<vector<int>> &indices)
{
    // Open the input file
    ifstream inFile;
    inFile.open(filename);
    if (!inFile)
    {
        cout << "Unable to open file";
        exit(1); // terminate with error
    }

    // Extract base string and indices to form cumulative string
    string s;
    while (getline(inFile, s))
    {
        if (isalpha(s[0]))
        {
            // Add a base string
            strs.push_back(s);
            cout << "Base String " << strs.size() - 1 << ": " << s << endl;
        }
        else if (isdigit(s[0]))
        {
            // Add a series of indices
            if (strs.size() - 1 < 0)
            {
                continue;
            }
            else
            {
                cout << stoi(s) << endl;
                indices[strs.size() - 1].push_back(stoi(s));
            }
        }
    }

    // Close file
    inFile.close();
    return;
}

string InputGenerator(const string &base_str, const vector<int> &indices)
{
    string res = base_str;
    for (int index : indices)
    {
        if (index < 0)
        {
            index = 0;
        }
        else if (index > res.size() - 1)
        {
            index = res.size() - 1;
        }

        res = res.substr(0, index + 1) + res + res.substr(index + 1, res.size() - index - 1);
    }
    return res;
}
