#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// Упрощенная функция для вычисления разнообразности
int calculateDiversity(const string& s) {
    int freq[256] = {0};  // Массив для подсчета частот (все элементы = 0)
    
    // Первый проход: подсчет частот
    for (char c : s) {
        freq[(unsigned char)c]++;
    }
    
    int diversity = 0;
    // Второй проход: подсчет уникальных символов
    for (char c : s) {
        if (freq[(unsigned char)c] == 1) {
            diversity++;
        }
    }
    
    return diversity;
}

int main() {
    ifstream input("input.txt");
    ofstream output("output.txt");
    
    string s;
    input >> s;
    int n = s.length();
    
    int maxDiversity = 0;
    vector<string> candidates;
    
    // Перебираем все возможные подстроки
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            string substring = s.substr(i, j - i + 1);
            int diversity = calculateDiversity(substring);
            
            if (diversity > maxDiversity) {
                maxDiversity = diversity;
                candidates.clear();
                candidates.push_back(substring);
            } else if (diversity == maxDiversity && maxDiversity > 0) {
                candidates.push_back(substring);
            }
        }
    }
    
    // Обработка случая, когда все символы повторяются
    if (candidates.empty()) {
        // Ищем подстроку минимальной длины (в лексикографическом порядке)
        string bestSubstring = s.substr(0, 1);
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                string current = s.substr(i, j - i + 1);
                if (current.length() < bestSubstring.length()) {
                    bestSubstring = current;
                } else if (current.length() == bestSubstring.length() && current < bestSubstring) {
                    bestSubstring = current;
                }
            }
        }
        output << bestSubstring;
    } else {
        // Сортируем кандидатов: сначала по разнообразности, потом по алфавиту
        sort(candidates.begin(), candidates.end(), [](const string& a, const string& b) {
            int divA = calculateDiversity(a);
            int divB = calculateDiversity(b);
            if (divA != divB) {
                return divA > divB;  // Сначала более разнообразные
            }
            return a < b;            // Потом по алфавиту
        });
        
        output << candidates[0];
    }
    
    input.close();
    output.close();
    return 0;
}