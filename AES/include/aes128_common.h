#pragma once

#include <algorithm>
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cctype>

using namespace std;

pair<string, string> init_encrypted();
pair<string, string> init_decrypt();
pair<vector<vector<unsigned char>>, vector<vector<vector<unsigned char>>>> create_matrices(const string& input_message, const string& input_key);
void transpose_matrix(vector<vector<unsigned char>>& matrix);
void key_expansion(vector<vector<unsigned char>>& key_matrix, vector<vector<vector<unsigned char>>>& extended_keys);
vector<vector<unsigned char>> xor_matrices(const vector<vector<unsigned char>>& matrix1, const vector<vector<unsigned char>>& matrix2);
void print_matrix_hex(const vector<vector<unsigned char>>& matrix);