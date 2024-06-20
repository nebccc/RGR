#pragma once

#include <algorithm>
#include <string>
#include <iostream>
#include <vector>
#include <fstream>

#include "aes128_common.h"
#include "box.h"

using namespace std;

void invSubBytes(vector<vector<unsigned char>>& matrix);
void invShiftRows(vector<vector<unsigned char>>& state);
unsigned char gmul(unsigned char a, unsigned char b);
void invMixColumns(vector<vector<unsigned char>>& state);
void aes_decrypt();