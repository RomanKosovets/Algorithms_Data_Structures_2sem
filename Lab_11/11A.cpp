#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;
typedef long long ll;
const long long INF = 100000000001;

void dijkstra(ll start, ll tops, vector <bool> &visited, vector <ll> &distanc, vector <vector <ll>> &graph) {
    distanc[start - 1] = 0;
   for (ll i = 0; i < tops; i++) {
        ll top = -1;
        for (ll j = 0; j < tops; j++)
            if (!visited[j] && (top == -1 || distanc[j] < distanc[top]))    // выбираем наименьшее расстояние
                top = j;

        if (distanc[top] == INF) //проверяем идет ли туда ребро
            break;
        visited[top] = true;

        for (ll j = 0; j < tops; j++)  // релаксируем все ребра исходящие из этой вершины
            distanc[j] = min(distanc[j], distanc[top] + graph[top][j]);
    }
}

int main()
{
    ifstream fin("pathmgep.in");
    ofstream fout("pathmgep.out");

    ll tops, start, finish;
    fin >> tops >> start >> finish;

    vector <vector <ll>> graph(tops, vector <ll>(tops, INF));
    vector <ll> distanc(tops, INF);
    vector <bool> visited(tops);

    for (ll i = 0; i < tops; i++) {
        for (ll j = 0; j < tops; j++) {
            fin >> graph[i][j];
            if (graph[i][j] < 0)
                graph[i][j] = INF;
        }
    }

    dijkstra(start, tops, visited, distanc, graph);
    distanc[finish - 1] >= INF ? fout << -1 : fout << distanc[finish - 1];
    return 0;
}

//7 4 2
//0 2 -1 1 -1 -1 -1
//-1 0 -1 3 10 -1 -1
//4 -1 0 -1 -1 5 -1
//-1 -1 2 0 2 8 4
//-1 -1 -1 -1 0 -1 6
//-1 -1 -1 -1 -1 0 -1
//-1 -1 -1 -1 -1 1 0