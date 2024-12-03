#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <climits> // ��� ������������ INT_MAX
#include <windows.h>
using namespace std;

// �������, ��� ��������� ������� ������������ ����� � �����
int findShortestWordInLine(const string& line) {
    int minLength = INT_MAX; // ��������� ������������ ����������� ��������
    int currentLength = 0;   // ������� ��������� �����

    for (char ch : line) {
        if (isalpha(ch)) { // ����������, �� � ������ ������
            currentLength++;
        }
        else if (currentLength > 0) { // ʳ���� �����
            if (currentLength < minLength) {
                minLength = currentLength;
            }
            currentLength = 0; // ������� ������� ��� ���������� �����
        }
    }

    // ���������� �������, ���� ����� ���������� � ���� �����
    if (currentLength > 0 && currentLength < minLength) {
        minLength = currentLength;
    }

    return minLength;
}

// �������, ��� ��������� ������� ������������ ����� � ����
int findShortestWordInFile(const string& fileName) {
    ifstream inputFile(fileName);
    if (!inputFile.is_open()) {
        throw runtime_error("�� ������� ������� ����: " + fileName);
    }

    int minLength = INT_MAX;
    string line;

    while (getline(inputFile, line)) {//����������
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
    cout << "������ ��'� �����: ";
    cin >> fileName;

    try {
        int shortestWordLength = findShortestWordInFile(fileName);
        if (shortestWordLength > 0) {
            cout << "������� ������������ �����: " << shortestWordLength << endl;
        }
        else {
            cout << "� ���� �� �������� ������� �����." << endl;
        }
    }
    catch (const exception& ex) {
        cerr << "�������: " << ex.what() << endl;
    }

    return 0;
}