#include "../include/box.h"

#include <algorithm>
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cctype>

using namespace std;

pair<string, string> init_encrypted() {
    string choice;
    string key, text;

    while(true) {
        cout << "Хотите ввести данные вручную или прочитать из файла? (Да/Нет) : ";
        getline(cin, choice);

        transform(choice.begin(), choice.end(), choice.begin(),
            [](unsigned char c) {return tolower(c); });


        if(choice == "да" || choice == "yes" || choice == "д" || choice == "y"){
            string key_file_path, text_file_path;

            cout << "Введите путь к файлу с ключом: ";
            getline(cin, key_file_path);

            cout << "Введите путь к файлу с текстом: ";
            getline(cin, text_file_path);

            ifstream key_file(key_file_path);
            ifstream text_file(text_file_path);

            while ((!key_file.is_open() || !text_file.is_open()))
            {
                cerr << "Ошибка открытия файла. Пожалуйста, проверьте пути и повторите попытку." << endl;
                cout << "Выход (q)" << endl;

                cout << "Путь к файлу с ключом:";
                getline(cin, key_file_path);

                cout << "Путь к файлу с текстом: ";
                getline(cin, text_file_path);
                
                ifstream key_file(key_file_path);
                ifstream text_file(text_file_path);
            }

            getline(key_file, key);
            getline(text_file, text);

            key_file.close();
            text_file.close();

            if (key.length() > 16) {
                cerr << "Длина ключа больше чем 16 символов. Пожалуйста, проверьте содержимое файла с ключом." << endl;
                exit(EXIT_FAILURE);
            }

            else {
                break;
            }
        }

        else {
            while (true) {
                cout << "Введите ключь длиной не больше 16 символов: ";
                getline(cin, key);
                
                if (key.length() > 16) {
                    cout << "Длина ключа больше чем 16 символов. \nВведите ключ: ";
                    getline(cin, key);
                } else {
                    break;
                }
            }

            cout << "Введите текст: ";
            getline(cin, text);

            break;
        }
    }

    return {key, text};
}

pair<string, string> init_decrypt() {
    string input_key, ciphertext;
    
    cout << "Введите ключ длиной не больше 16 символов: ";

    while (true) {
        getline(cin, input_key);

        if (input_key.length() > 16) {
            cout << "Длина ключа больше чем 16 символов. \nВведите ключ: ";
        }
         
        else {
            break;
        }
    }

    ifstream inputFile("ciphertext.txt", ios::binary);
    if (inputFile.is_open()) {
        unsigned char ch;
        while (inputFile.read(reinterpret_cast<char*>(&ch), sizeof(ch))) {
            ciphertext.push_back(ch);
        }

        inputFile.close();
    } 
    
    else {
        cout << "Не удалось открыть файл для чтения" << endl;
    }

    return {input_key, ciphertext};
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
            int index = i * 4 + j;
            if (index < input_key.length()) {
                key_matrix[i][j] = input_key[index];
            }
        }
    }

    return {key_matrix, message};
}

void transpose_matrix(vector<vector<unsigned char>>& matrix) {
    int n = matrix.size();
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
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
    int n = matrix1.size();
    vector<vector<unsigned char>> result(n, vector<unsigned char>(n));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            result[i][j] = matrix1[i][j] ^ matrix2[i][j];
        }
    }

    return result;
}

void print_matrix_hex(const vector<vector<unsigned char>>& matrix) {
    for (const auto& row : matrix) {
        for (unsigned char value : row) {
            printf("%02X ", value);
        }
        cout << "\n";
    }

    cout << "\n\n";
}