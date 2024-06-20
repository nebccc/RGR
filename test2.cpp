#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <map>

using namespace std;

// Словари для шифрования и расшифровки на английском и русском языках
map<char, char> GramotaEng = {
    {'B', 'A'}, {'A', 'B'}, {'C', 'E'}, {'E', 'C'}, {'D', 'I'}, {'I', 'D'}, {'F', 'O'}, {'O', 'F'}, {'G', 'U'}, {'U', 'G'}, {'H', 'Y'}, {'Y', 'H'},
    {'J', 'Z'}, {'Z', 'J'}, {'K', 'X'}, {'X', 'K'}, {'L', 'W'}, {'W', 'L'}, {'M', 'V'}, {'V', 'M'}, {'N', 'T'}, {'T', 'N'}, {'P', 'S'}, {'S', 'P'},
    {'Q', 'R'}, {'R', 'Q'}, {' ', '#'}, {'b', 'a'}, {'a', 'b'}, {'c', 'e'}, {'e', 'c'}, {'d', 'i'}, {'i', 'd'}, {'f', 'o'}, {'o', 'f'}, {'g', 'u'},
    {'u', 'g'}, {'h', 'y'}, {'y', 'h'}, {'j', 'z'}, {'z', 'j'}, {'k', 'x'}, {'x', 'k'}, {'l', 'w'}, {'w', 'l'}, {'m', 'v'}, {'v', 'm'}, {'n', 't'},
    {'t', 'n'}, {'p', 's'}, {'s', 'p'}, {'q', 'r'}, {'r', 'q'}, {' ', '#'}
};

map<char, char> GramotaRus = {
    {'Б', 'А'}, {'А', 'Б'}, {'В', 'Е'}, {'Е', 'В'}, {'Г', 'Ё'}, {'Ё', 'Г'}, {'Д', 'И'}, {'И', 'Д'}, {'Ж', 'О'}, {'О', 'Ж'}, {'З', 'У'}, {'У', 'З'},
    {'К', 'Ы'}, {'Ы', 'К'}, {'Л', 'Э'}, {'Э', 'Л'}, {'М', 'Ю'}, {'Ю', 'М'}, {'Н', 'Я'}, {'Я', 'Н'}, {'П', 'Щ'}, {'Щ', 'П'}, {'Р', 'Ш'}, {'Ш', 'Р'},
    {'С', 'Ч'}, {'Ч', 'С'}, {'Т', 'Ц'}, {'Ц', 'Т'}, {'Ф', 'Х'}, {'Х', 'Ф'}, {'б', 'а'}, {'а', 'б'}, {'в', 'е'}, {'е', 'в'}, {'г', 'ё'}, {'ё', 'г'},
    {'д', 'и'}, {'и', 'д'}, {'ж', 'о'}, {'о', 'ж'}, {'з', 'у'}, {'у', 'з'}, {'к', 'ы'}, {'ы', 'к'}, {'л', 'э'}, {'э', 'л'}, {'м', 'ю'}, {'ю', 'м'},
    {'н', 'я'}, {'я', 'н'}, {'п', 'щ'}, {'щ', 'п'}, {'р', 'ш'}, {'ш', 'р'}, {'с', 'ч'}, {'ч', 'с'}, {'т', 'ц'}, {'ц', 'т'}, {'ф', 'х'}, {'х', 'ф'},
    {' ', '#'}
};

// Функция для шифрования текста
string encryptGramota(const string& text, map<char, char>& Gramota) {
    string encryptedGramota;
    for (char c : text) {
        if (Gramota.count(c)) {
            encryptedGramota += Gramota[c];
        } else {
            encryptedGramota += c;
        }
    }
    return encryptedGramota;
}

// Функция для расшифровки текста
string decryptGramota(const string& text, map<char, char>& Gramota) {
    string decryptedGramota;
    for (char c : text) {
        bool found = false;
        for (const auto& pair : Gramota) {
            if (pair.second == c) {
                decryptedGramota += pair.first;
                found = true;
                break;
            }
        }
        if (!found) {
            decryptedGramota += c;
        }
    }
    return decryptedGramota;
}

// Основная функция для взаимодействия с пользователем
void DisplayGramota() {
    while (true) {
        try {
            cout << "---------------------------------\n";
            cout << "Выберите язык :\n1. English\n2. Русский\n3. Назад\n";
            cout << "---------------------------------\n";
            string ChoiceGramota;
            getline(cin, ChoiceGramota);

            if (ChoiceGramota != "1" && ChoiceGramota != "2" && ChoiceGramota != "3") {
                throw invalid_argument("Неправильная команда. Нужно чтобы команда состояла из 1 символа: '1', '2' или '3'. Попробуйте еще раз.\n");
            }

            int Choice = stoi(ChoiceGramota);
            if (Choice == 3) {
                cout << "---------------------------------\n";
                break;
            }

            string inputTextGramota;
            cout << "Введите текст для шифрования: ";
            getline(cin >> ws, inputTextGramota);
            cout << "---------------------------------\n";

            ofstream outputFile("encryptedGramota.txt");
            if (!outputFile.is_open()) {
                throw runtime_error("Не удалось открыть файл для записи.\n");
            }

            string encryptedTextGramota;
            switch (Choice) {
            case 1:
                encryptedTextGramota = encryptGramota(inputTextGramota, GramotaEng);
                break;
            case 2:
                encryptedTextGramota = encryptGramota(inputTextGramota, GramotaRus);
                break;
            }

            outputFile << encryptedTextGramota;
            outputFile.close();
            cout << "Зашифрованный текст сохранен в файл encryptedGramota.txt\n";
            cout << "Зашифрованный текст: " << encryptedTextGramota << "\n";
            cout << "---------------------------------\n";

            ifstream inputFile("encryptedGramota.txt");
            if (!inputFile.is_open()) {
                throw runtime_error("Не удалось открыть файл для чтения.\n");
            }

            string decryptedTextGramota;
            getline(inputFile, encryptedTextGramota);
            inputFile.close();

            switch (Choice) {
            case 1:
                decryptedTextGramota = decryptGramota(encryptedTextGramota, GramotaEng);
                break;
            case 2:
                decryptedTextGramota = decryptGramota(encryptedTextGramota, GramotaRus);
                break;
            }

            cout << "---------------------------------\n";
            cout << "Расшифрованный текст: " << decryptedTextGramota << "\n";
            cout << "---------------------------------\n";

            ofstream decryptFile("decryptGramota.txt");
            if (!decryptFile.is_open()) {
                throw runtime_error("Не удалось открыть файл для записи.\n");
            }

            decryptFile << decryptedTextGramota;
            decryptFile.close();
            cout << "Расшифрованный текст сохранен в файл decryptGramota.txt\n";
            cout << "---------------------------------\n";

        } catch (const invalid_argument& e) {
            cerr << "Ошибка: " << e.what() << "\n";
        } catch (const runtime_error& e) {
            cerr << "Ошибка: " << e.what() << "\n";
        }
    }
}

int main() {
    DisplayGramota();
    return 0;
}