#include <iostream>
#include <vector>
#include "fstream"

using namespace std;

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    int n, m;
    fin >> n >> m;
    vector<vector <int>> graph(n);

    for (int i = 0; i < m; i++) {
        int from, to;
        fin >> from >> to;
        graph[from - 1].push_back(to - 1);
        graph[to - 1].push_back(from - 1);
    }

    for (int i = 0; i < graph.size(); i++)
        fout << graph[i].size() << ' ';

    return 0;
}

