#include <iostream>
#include <vector>
#include <algorithm>
#include <cctype>
#include <string>

using namespace std;

ostream& operator<<(ostream& os, const vector<int>& aboba) {
    for (int i = 0; i < aboba.size(); i++) {
        os << aboba[i] << " ";
    }
    return os;
}

istream& operator>>(istream& is, vector<int>& aboba) {
    int size;
    cout << "Введите количество элементов: ";
    is >> size;
    
    aboba.resize(size);  // Изменяем размер вектора

    for (int i = 0; i < size; i++) {
        is >> aboba[i];  // Считываем каждый элемент
    }

    cout << endl;

    return is;
}

vector<int> operator+(const vector<int> vec1, const vector<int> vec2) {
    vector<int> result(vec1.size());

    for(int i = 0; i < vec1.size(); i++) {
        result[i] = vec1[i] + vec2[i];
    }

    return result;
}

vector<int> operator-(const vector<int> vec1, const vector<int> vec2) {
    vector<int> result;
    result.resize(vec1.size());

    for(int i = 0; i < result.size(); i++) {
        result[i] = vec1[i] - vec2[i];
    }

    return result;
}

int gcd(int a, int b) {
    if(b == 0) return a;

    return(b, a % b);
}

void printCont(vector<int>& aboba) {
    for(auto it = aboba.begin(); it != aboba.end(); it++) {
        cout << *it << " ";
    }
}


int main() {
    string text;
    getline(cin, text);

    transform(text.begin(), text.end(), text.begin(),
            [](unsigned char c) {return tolower(c); });

    cout << text << endl;
    
    return 0;
}