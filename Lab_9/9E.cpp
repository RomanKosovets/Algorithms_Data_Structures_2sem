#include <vector>
#include <fstream>

enum {WHITE, BLACK};

using namespace std;

vector<int> topsorted;
vector<int> color;
vector< vector<int> > graph;

void DFS(int top) {
    for (auto u : graph[top]) {
        if (color[u] == WHITE) {
            DFS(u);
        }
    }

    topsorted.push_back(top);
    color[top] = BLACK;
}

bool exist(vector <vector <int>>& graph, int from, int here) {
    for (int i : graph[from])
        if (i == here)
            return true;
    return false;
}

int main() {
    ifstream fin("C:\\Users\\roman\\CLionProjects\\Project C++\\9 lab\\123.txt");
    ofstream fout("C:\\Users\\roman\\CLionProjects\\Project C++\\9 lab\\321.txt");

    int n_tops, n_edges = 0;
    fin >> n_tops >> n_edges;

    graph.resize(n_tops);
    color.resize(n_tops, WHITE);

    for (int i = 0; i < n_edges; ++i) {
        int from, here = 0;
        fin >> from >> here;
        graph[from - 1].push_back(here - 1);
    }

    for (int i = 0; i < n_tops; i++) {
        if (color[i] == WHITE) {
            DFS(i);
        }
    }

    for (int i = n_tops - 1; i > 0; i--)
        if (!exist(graph, topsorted[i], topsorted[i - 1])) {
            fout << "NO";
            return 0;
        }

    fout << "YES";
    return 0;
}
