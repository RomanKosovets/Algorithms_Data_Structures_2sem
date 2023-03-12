#include <fstream>
#include <queue>
#include <algorithm>
using namespace std;

struct Edge {
    int from, to, weight, flow;
};


vector<vector<int>> graph;
vector<Edge> edges;
vector<int> ptr;
vector<int> level;
int tops, All_edges, Istok, Stok;

bool bfs() {
    level.assign(tops, 0);
    queue<int> q;
    q.push(Istok);
    level[Istok] = 1;
    while (!q.empty() && !level[Stok]) {
        int from = q.front();
        q.pop();
        for (auto& edge : graph[from]) {
            if (!level[edges[edge].to] && edges[edge].weight > edges[edge].flow) {
                q.push(edges[edge].to);
                level[edges[edge].to] = level[from] + 1;
            }
        }
    }
    return level[Stok];
}

int dfs(int vertex = Istok, int flow = INT_MAX) {
    if (!flow)
        return 0;
    if (vertex == Stok)
        return flow;
    while (ptr[vertex] < graph[vertex].size()) {
        int edge = graph[vertex][ptr[vertex]];
        if (level[vertex] + 1 == level[edges[edge].to]){
            int pushed = dfs(edges[edge].to, min(flow, edges[edge].weight - edges[edge].flow));
            if (pushed) {
                edges[edge].flow += pushed;
                edges[edge ^ 1].flow -= pushed;
                return pushed;
            }
        }
        ptr[vertex]++;
    }
    return 0;
}

void add(int from, int to, int weight) {
    graph[from].push_back(edges.size());
    edges.emplace_back(Edge{ from, to, weight, 0});
    graph[to].push_back(edges.size());
    edges.emplace_back(Edge{ to, from, 0, 0 });
}

int main() {
    ifstream fin("circulation.in");
    ofstream fout("circulation.out");

    fin >> tops >> All_edges;
    tops += 2;
    
    graph.resize(tops);
    ptr.resize(tops, 0);
    Stok = tops - 1;
    
    for (int i = 0; i < All_edges; i++) {
        int from, to, lowFlow, highFlow;
        fin >> from >> to >> lowFlow >> highFlow;
        add(Istok, to, lowFlow);
        add(from, to, highFlow - lowFlow);
        add(from, Stok, lowFlow);
    }
    
    while (bfs()) {
        while (dfs());
        ptr.assign(tops, 0);
    }

    for (int edge : graph[0]) {
        if (edges[edge].flow < edges[edge].weight) {
            fout << "NO\n";
            return 0;
        }
    }

    fout << "YES\n";
    for (int i = 0; i < edges.size(); i += 6)
        fout << edges[i + 2].flow + edges[i + 4].flow << endl;
    return 0;
}
