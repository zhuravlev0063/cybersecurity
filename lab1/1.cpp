#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main() {
    string s;
    
    // Чтение строки из файла
    ifstream input_file("input1.txt");
    if (input_file.is_open()) {
        getline(input_file, s);
        input_file.close();
    } else {
        cout << "Ошибка: не удалось открыть файл input.txt" << endl;
        return 1;
    }
    
    cout << "Исходная строка: " << s << endl;
    
    int write_index = 0;
    for (int read_index = 0; read_index < s.size(); read_index++) {
        if (write_index > 0 && s[write_index - 1] == s[read_index]) {
            write_index--;
        } else {
            s[write_index++] = s[read_index];
        }
    }
    
    cout << "Результат: " << s.substr(0, write_index) << endl;
    
    return 0;
}