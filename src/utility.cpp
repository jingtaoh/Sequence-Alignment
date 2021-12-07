#include "utility.h"

void ReadFile(const string& filename, vector<string>& strs, vector<vector<int>>& indices)
{
    // Open the input file
    ifstream inFile;
    inFile.open(filename);
    if (!inFile) {
        cout << "Unable to open file";
        exit(1); // terminate with error
    }

    // Extract base string and indices to form cumulative string
    string s;
    while (getline(inFile, s)) {
        if (isalpha(s[0])) {
            // Add a base string
            strs.push_back(s);
            // cout << "Base String " << strs.size() - 1 << ": " << s << endl;
        } else if (isdigit(s[0])) {
            // Add a series of indices
            if (strs.size() - 1 < 0) {
                continue;
            } else {
                // cout << stoi(s) << endl;
                indices[strs.size() - 1].push_back(stoi(s));
            }
        }
    }

    // Close file
    inFile.close();
    return;
}

void WriteFile(const string& filename, const vector<pair<char, char>>& alignment, int opt_value)
{
    ofstream outFile{filename};

    if (!outFile) {
        cout << filename << " could not be opened for writing";
        exit(1); // terminate with error
    }

    //    // Output alignment
    //    for (int i = alignment.size() - 1; i >= 0; i--) {
    //        outFile << alignment[i].first;
    //    }
    //    outFile << endl;
    //    for (int i = alignment.size() - 1; i >= 0; i--) {
    //        outFile << alignment[i].second;
    //    }
    //    outFile << endl;

    // Output The first 50 elements of the 1st string
    for (int i = alignment.size() - 1; i >= max(int(alignment.size() - 1 - 50), 0); i--) {
        outFile << alignment[i].first;
    }
    outFile << " ";
    // Output The last 50 elements of the 1st string
    for (int i = min(int(alignment.size() - 1), 50); i >= 0; i--) {
        outFile << alignment[i].first;
    }
    outFile << endl;

    // Output The first 50 elements of the 2nd string
    for (int i = alignment.size() - 1; i >= max(int(alignment.size() - 1 - 50), 0); i--) {
        outFile << alignment[i].second;
    }
    outFile << " ";
    // Output The last 50 elements of the 2nd string
    for (int i = min(int(alignment.size() - 1), 50); i >= 0; i--) {
        outFile << alignment[i].second;
    }
    outFile << endl;

    // Print OPT value
    outFile << opt_value << endl;
}

string InputGenerator(const string& base_str, const vector<int>& indices)
{
    string res = base_str;
    for (int index : indices) {
        if (index < 0) {
            index = 0;
        } else if (index > res.size() - 1) {
            index = res.size() - 1;
        }

        res = res.substr(0, index + 1) + res + res.substr(index + 1, res.size() - index - 1);
    }
    return res;
}

string OutputGenerator(string& program, string& input_file)
{
    program = program.substr(program.find_last_of("/\\") + 1);
    string output_file = input_file.replace(input_file.find("input"), 5, "output");
    output_file.insert(output_file.find(".txt"), '_' + program);
    return output_file;
}
