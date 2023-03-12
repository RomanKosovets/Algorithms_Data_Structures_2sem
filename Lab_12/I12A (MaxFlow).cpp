#include <fstream>
#include <queue>

using namespace std;

int maxFlow;
int tops, edges;

bool bfs(int Istok, int Stok, vector<vector<int>> &graph, vector<int> &parents) {
    vector<bool> visited(tops);
    queue <int> q;
    q.push(Istok);
    visited[Istok] = true;
    while (!q.empty()) {                // В остаточной сети находим кратчайший путь из источника в сток.
        int from = q.front();
        q.pop();
        for (int to = 0; to < tops; to++) {
            if (!visited[to] && graph[from][to] > 0) {
                q.push(to);
                parents[to] = from;
                visited[to] = true;
            }
        }
    }
    return visited[Stok];
}

void edmondsKarp(int Istok, int Stok, vector<vector<int>> &graph, vector<int> &parents) {
    while (bfs(Istok, Stok, graph, parents)) {
        int partFlow = INT_MAX;
        for (int to = Stok; to != Istok; to = parents[to]) {    // ищем минимальный вес потока в нашем пути
            int from = parents[to];
            partFlow = min(partFlow, graph[from][to]);
        }
        for (int to = Stok; to != Istok; to = parents[to]) {    // Для каждого ребра в пути увеличиваем поток на min,
            int from = parents[to];                             // а в противоположном ему — уменьшаем на min
            graph[from][to] -= partFlow;
            graph[to][from] += partFlow;
        }
        maxFlow += partFlow;
    }
}

int main() {
    ifstream fin("maxflow.in");
    ofstream fout("maxflow.out");

    fin >> tops >> edges;
    vector<vector<int>> graph(tops, vector<int>(tops, 0));
    vector<int> parents(tops, -1);

    for (int i = 0; i < edges; i++) {
        int from, to, flow;
        fin >> from >> to >> flow;
        graph[from - 1][to - 1] = flow;
    }

    edmondsKarp(0, tops - 1, graph, parents);
    fout << maxFlow;
    return 0;
}