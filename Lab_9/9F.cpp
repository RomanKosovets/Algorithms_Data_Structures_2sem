#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

enum Game {LOSE, WIN};

vector <vector <int>> graph;
vector <Game> Position;
vector <bool> visited;

void dfs(vector <vector <int>>& graph, vector <bool>& visited, vector<Game>& Position, int from) {
    visited[from] = true;
    Game status = LOSE;

    for (int i = 0; i < graph[from].size(); i++) {
        int next = graph[from][i];
        if (!visited[next])
            dfs(graph, visited, Position, next);
        if (Position[next] == LOSE)
            status = WIN;
    }
    Position[from] = status;
}

int main() {
    ifstream fin("game.in");
    ofstream fout("game.out");

    int n_tops, m_edges, start = 0;
    fin >> n_tops >> m_edges >> start;

    graph.resize(n_tops);
    Position.resize(n_tops);
    visited.resize(n_tops, false);

    for (int i = 0; i < m_edges; i++) {
        int from, here = 0;
        fin >> from >> here;
        graph[from - 1].push_back(here - 1);
    }

    dfs(graph, visited, Position, start - 1);

    if (Position[start- 1])
        fout << "WIN player wins" << "\n";
    else
        fout << "LOSE player wins" << "\n";
    return 0;
}