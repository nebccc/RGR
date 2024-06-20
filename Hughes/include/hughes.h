#include <iostream>
#include <string>
#include <random>
#include <tuple>
#include <cmath>

using namespace std;

std::pair<int64_t, int64_t> init();
bool isPrime(int64_t n);
int64_t rn(int64_t p);
int64_t gcd(int64_t a, int64_t b);
int64_t f(int64_t x, int64_t y, int64_t n, int64_t r);
int64_t powMod(int64_t x, int64_t y, int64_t n);
int64_t extendedEuclidean(int64_t a, int64_t b, int64_t& x, int64_t& y);
int64_t findModularInverse(int64_t a, int64_t m);
std::string caesar_cipher(const std::string& message, int64_t k);
std::string caesar_decipher(const std::string& message, int64_t k_prime);
int64_t huges();
