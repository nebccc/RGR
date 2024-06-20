#include <iostream>
#include <limits>
#include <stdexcept>
#include "AES/include/aes128_encrypted.h"
#include "AES/include/aes128_decrypt.h"
#include "Littera/include/littera.h"
#include "Hughes/include/hughes.h"

using namespace std;

#define password "1423"

bool login() {
    string input_password;

    try {
        cout << "Введите пароль: ";
        getline(cin, input_password);

        if (input_password == password) {
            return true;
        } else {
            throw runtime_error("Пароль неверный!");
        }
    } catch (const runtime_error& e) {
        cout << e.what() << endl;
        return false;
    } catch (const exception& e) {
        cout << "Ошибка: " << e.what() << endl;
        return false;
    }
}

int getChoice(int min, int max) {
    int choice;
    cout << "Введите выбор: ";
    while (!(cin >> choice) || choice < min || choice > max) {
        cout << "Ошибка: Неверный выбор. Пожалуйста, введите число от " << min << " до " << max << ": ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return choice;
}

void aes_menu() {
    try {
        cout << "1 - Закодировать" << endl;
        cout << "2 - Расскодировать" << endl;
        cout << "3 - Выйти" << endl;

        int choice = getChoice(1, 3);

        printf("\033[2J");
        printf("\033[0;0f");

        switch (choice) {
            case 1:
                aes_encrypted();
                break;
            case 2:
                aes_decrypt();
                break;
            case 3:
                return;
            default:
                throw runtime_error("Неверный выбор!");
        }
    } catch (const runtime_error& e) {
        cout << e.what() << endl;
    } catch (const exception& e) {
        cout << "Ошибка: " << e.what() << endl;
    }
}

void littera_menu() {
    try {
        cout << "1 - Закодировать" << endl;
        cout << "2 - Расскодировать" << endl;
        cout << "3 - Выйти" << endl;

        int choice = getChoice(1, 3);

        printf("\033[2J");
        printf("\033[0;0f");

        switch (choice) {
            case 1:
            case 2:
                littera();
                break;
            case 3:
                return;
            default:
                throw runtime_error("Неверный выбор!");
        }
    } catch (const runtime_error& e) {
        cout << e.what() << endl;
    } catch (const exception& e) {
        cout << "Ошибка: " << e.what() << endl;
    }
}

void hughes_menu() {
    try {
        cout << "1 - Закодировать" << endl;
        cout << "2 - Расскодировать" << endl;
        cout << "3 - Выйти" << endl;

        int choice = getChoice(1, 3);

        printf("\033[2J");
        printf("\033[0;0f");

        switch (choice) {
            case 1:
            case 2:
                huges();
                break;
            case 3:
                return;
            default:
                throw runtime_error("Неверный выбор!");
        }
    } catch (const runtime_error& e) {
        cout << e.what() << endl;
    } catch (const exception& e) {
        cout << "Ошибка: " << e.what() << endl;
    }
}

void menu() {
    try {
        while (true) {
            cout << "1 - AES128" << endl;
            cout << "2 - Тарабарская грамота" << endl;
            cout << "3 - Hughes" << endl;
            cout << "4 - Выйти" << endl;

            int choice = getChoice(1, 4);

            printf("\033[2J");
            printf("\033[0;0f");

            switch (choice) {
                case 1:
                    aes_menu();
                    break;
                case 2:
                    littera_menu();
                    break;
                case 3:
                    hughes_menu();
                    break;
                case 4:
                    return;
                default:
                    throw runtime_error("Неверный выбор!");
            }
        }
    } catch (const runtime_error& e) {
        cout << e.what() << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } catch (const exception& e) {
        cout << "Ошибка: " << e.what() << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

int main() {
    try {
        bool log = login();

        if (log) {
            menu();
        }
    } catch (const exception& e) {
        cout << "Ошибка в основной функции: " << e.what() << endl;
    }

    return 0;
}