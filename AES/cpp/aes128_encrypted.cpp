#include "../include/aes128_common.h"
#include "../include/box.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

void sub_bytes(vector<vector<unsigned char>>& matrix) {
    for (int i = 0; i < 4; i++) { 
        for (int j = 0; j < 4; j++) {
            matrix[i][j] = sBox[matrix[i][j] / 16][matrix[i][j] % 16];
        }
    }
}

void shiftRows(vector<vector<unsigned char>>& state) {
    for (int i = 1; i < 4; ++i) {
        rotate(state[i].begin(), state[i].begin() + i, state[i].end());
    }
}

void mixColumns(vector<vector<unsigned char>>& state) {
    for (int i = 0; i < 4; ++i) {
        unsigned char a[4];
        unsigned char b[4];
        unsigned char h;

        for (int c = 0; c < 4; ++c) {
            a[c] = state[c][i];
            h = (unsigned char)((signed char)state[c][i] >> 7);
            b[c] = state[c][i] << 1;
            b[c] ^= 0x1B & h;
        }

        state[0][i] = b[0] ^ a[1] ^ b[1] ^ a[2] ^ a[3];
        state[1][i] = a[0] ^ b[1] ^ a[2] ^ b[2] ^ a[3];
        state[2][i] = a[0] ^ a[1] ^ b[2] ^ a[3] ^ b[3];
        state[3][i] = a[0] ^ b[0] ^ a[1] ^ a[2] ^ b[3];
    }
}

void wride_ciphertext(vector<unsigned char> ciphertext) {
    ofstream outputFile("ciphertext.txt");
    if (outputFile.is_open()) {
        for (unsigned char ch : ciphertext) {
            outputFile << ch;
        }

        outputFile.close();

        cout << "Зашифрованный текст успешно записан в файл ciphertext.txt" << endl;
    }
}

void aes_encrypted() {
    string input_key, input_message;

    tie(input_key, input_message) = init_encrypted();

    vector<vector<unsigned char>> key_matrix;
    vector<vector<vector<unsigned char>>> message_matrices;

    tie(key_matrix, message_matrices) = create_matrices(input_message, input_key);

    vector<vector<vector<unsigned char>>> extended_keys;

    key_expansion(key_matrix, extended_keys);

    for (int i = 0; i < 10; i++) {
        transpose_matrix(extended_keys[i]);
    }

    transpose_matrix(key_matrix);

    for (int i = 0; i < message_matrices.size(); i++) {
        transpose_matrix(message_matrices[i]);
    }

    vector<unsigned char> ciphertext;

    for (int i = 0; i < message_matrices.size(); i++) {
        vector<vector<unsigned char>> result_matrix = xor_matrices(key_matrix, message_matrices[i]);

        for (int j = 0; j < 9; j++) {
            sub_bytes(result_matrix);
            shiftRows(result_matrix);
            mixColumns(result_matrix);

            result_matrix = xor_matrices(result_matrix, extended_keys[j]);
        }

        sub_bytes(result_matrix);
        shiftRows(result_matrix);

        result_matrix = xor_matrices(result_matrix, extended_keys[9]);

        transpose_matrix(result_matrix);

        for (const auto& row : result_matrix) {
            for (const auto ch : row) {
                ciphertext.push_back(ch);
            }
        }
    }
    
    cout << "Зашифрованное сообщение: ";
    for(char ch : ciphertext) {
        cout << ch;
    }

    cout << endl;

    wride_ciphertext(ciphertext);
}