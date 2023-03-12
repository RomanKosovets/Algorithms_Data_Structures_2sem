#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

enum {WHITE, GRAY, BLACK};

vector<int> topsort;                // наш стек
vector<int> color;                  // массив цветов вершин
vector< vector<int> > graph;        // массив графа

bool dfs(int top) {
    color[top] = GRAY;              // заходим в dfs, красим вершину в серый, т.к. она в процессе
    for (auto i : graph[top]){      // просматриваем каждую вершину куда ведёт top
        if (color[i] == GRAY) {
            return true;
        }
        if (color[i] == WHITE) {
            if (dfs(i)) {
                return true;
            }
        }
    }

    topsort.push_back(top);
    color[top] = BLACK;
    return false;
}

int main()
{
    ifstream fin("C:\\Users\\roman\\CLionProjects\\Project C++\\9 lab\\123.txt");
    ofstream fout("C:\\Users\\roman\\CLionProjects\\Project C++\\9 lab\\321.txt");

    int n_tops, n_edges = 0;
    fin >> n_tops >> n_edges;

    graph.resize(n_tops);
    color.resize(n_tops, WHITE);

    for (int i = 0; i < n_edges; i++) {
        int from, here = 0;
        fin >> from >> here;
        graph[from - 1].push_back(here - 1);
    }

    for (int i = 0; i < n_tops; i++) {
        if (color[i] == WHITE) {
            if (dfs(i)) {
                fout << "-1\n";
                return 0;
            }
        }
    }

    for (int i = topsort.size() - 1; i >= 0; i--) {
        fout << topsort[i] + 1 << " ";
    }
    return 0;
}

