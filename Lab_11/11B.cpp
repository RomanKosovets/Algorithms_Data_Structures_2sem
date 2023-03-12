#include <fstream>
#include <vector>

using namespace std;

void floyd(vector <vector <int>> &graph, int tops) {
    for (int j = 0; j < tops; j++) {
        for (int i = 0; i < tops; i++){
            for (int k = 0; k < tops; k++) {
                graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
            }
        }
    }
}

int main() {
    ifstream fin("C:\\Users\\roman\\Programming\\CLionProjects\\ALgos_C++\\11 lab\\input.txt");
    ofstream fout("C:\\Users\\roman\\Programming\\CLionProjects\\ALgos_C++\\11 lab\\123.txt");
    
    int tops, edges;
    fin >> tops >> edges;

    vector<vector <int>> graph(tops, vector <int>(tops, 100000));

    for (int i = 0; i < edges; i++) {
        int from, to, weight;
        fin >> from >> to >> weight;

        graph[from - 1][to - 1] = weight;
    }

    floyd(graph, tops);

    for (int i = 0; i < tops; i++) {
        for (int j = 0; j < tops; j++) {
            if (i == j)
                graph[i][j] = 0;
            fout << graph[i][j] << ' ';
        }
        fout << '\n';
    }
    return 0;
}