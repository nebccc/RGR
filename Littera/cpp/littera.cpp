#include <iostream>
#include <string>
#include <map>
#include <locale>
#include <algorithm>
#include <cctype>
#include <fstream>

using namespace std;

map<char, char> ru_alphabet = {
    {'б', 'а'}, {'в', 'е'}, {'г', 'ё'}, {'д', 'и'}, {'ж', 'о'},
    {'з', 'у'}, {'к', 'ы'}, {'л', 'э'}, {'м', 'ю'}, {'н', 'я'}, 
    {'п', 'щ'}, {'р', 'ш'}, {'с', 'ч'}, {'т', 'ц'}, {'ф', 'х'},

    {'а', 'б'}, {'е', 'в'}, {'ё', 'г'}, {'и', 'д'}, {'о', 'ж'},
    {'у', 'з'}, {'ы', 'к'}, {'э', 'л'}, {'ю', 'м'}, {'я', 'н'}, 
    {'щ', 'п'}, {'ш', 'р'}, {'ч', 'с'}, {'т', 'ц'}, {'х', 'ф'},

    {' ', '#'}, {'#', ' '}
};

map<char, char> eng_alphabet = {
    {'a', 'b'}, {'b', 'c'}, {'c', 'd'}, {'d', 'e'}, {'e', 'f'},
    {'f', 'g'}, {'g', 'h'}, {'h', 'i'}, {'i', 'j'}, {'j', 'k'},
    {'k', 'l'}, {'l', 'm'}, {'m', 'n'}, {'n', 'o'}, {'o', 'p'},
    {'p', 'q'}, {'q', 'r'}, {'r', 's'}, {'s', 't'}, {'t', 'u'},
    {'u', 'v'}, {'v', 'w'}, {'w', 'x'}, {'x', 'y'}, {'y', 'z'},
    {'z', 'a'},

    {'A', 'B'}, {'B', 'C'}, {'C', 'D'}, {'D', 'E'}, {'E', 'F'},
    {'F', 'G'}, {'G', 'H'}, {'H', 'I'}, {'I', 'J'}, {'J', 'K'},
    {'K', 'L'}, {'L', 'M'}, {'M', 'N'}, {'N', 'O'}, {'O', 'P'},
    {'P', 'Q'}, {'Q', 'R'}, {'R', 'S'}, {'S', 'T'}, {'T', 'U'},
    {'U', 'V'}, {'V', 'W'}, {'W', 'X'}, {'X', 'Y'}, {'Y', 'Z'},
    {'Z', 'A'},

    {' ', '#'}, {'#', ' '}
};

string init_littera() {
    string choice, text;

    cout << "Хотите считать данные сфайла: (Да/Нет): ";
    getline(cin, choice);

    transform(choice.begin(), choice.end(), choice.begin(),
        [](unsigned char c) {return tolower(c); });
    
    if(choice == "да" || choice == "yes" || choice == "д" || choice == "y") {
        string text_file_path;

        cout << "Введите путь к файлу с текстом: ";
        getline(cin, text_file_path);

        ifstream text_file(text_file_path);

        while((!text_file.is_open())) {
            cerr << "Ошибка открытия файла. Пожалуйста, проверьте пути и повторите попытку." << endl;

            cout << "Путь к файлу с текстом: ";
            getline(cin, text_file_path);

            ifstream text_file(text_file_path);
        }

        getline(text_file, text);

        text_file.close();
    }

    else{
        cout << "Введите текст: ";
        getline(cin, text);
    }

    return text;
}

void write_text(const string& text) {
    string choice;

    cout << "Хотите записать результат в файл? (Да/Нет) : ";
    getline(cin, choice);

    transform(choice.begin(), choice.end(), choice.begin(),
        [](unsigned char c) {return tolower(c); });

    if(choice == "да" || choice == "yes" || choice == "д" || choice == "y") {
        string file_path;

        cout << "Введите путь куда сохранить текст: ";
        getline(cin, file_path);

        ofstream file(file_path);
        if (file.is_open()) {
            file << text;
            
            file.close();
            cout << "Текст успешно записан в файл." << endl;


        } 
        
        else {
            cout << "Не удалось открыть файл." << endl;
        }
    }
}

void littera() {
    setlocale(LC_ALL, "");

    string text = init_littera();

    for (char& ch : text) {
        if (ru_alphabet.find(ch) != ru_alphabet.end()) {
            ch = ru_alphabet[ch];
        }
        
        else if(eng_alphabet.find(ch) != eng_alphabet.end()) {
            ch = eng_alphabet[ch];
        }
    }

    cout << "Результат: " << text << endl;
    
    write_text(text);
}