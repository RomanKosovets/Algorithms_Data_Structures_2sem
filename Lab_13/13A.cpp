#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


bool equal(string &main_str, string &sub_str, int start) {
    for (int i = 0; i < sub_str.length(); i++)
        if (main_str[start + i] != sub_str[i])
            return false;
    return true;
}


vector <int> find_substrings (string &main_str, string &sub_str) {
    int n = main_str.length();
    int m  = sub_str.length();
    vector <int> indexes;

    for (int i = 0; i <= n - m; i++) {
        if (equal(main_str, sub_str, i))
            indexes.push_back(i);
    }
    return indexes;
}


int main() {
    ifstream fin ("C:\\Users\\roman\\Programming\\CLionProjects\\Algos_C++\\13 lab\\input.txt");
    ofstream fout ("C:\\Users\\roman\\Programming\\CLionProjects\\Algos_C++\\13 lab\\output.txt");

    string sub_str, main_str;
    fin >> sub_str >> main_str;

    vector <int> answer = find_substrings(main_str, sub_str);

    fout << answer.size() << "\n";
    for (int i = 0; i < answer.size(); i++)
        fout << answer[i] + 1 << ' ';
    return 0;
}