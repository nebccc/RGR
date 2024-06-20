#pragma once

#include <algorithm>
#include <string>
#include <iostream>
#include <vector>
#include <fstream>

#include "aes128_common.h"
#include "box.h"

using namespace std;

void sub_bytes(vector<vector<unsigned char>>& matrix);
void shiftRows(vector<vector<unsigned char>>& state);
void mixColumns(vector<vector<unsigned char>>& state);
void wride_ciphertext(vector<unsigned char> ciphertext);
void aes_encrypted();