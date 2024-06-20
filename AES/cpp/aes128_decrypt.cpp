#include "../include/aes128_common.h"
#include "../include/box.h"

#include <algorithm>
#include <string>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

void invSubBytes(vector<vector<unsigned char>>& matrix) {
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            matrix[i][j] = invsBox[matrix[i][j] / 16][matrix[i][j] % 16];
        }
    }
}

void invShiftRows(vector<vector<unsigned char>>& state) {
    for (int i = 1; i < 4; ++i) {
        rotate(state[i].rbegin(), state[i].rbegin() + i, state[i].rend());
    }
}

unsigned char gmul(unsigned char a, unsigned char b) {
    unsigned char p = 0;
    unsigned char counter;
    unsigned char hi_bit_set;
    for (counter = 0; counter < 8; counter++) {
        if (b & 1) {
            p ^= a;
        }
        hi_bit_set = (a & 0x80);
        a <<= 1;
        if (hi_bit_set) {
            a ^= 0x1b;
        }
        b >>= 1;
    }
    return p;
}

void invMixColumns(vector<vector<unsigned char>>& state) {
    for (int i = 0; i < 4; ++i) {
        unsigned char a[4];
        unsigned char b[4];

        for (int c = 0; c < 4; ++c) {
            a[c] = state[c][i];
        }

        b[0] = gmul(a[0], 0x0e) ^ gmul(a[1], 0x0b) ^ gmul(a[2], 0x0d) ^ gmul(a[3], 0x09);
        b[1] = gmul(a[0], 0x09) ^ gmul(a[1], 0x0e) ^ gmul(a[2], 0x0b) ^ gmul(a[3], 0x0d);
        b[2] = gmul(a[0], 0x0d) ^ gmul(a[1], 0x09) ^ gmul(a[2], 0x0e) ^ gmul(a[3], 0x0b);
        b[3] = gmul(a[0], 0x0b) ^ gmul(a[1], 0x0d) ^ gmul(a[2], 0x09) ^ gmul(a[3], 0x0e);

        for (int c = 0; c < 4; ++c) {
            state[c][i] = b[c];
        }
    }
}

void aes_decrypt() {
    string input_key, ciphertext;
    tie(input_key, ciphertext) = init_decrypt();

    vector<vector<unsigned char>> key_matrix;
    vector<vector<vector<unsigned char>>> ciphertext_matrices;

    tie(key_matrix, ciphertext_matrices) = create_matrices(ciphertext, input_key);

    vector<vector<vector<unsigned char>>> extended_keys;

    extended_keys.push_back(key_matrix);
    key_expansion(key_matrix, extended_keys);

    for (int i = 0; i <= 10; i++) {
        transpose_matrix(extended_keys[i]);
    }

    transpose_matrix(key_matrix);

    for (int i = 0; i < ciphertext_matrices.size(); i++) {
        transpose_matrix(ciphertext_matrices[i]);
    }

    vector<unsigned char> plaintext;

    for (int i = 0; i < ciphertext_matrices.size(); i++) {
        vector<vector<unsigned char>> result_matrix = xor_matrices(extended_keys[10], ciphertext_matrices[i]);

        for (int j = 9; j > 0; j--) {
            invShiftRows(result_matrix);
            invSubBytes(result_matrix);

            result_matrix = xor_matrices(result_matrix, extended_keys[j]);

            invMixColumns(result_matrix);

        }

        invShiftRows(result_matrix);
        invSubBytes(result_matrix);

        result_matrix = xor_matrices(result_matrix, extended_keys[0]);

        transpose_matrix(result_matrix);

        for (const auto& row : result_matrix) {
            for (const auto ch : row) {
                plaintext.push_back(ch);
            }
        }
    }

    cout << "Расшифрованное сообщение: ";
    for(char ch : plaintext) {
        cout << ch;
    }
    cout << endl;

    ofstream outputFile("decrypted_message.txt");
    if (outputFile.is_open()) {
        for (unsigned char ch : plaintext) {
            outputFile << ch;
        }
        outputFile.close();
        cout << "Расшифрованный текст успешно записан в файл decrypted_message.txt" << endl;
    }
    
    else {
        cout << "Не удалось открыть файл для записи" << endl;
    }
}