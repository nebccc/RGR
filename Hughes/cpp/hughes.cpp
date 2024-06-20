#include <iostream>
#include <string>
#include <random>
#include <tuple>
#include <cmath>
#include <cstdint>

using namespace std;

// Declare isPrime function
bool isPrime(int n);

pair<int64_t, int64_t> init() {
    int64_t a, p;

    cout << "Введите значения (a) и модуля (p): ";

    while (true) {
        cin >> a >> p;

        if (a < p && p < pow(2, 1024)) {
            if (isPrime(p)) {
                break;
            } else {
                cout << "Не подходит под параметры выполнения алгоритма" << endl;
            }
        } else {
            cout << "Не подходит под параметры выполнения алгоритма" << endl;
        }
    }

    return make_pair(a, p);
}

bool isPrime(int n) {
    if (n <= 1) return false; // 1 и меньшие числа не являются простыми

    // Проверяем делители от 2 до sqrt(n)
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) {
            // Если число делится без остатка, то оно не простое
            return false;
        }
    }

    return true; // Если не нашлось делителей, то число простое
}

int64_t rn(int64_t p) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int64_t> dist(1, p - 1);

    int64_t num = dist(gen);

    return num;
}

int64_t gcd(int64_t a, int64_t b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int64_t f(int64_t x, int64_t y, int64_t n, int64_t r) {
    if (y == 0) return r;
    if (y & 0x01) return f((x * x) % n, y >> 1, n, (r * x) % n);
    return f((x * x) % n, y >> 1, n, r);
}

int64_t powMod(int64_t x, int64_t y, int64_t n) {
    return f(x, y, n, 1);
}

// Расширенный алгоритм Евклида
int64_t extendedEuclidean(int64_t a, int64_t b, int64_t& x, int64_t& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }

    int64_t x1, y1;
    int64_t gcd = extendedEuclidean(b, a % b, x1, y1);

    x = y1;
    y = x1 - (a / b) * y1;

    return gcd;
}

// Функция для нахождения обратного элемента
int64_t findModularInverse(int64_t a, int64_t m) {
    int64_t x, y;
    int64_t gcd = extendedEuclidean(a, m, x, y);

    x = (x % m + m) % m;

    return x;
}

string caesar_cipher(const string& message, int64_t k) {
    string result = "";

    for (char c : message) {
        result += char((c + k) % 256);
    }

    return result;
}

string caesar_decipher(const string& message, int64_t k_prime) {
    string result = "";

    for (char c : message) {
        result += char((c - k_prime + 256) % 256);
    }

    return result;
}

void huges() {
    string message;
    getline(cin, message);

    int64_t a, p;
    tie(a, p) = init();

    int64_t x = rn(p);
    int64_t y;

    while (true) {
        y = rn(p);
        if (gcd(y, p - 1) == 1) {
            break;
        }
    }

    cout << "Абонент А выбирает случайное большое целое число х: " << x << endl;

    int64_t k = powMod(a, x, p);
    cout << "Абонент А генерирует закрытый ключ k: " << k << endl;

    string encrypted = caesar_cipher(message, k);
    cout << "Абонент А зашифровывает сообщение: " << encrypted << endl;
    cout << "Абонент B выбирает случайное большое целое число у (взаимно простое с p - 1): " << y << endl;

    int64_t Y = powMod(a, y, p);
    cout << "Абонент B посылает абоненту А: " << Y << endl;

    int64_t X = powMod(Y, x, p);
    cout << "Абонент А посылает абоненту B: " << X << endl;

    int64_t z = findModularInverse(y, p - 1);
    cout << "Абонент B вычисляет z: " << z << endl;

    int64_t k_prime = powMod(X, z, p);
    cout << "Абонент B вычисляет k': " << k_prime << endl;

    if (k == k_prime) {
        cout << "Закрытый ключ k = k'" << endl;
        string decrypted = caesar_decipher(encrypted, k_prime);
        cout << "Расшифрованное сообщение: " << decrypted << endl;
    } else {
        cout << "Закрытый не равен k = k'" << endl;
    }

    cout << endl << endl;
}