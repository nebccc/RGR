#include <iostream>

struct Vector {
    double x, y;

    // Перегрузка оператора + для сложения векторов
    Vector operator+(const Vector& other) const {
        return {x + other.x, y + other.y};
    }

    // Перегрузка оператора - для вычитания векторов
    Vector operator-(const Vector& other) const {
        return {x - other.x, y - other.y};
    }

    // Перегрузка оператора * для умножения вектора на скаляр
    Vector operator*(double scalar) const {
        return {x * scalar, y * scalar};
    }

    // Перегрузка оператора * для скалярного произведения векторов
    double operator*(const Vector& other) const {
        return x * other.x + y * other.y;
    }

    // Перегрузка оператора == для сравнения векторов
    bool operator==(const Vector& other) const {
        return x == other.x && y == other.y;
    }

    // Перегрузка оператора != для сравнения векторов
    bool operator!=(const Vector& other) const {
        return !(*this == other);
    }

    // Перегрузка оператора << для вывода вектора
    friend std::ostream& operator<<(std::ostream& os, const Vector& v) {
        os << "(" << v.x << ", " << v.y << ")";
        return os;
    }

    // Перегрузка оператора >> для ввода вектора
    friend std::istream& operator>>(std::istream& is, Vector& v) {
        is >> v.x >> v.y;
        return is;
    }
};

int main() {
    Vector v1{1.0, 2.0};
    Vector v2{3.0, 4.0};

    // Пример использования перегруженных операторов
    Vector v3 = v1 + v2;
    Vector v4 = v1 - v2;
    Vector v5 = v1 * 2.0;
    double dotProduct = v1 * v2;
    bool areEqual = (v1 == v2);
    bool areNotEqual = (v1 != v2);

    std::cout << "v3 = " << v3 << std::endl;
    std::cout << "v4 = " << v4 << std::endl;
    std::cout << "v5 = " << v5 << std::endl;
    std::cout << "Dot product = " << dotProduct << std::endl;
    std::cout << "v1 and v2 are equal: " << (areEqual ? "true" : "false") << std::endl;
    std::cout << "v1 and v2 are not equal: " << (areNotEqual ? "true" : "false") << std::endl;

    Vector v6;
    std::cout << "Enter vector v6 (format: x y): ";
    std::cin >> v6;
    std::cout << "v6 = " << v6 << std::endl;

    return 0;
}
