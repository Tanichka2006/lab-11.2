#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <climits> // Для використання INT_MAX
#include <windows.h>
using namespace std;

// Функція, яка знаходить довжину найкоротшого слова в рядку
int findShortestWordInLine(const string& line) {
    int minLength = INT_MAX; // Початково встановлюємо максимальне значення
    int currentLength = 0;   // Довжина поточного слова

    for (char ch : line) {
        if (isalpha(ch)) { // Перевіряємо, чи є символ літерою
            currentLength++;
        }
        else if (currentLength > 0) { // Кінець слова
            if (currentLength < minLength) {
                minLength = currentLength;
            }
            currentLength = 0; // Скидаємо довжину для наступного слова
        }
    }

    // Обробляємо випадок, якщо слово закінчилося в кінці рядка
    if (currentLength > 0 && currentLength < minLength) {
        minLength = currentLength;
    }

    return minLength;
}

// Функція, яка знаходить довжину найкоротшого слова у файлі
int findShortestWordInFile(const string& fileName) {
    ifstream inputFile(fileName);
    if (!inputFile.is_open()) {
        throw runtime_error("Не вдалося відкрити файл: " + fileName);
    }

    int minLength = INT_MAX;
    string line;

    while (getline(inputFile, line)) {//зчитування
        int lineMinLength = findShortestWordInLine(line);
        if (lineMinLength < minLength) {
            minLength = lineMinLength;
        }
    }

    inputFile.close();

    return (minLength == INT_MAX) ? 0 : minLength;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    string fileName;
    cout << "Введіть ім'я файлу: ";
    cin >> fileName;

    try {
        int shortestWordLength = findShortestWordInFile(fileName);
        if (shortestWordLength > 0) {
            cout << "Довжина найкоротшого слова: " << shortestWordLength << endl;
        }
        else {
            cout << "У файлі не знайдено жодного слова." << endl;
        }
    }
    catch (const exception& ex) {
        cerr << "Помилка: " << ex.what() << endl;
    }

    return 0;
}