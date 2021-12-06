#ifndef SEQUENCEALIGNMENT_UTILITY_H
#define SEQUENCEALIGNMENT_UTILITY_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
// #include <filesystem>

using namespace std;
// namespace fs = std::filesystem;

/**
 * @brief: Read input from a given file
 * @param: filename
 * @param: strs: base strings
 * @param: indices: indices to generate a cumulative string
 **/
void ReadFile(const string& filename, vector<string>& strs, vector<vector<int>>& indices);

/**
 * @brief Write output into a file
 * @param filename
 * @param alignment
 * @param opt_value
 * @param time
 */
void WriteFile(const string& filename, const vector<pair<char, char>>& alignment, int opt_value);

/**
 * @brief: Generate cumulative string
 * @param: base_str: base strings
 * @param: indices: indices to generate a cumulative string
 **/
string InputGenerator(const string& base_str, const vector<int>& indices);

/**
 * @brief Generate output filename based on input file name
 * @param input_file input filename
 * @return output filename
 */
// string OutputGenerator(string& program, string& input_file);

#endif
