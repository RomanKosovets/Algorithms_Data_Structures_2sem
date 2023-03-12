#include <fstream>
#include <queue>
#include <algorithm>

using namespace std;

struct Edge {
    int from, to, weight, flow, number;
};

int tops, ALL_edges, Istok, Stok;
vector<vector<int>> answer; // массив ответов
vector<vector<int>> graph;  // массив номеров ребер
vector<Edge> edges;         // массив наших ребер
vector<int> Used_egs;       // массив посещенных ребер
vector<int> level;          // массив номеров пути нашего потока


bool bfs() {                // ищем наш поток и заносим номера вершин в level
    level.assign(tops, 0);
    queue<int> q;
    q.push(Istok);
    level[Istok] = 1;
    while (!q.empty() && !level[Stok]) {
        int from = q.front();
        q.pop();
        for (auto &edge: graph[from]) {
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
    while (Used_egs[vertex] < graph[vertex].size()) { //пробегаемся по всем не посещенным ребрам для вершины в которой находимся
        int edge = graph[vertex][Used_egs[vertex]];
        if (level[vertex] + 1 == level[edges[edge].to]) {           // проверяем что поток идёт в след. вершину в level
            int pushed = dfs(edges[edge].to, min(flow, edges[edge].weight - edges[edge].flow));  // если так, то идем в верш и берем мин вес
            if (pushed) {                                           // меняем кол-во потока у двух ребер (туда, сюда)
                edges[edge].flow += pushed;
                edges[edge ^ 1].flow -= pushed;
                return pushed;
            }
        }
        Used_egs[vertex]++;
    }
    return 0;
}


int decomposition(int vertex, int minFlow = INT_MAX) {
    if (vertex == Stok) {
        answer.emplace_back();
        return minFlow;
    }
    for (int edge: graph[vertex]) {
        if (edges[edge].flow > 0) { // если есть вес, то идем дальше
            int result = decomposition(edges[edge].to, min(minFlow, edges[edge].flow));
            if (result) {
                answer.back().push_back(edges[edge].number);                   // номер ребра
                if (vertex == Istok) {
                    answer.back().push_back(answer[answer.size() - 1].size()); // записываем длину нашего пути
                    answer.back().push_back(result);                           // вес нашего пути
                    reverse(answer.back().begin(), answer.back().end());       // переворачиваем
                }
                edges[edge].flow -= result;
                return result;
            }
        }
    }
    return 0;
}


int main() {
    ifstream fin("decomposition.in");
    ofstream fout("decomposition.out");

    fin >> tops >> ALL_edges;

    graph.resize(tops);
    Used_egs.resize(tops, 0);

    for (int i = 0; i < ALL_edges; i++) {
        int from, to, weight;
        fin >> from >> to >> weight;
        graph[from - 1].push_back(edges.size());
        edges.emplace_back(Edge{from - 1, to - 1, weight, 0, i + 1});
        graph[to - 1].push_back(edges.size());
        edges.emplace_back(Edge{to - 1, from - 1, 0, 0, i + 1});
    }

    Stok = tops - 1;
    while (bfs()) {
        while (dfs());
        Used_egs.assign(tops, 0);
    }

    while (decomposition(Istok));
    fout << answer.size() << "\n";
    
    for (int i = 0; i < answer.size(); i++) {
        for (int j = 0; j < answer[i].size(); j++)
            fout << answer[i][j] << ' ';
        fout << '\n';
    }
    return 0;
}