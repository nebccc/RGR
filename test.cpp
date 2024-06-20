#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

#include "box.h"

using namespace std;

// Функция для инициализации ввода
pair<string, string> init() {
    string input_key, input_message;
    
    cout << "Введите ключ длиной не больше 16 символов: ";
    
    while (true) {
        getline(cin, input_key);

        if (input_key.length() > 16) {
            cout << "Длина ключа больше чем 16 символов. \nВведите ключ: ";
        } else {
            break;
        }
    }

    cout << "Введите сообщение: ";
    getline(cin, input_message);

    return {input_key, input_message};
}

// Функция для создания матриц из ключа и сообщения
pair<vector<vector<unsigned char>>, vector<vector<vector<unsigned char>>>> create_matrices(const string& input_message, const string& input_key) {
    vector<vector<vector<unsigned char>>> message;
    vector<vector<unsigned char>> matrix(4, vector<unsigned char>(4, 0));

    size_t position = 0;

    // Создание матриц из сообщения
    while (position < input_message.length()) {
        for (int i = 0; i < 4 && position < input_message.size(); ++i) {
            for (int j = 0; j < 4 && position < input_message.size(); ++j) {
                matrix[i][j] = input_message[position++];
            }
        }
        message.push_back(matrix);
    }

    // Создание матрицы из ключа
    vector<vector<unsigned char>> key_matrix(4, vector<unsigned char>(4, 0));

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            int index = i * 4 + j;#include <iostream>

#include "AES/include/aes128_encrypted.h"
#include "AES/include/aes128_decrypt.h"
            if (index < input_key.length()) {
                key_matrix[i][j] = input_key[index];
            }
        }
    }

    return {key_matrix, message};
}

void transpose_matrix(vector<vector<unsigned char>>& matrix) {
    for (int i = 0; i < 4; ++i) {
        for (int j = i + 1; j < 4; ++j) {
            swap(matrix[i][j], matrix[j][i]);
        }
    }
}

void key_expansion(vector<vector<unsigned char>>& key_matrix, vector<vector<vector<unsigned char>>>& extended_keys) {
    vector<vector<unsigned char>> exp_key;
    vector<vector<unsigned char>> state;

    for (const auto& row : key_matrix) {
        exp_key.push_back(row);
        state.push_back(row);
    }

    for (int j = 0; j < 10; j++) {
        rotate(state[3].begin(), state[3].begin() + 1, state[3].end());

        for (int i = 0; i < 4; i++) {
            state[3][i] = sBox[state[3][i] / 16][state[3][i] % 16];
            state[3][i] = state[3][i] ^ r_w[j][i];

            exp_key[0][i] = exp_key[0][i] ^ state[3][i];
            exp_key[1][i] = exp_key[0][i] ^ state[1][i];
            exp_key[2][i] = exp_key[1][i] ^ state[2][i];
            exp_key[3][i] = exp_key[2][i] ^ exp_key[3][i];
        }

        extended_keys.push_back(exp_key);

        state = exp_key;
    }
}

vector<vector<unsigned char>> xor_matrices(const vector<vector<unsigned char>>& matrix1, const vector<vector<unsigned char>>& matrix2) {
    vector<vector<unsigned char>> result(4, vector<unsigned char>(4));

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result[i][j] = matrix1[i][j] ^ matrix2[i][j];
        }
    }

    return result;
}

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

int main() {
    string input_key, input_message;

    tie(input_key, input_message) = init();

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

    wride_ciphertext(ciphertext);

    return 0;
}