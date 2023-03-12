#include <fstream>
#include <vector>
#include <set>

using namespace std;

void dijkstra(vector <vector <pair <int, int>>> &graph, vector <int> &distanc, set <pair<int, int>> &AllEdges) {
    distanc[0] = 0;
    AllEdges.emplace(distanc[0], 0);

    while (!AllEdges.empty()) {
        int from = AllEdges.begin()->second;  // берем нашу вершину заносим в from
        AllEdges.erase(AllEdges.begin());     // удаляем вершину и вес

        for (int edge = 0; edge < graph[from].size(); edge++) {
            int to = graph[from][edge].first;
            int weight = graph[from][edge].second;

            if (distanc[from] + weight < distanc[to]) {
                AllEdges.erase({distanc[to], to});
                distanc[to] = distanc[from] + weight;       // } перезаписываем дист в след. вершину
                AllEdges.emplace(distanc[to], to);
            }
        }
    }
}

int main() {
    ifstream fin("pathbgep.in");
    ofstream fout("pathbgep.out");


    int tops, edges;
    fin >> tops >> edges;

    vector <vector <pair <int, int>>> graph(tops);
    vector <int> distanc(tops, INT_MAX);
    set <pair<int, int>> AllEdges;

    for (int i = 0; i < edges; i++) {
        int from, to, weight;
        fin >> from >> to >> weight;
        graph[from - 1].emplace_back(to - 1, weight);
        graph[to - 1].emplace_back(from - 1, weight);
    }

    dijkstra(graph, distanc, AllEdges);
    for (int i = 0; i < distanc.size(); i++)
        fout << distanc[i] << " ";
    return 0;
}

