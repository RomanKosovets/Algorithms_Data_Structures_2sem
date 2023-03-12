#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

int flag = -1;
enum {WHITE, GRAY, BLACK};

vector<int> parents;
vector<int> color;
vector<int> cycle;
vector< vector<int> > graph;

int dfs(int top) {
    color[top] = GRAY;

    for (int i : graph[top]) {
        if (color[i] == GRAY) {
            parents[i] = top;
            return top;
        }
        if (color[i] == WHITE) {
            parents[i] = top;
            int Top_cycle_start = dfs(i);
            if (Top_cycle_start != flag) {
                return Top_cycle_start;
            }
        }
    }

    color[top] = BLACK;
    return flag;
}

int main()
{
    ifstream fin("C:\\Users\\roman\\CLionProjects\\Project C++\\9 lab\\123.txt");
    ofstream fout("C:\\Users\\roman\\CLionProjects\\Project C++\\9 lab\\321.txt");

    int n_tops, n_edges = 0;
    fin >> n_tops >> n_edges;

    graph.resize(n_tops);
    color.resize(n_tops, WHITE);
    parents.resize(n_tops, -1);

    for (int i = 0; i < n_edges; i++) {
        int from, here = 0;
        fin >> from >> here;
        graph[from - 1].push_back(here - 1);
    }

    for (int i = 0; i < n_tops; i++) {
        if (color[i] == WHITE) {
            int Top_cycle_start = dfs(i);
            if (Top_cycle_start != flag) {
                fout << "YES\n";
                fout << Top_cycle_start + 1 << ' ';

                for (int top = parents[Top_cycle_start]; top != Top_cycle_start; top = parents[top]) {
                    cycle.push_back(top + 1);
                }
                for (int i = cycle.size() - 1; i >= 0; i--) {
                    fout << cycle[i] << " ";
                }
                return 0;
            }
        }
    }

    fout << "NO";
    return 0;
}