#include <iostream>
#include <vector>
#include <fstream>

using namespace std;
enum Color {WHITE, BLACK};

vector <vector <int>> graph;
vector <Color> color;

Color reverse(Color color) {
    if (color == BLACK)
        return WHITE;
    else return BLACK;
}

void dfs(vector <vector <int>>& graph, vector <Color>& color, int from, Color topColor, bool& Its_Bi_graph) {
    color[from] = topColor;
    for (int here : graph[from]) {
        if (color[here] == WHITE) {
            dfs(graph, color, here, reverse(topColor), Its_Bi_graph);
        }
        else if (color[here] == topColor) {
            Its_Bi_graph = false;
            return;
        }
    }
}

int main() {
    ifstream fin("bipartite.in");
    ofstream fout("bipartite.out");

    int n_tops, m_edges = 0;
    fin >> n_tops >> m_edges;

    graph.resize(n_tops);
    color.resize(n_tops, WHITE);

    for (int i = 0; i < m_edges; i++) {
        int from, here;
        fin >> from >> here;
        graph[from - 1].push_back(here - 1);
        graph[here - 1].push_back(from - 1);
    }

    bool Its_Bi_graph = true;

    for (int i = 0; i < n_tops; i++)
        if (color[i] == WHITE) {
            dfs(graph, color, i, WHITE, Its_Bi_graph);
            if (!Its_Bi_graph) {
                fout << "NO";
                return 0;
            }
        }
    fout << "YES";
    return 0;
}
